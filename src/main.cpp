#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>
#include <RTClib.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <WiFi.h>
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

#include <Ntp_Servers.h>
#include <Macros.h>
#include <TimeZoneConf.h>

#include <Font_Data.h>
#include <Screens.h>
#include <Set_NTP_Time.h>
#include <Set_Intensity.h>
#include <Beep.h>

#define path_to_conf "/config.json"

MD_Parola matrix = MD_Parola(MD_MAX72XX::FC16_HW, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
RTC_DS3231 rtc;
Adafruit_BME280 bme;
BH1750 light_sensor;

Bounce2::Button screen_button = Bounce2::Button();
uint8_t buzzer = BUZZER_PIN;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, INRIM);

DateTime current_time;

std::unordered_map<std::string, std::vector<std::string>> months = {
    {"en", {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}},
    {"it", {"Gen", "Feb", "Mar", "Apr", "Mag", "Giu", "Lug", "Ago", "Set", "Ott", "Nov", "Dic"}},
    {"es", {"Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"}},
    {"fr", {"Jan", "Fev", "Mar", "Avr", "Mai", "Jun", "Jul", "Aou", "Sep", "Oct", "Nov", "Dec"}},
    {"de", {"Jan", "Feb", "Mar", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Dez"}}
};

std::unordered_map<std::string, std::vector<std::string>> days = {
    {"en", {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"}},
    {"it", {"Dom", "Lun", "Mar", "Mer", "Gio", "Ven", "Sab"}},
    {"es", {"Dom", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab"}},
    {"fr", {"Dim", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam"}},
    {"de", {"Son", "Mon", "Die", "Mit", "Don", "Fre", "Sam"}}
};

struct Config {
  char hostname[64];
  int port;
};

bool sound = true;
int sound_interval = 0;

uint8_t displaySelector = 0;
Config conf;

void loadConfiguration(Config& config) {
  File file = SPIFFS.open(path_to_conf, "r");
  JsonDocument doc;

  DeserializationError error = deserializeJson(doc, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

  config.port = doc["port"] | 2731;
  strlcpy(config.hostname,                  // <- destination
          doc["hostname"] | "example.com",  // <- source
          sizeof(config.hostname));         // <- destination's capacity

  file.close();
}

void setup()
{
  Serial.begin(115200);

  if(!SPIFFS.begin()){
    Serial.println("Failed to mount SPIFFS.\n");
    return;
  }
  Serial.println("SPIFFS mounted successfully.\n");

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  //initialize button
  screen_button.attach(BUTTON_PIN, INPUT_PULLUP);
  screen_button.interval(5);
  screen_button.setPressedState(LOW);

  if(!matrix.begin(9)) {
    Serial.printf("Could not find MAX7219! Check wiring!\n");
    while(true);
  }

  if (!rtc.begin(&Wire)) {
    Serial.printf("Could not find DS3231 RTC! Check wiring!\n");
    while(true);
  }

  if (!bme.begin(BME280_ADDR, &Wire)) {
    Serial.println("Could not find BME280 sensor! Check wiring!\n");
    while(true);
  }

  if(!light_sensor.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, BH1750_ADDR, &Wire)) {
    Serial.println("Could not find BH1750 sensor! Check wiring!\n");
    while(true);
  }

  if (rtc.lostPower()) {
    // if the RTC lost power, set the time trying to sync with NTP server
    Serial.printf("RTC lost power. Press the button for trying to set the time.\n");

    matrix.setZone(7, 4, 7);
    matrix.setZone(8, 0, 3);
    matrix.setFont(7, small_font);
    matrix.setFont(8, small_font);
    matrix.setZoneEffect(7, 1, PA_FLIP_UD);
    matrix.setZoneEffect(7, 1, PA_FLIP_LR);
    matrix.displayZoneText(7, "POWER", PA_CENTER, 75, 10, PA_PRINT);
    matrix.displayZoneText(8, "LOST", PA_CENTER, 75, 10, PA_PRINT);
    matrix.synchZoneStart();
    matrix.displayAnimate();

    //wait for button press
    while(!screen_button.pressed())
      screen_button.update();

    Serial.printf("Button pressed. Trying to sync time with NTP server.\n");

    set_NTP_time();
  }

  //setting up zones of the matrix display

  // upper screen for HH:MM and SS
  matrix.setZone(0, 7, 7);
  matrix.setZone(1, 4, 6);

  // lower screen for temperature
  matrix.setZone(2, 0, 3);

  // flip the upper screen
  matrix.setZoneEffect(0, 1, PA_FLIP_UD);
  matrix.setZoneEffect(0, 1, PA_FLIP_LR);
  matrix.setZoneEffect(1, 1, PA_FLIP_UD);
  matrix.setZoneEffect(1, 1, PA_FLIP_LR);

  matrix.setFont(0, small_font);
  matrix.setFont(1, pixel_font);
  matrix.setFont(2, pixel_font);

  // upper screen for DDD DD
  matrix.setZone(3, 4, 7);
  // lower screen for MMM YYYY
  matrix.setZone(4, 0, 3);

  // flip the upper screen
  matrix.setZoneEffect(3, 1, PA_FLIP_UD);
  matrix.setZoneEffect(3, 1, PA_FLIP_LR);

  matrix.setFont(3, small_font);
  matrix.setFont(4, small_font);

  // upper screen for humidity
  matrix.setZone(5, 4, 7);
  // lower screen for pressure
  matrix.setZone(6, 0, 3);

  // flip the upper screen
  matrix.setZoneEffect(5, 1, PA_FLIP_UD);
  matrix.setZoneEffect(5, 1, PA_FLIP_LR);

  matrix.setFont(5, pixel_font);
  matrix.setFont(6, pixel_font);

  matrix.displayClear();

  bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                  Adafruit_BME280::SAMPLING_X1,
                  Adafruit_BME280::SAMPLING_X1,
                  Adafruit_BME280::SAMPLING_X1,
                  Adafruit_BME280::FILTER_OFF,
                  Adafruit_BME280::STANDBY_MS_1000
                  );
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

  current_time = localTimezone->toLocal((rtc.now()).unixtime());

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
    matrix.displayShutdown(true);

    while(!screen_button.pressed())
      screen_button.update();

    while(!screen_button.released())
      screen_button.update();

    matrix.displayShutdown(false);
  }

  if(current_time.second() == 0 && current_time.minute() == 0 && sound) {
    beep_sound();
    sound = false;
    sound_interval = millis();
  }

  if(!sound && (millis() - sound_interval) > 1000)
    sound = true;

  set_intensity();
}
