#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>
#include <RTClib.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <WiFi.h>
#include <WebServer.h>
#include <IPAddress.h>
#include <NTPClient.h>
#include <Timezone.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <BH1750.h>
#include <Bounce2.h>
#include <ArduinoJson.h>

#include <unordered_map>
#include <vector>
#include <string>

#include <Macros.h>

#include <Config_Parser.h>
#include <WebSettings.h>
#include <Languages.h>
#include <Font_Data.h>
#include <Screens.h>
#include <Set_NTP_Time.h>
#include <Set_Intensity.h>
#include <Beep.h>

Config conf;
WebServer server(80);

MD_Parola* matrix = nullptr;
RTC_DS3231 rtc;
Adafruit_BME280 bme;
BH1750 light_sensor;
Bounce2::Button screen_button = Bounce2::Button();

DateTime current_time;
Timezone* TMZ = nullptr;

bool tic = true;
int sound_interval = 0;
bool screen_off = false;
uint8_t displaySelector = 0;

void setup() {
  Serial.begin(115200);

  if (!SPIFFS.begin()) {
    Serial.printf("%s\n", SPIFFS_ERR);
    return;
  }
  Serial.printf("%s\n", SPIFFS_SUC);

  loadConfiguration(conf);

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(AP_NAME, AP_PASSWORD);
  IPAddress local_IP(IP_ADDRESS);
  IPAddress gateway(GATEWAY);
  IPAddress subnet(SUBNET);
  WiFi.softAPConfig(local_IP, gateway, subnet);

  server.on("/", handleHome);
  server.on("/settings", handleSettings);
  server.on("/updateTime", HTTP_POST, handleUpdateTime);
  server.on("/toggleScreen", HTTP_POST, handleToggleScreen);
  server.on("/submitNetwork", HTTP_POST, handleNetworkSubmit);
  server.on("/submitNTP", HTTP_POST, handleNTPSubmit);
  server.on("/submitLanguage", HTTP_POST, handleLanguageSubmit);
  server.on("/submitTimezone", HTTP_POST, handleTimezoneSubmit);
  server.on("/submitAdditional", HTTP_POST, handleAdditionalSubmit);
  server.begin();

  TMZ = new Timezone(conf.std, conf.dlt);
  matrix = new MD_Parola(HW_TYPE, conf.max7219.DATA_PIN, conf.max7219.CLK_PIN, conf.max7219.CS_PIN, MAX7219_DEVICES);

  pinMode(conf.pins.BUZZER_PIN, OUTPUT);
  digitalWrite(conf.pins.BUZZER_PIN, LOW);

  screen_button.attach(conf.pins.BUTTON_PIN, INPUT_PULLUP);
  screen_button.interval(5);
  screen_button.setPressedState(LOW);

  if(!matrix->begin(9)) {
    Serial.printf("%s %s\n", MAX7219_ERR, WIRE_ERR);
    while(true);
  }

  if (!rtc.begin(&Wire)) {
    Serial.printf("%s %s\n", DS3231_ERR, WIRE_ERR);
    while(true);
  }

  if (!bme.begin(conf.i2c.BME_280, &Wire)) {
    Serial.printf("%s %s\n", BME280_ERR, WIRE_ERR);
    while(true);
  }

  if(!light_sensor.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, conf.i2c.BH1750, &Wire)) {
    Serial.printf("%s %s\n", BH1750_ERR, WIRE_ERR);
    while(true);
  }

  if (rtc.lostPower()) {
    Serial.printf("%s\n", RTC_POWER_LOST);

    matrix->setZone(7, 4, 7);
    matrix->setZone(8, 0, 3);
    matrix->setFont(7, small_font);
    matrix->setFont(8, small_font);
    matrix->setZoneEffect(7, 1, PA_FLIP_UD);
    matrix->setZoneEffect(7, 1, PA_FLIP_LR);
    matrix->displayZoneText(7, "POWER", PA_CENTER, 75, 10, PA_PRINT);
    matrix->displayZoneText(8, "LOST", PA_CENTER, 75, 10, PA_PRINT);
    matrix->synchZoneStart();
    matrix->displayAnimate();

    while(!screen_button.pressed())
      screen_button.update();

    Serial.printf("Button pressed. Trying to sync time with NTP server.\n");

    set_NTP_time();
  }

  matrix->setZone(0, 7, 7);
  matrix->setZone(1, 4, 6);
  matrix->setZone(2, 0, 3);

  matrix->setZoneEffect(0, 1, PA_FLIP_UD);
  matrix->setZoneEffect(0, 1, PA_FLIP_LR);
  matrix->setZoneEffect(1, 1, PA_FLIP_UD);
  matrix->setZoneEffect(1, 1, PA_FLIP_LR);

  matrix->setFont(0, small_font);
  matrix->setFont(1, pixel_font);
  matrix->setFont(2, pixel_font);

  matrix->setZone(3, 4, 7);
  matrix->setZone(4, 0, 3);

  matrix->setZoneEffect(3, 1, PA_FLIP_UD);
  matrix->setZoneEffect(3, 1, PA_FLIP_LR);

  matrix->setFont(3, small_font);
  matrix->setFont(4, small_font);

  matrix->setZone(5, 4, 7);
  matrix->setZone(6, 0, 3);

  matrix->setZoneEffect(5, 1, PA_FLIP_UD);
  matrix->setZoneEffect(5, 1, PA_FLIP_LR);

  matrix->setFont(5, pixel_font);
  matrix->setFont(6, pixel_font);

  matrix->displayClear();

  bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                  Adafruit_BME280::SAMPLING_X16,
                  Adafruit_BME280::SAMPLING_X16,
                  Adafruit_BME280::SAMPLING_X16,
                  Adafruit_BME280::FILTER_OFF,
                  Adafruit_BME280::STANDBY_MS_1000
                  );

  printConfiguration(conf);
}

void loop()
{
  /**
  * @brief MAIN LOOP
  * updates the screen_button
  * if the button is pressed, changes the displaySelector
  * to display the time, date or humidity and pressure
  * then sets the intensity of the matrix display
  * 
  * if the button is pressed for more than 500ms
  * the display is turned off
  * and turned on again when the button is pressed again
  */

  current_time = TMZ->toLocal((rtc.now()).unixtime());
  server.handleClient();

  screen_button.update();
  if (screen_button.released())
    ++displaySelector %= 3;

  switch(displaySelector) {
    case CLOCK_TEMP:
      print_time_temp();
      break;
    case DATE:
      print_date();
      break;
    case HUMIDITY_PRESSURE:
      print_hum_pres();
      break;
  }

  if(screen_button.isPressed() && screen_button.currentDuration() > 500) {
    matrix->displayShutdown(true);
    screen_off = true;
    while(!screen_button.released())
      screen_button.update();
  }

  if(screen_button.pressed() && screen_off) {
    matrix->displayShutdown(false);
    screen_off = false;
    while(!screen_button.released())
      screen_button.update();
  }

  if(conf.buzzSound){
    if(current_time.second() == 0 && current_time.minute() == 0 && tic) {
      beep_sound();
      tic = false;
      sound_interval = millis();
    }

    if(!tic && (millis() - sound_interval) > 1000)
      tic = true;
  }

  set_intensity();
}
