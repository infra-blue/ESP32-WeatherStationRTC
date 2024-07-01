#include <Arduino.h>
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

#include <Font_Data.h>

#ifndef BME280_ADDR
#define BME280_ADDR 0x76
#endif

#ifndef BH1750_ADDR
#define BH1750_ADDR 0x23
#endif

#ifndef DS3231_ADDR
#define DS3231_ADDR 0x68
#endif

#define BUTTON_PIN 0

#define CLK_PIN   18
#define DATA_PIN  23
#define CS_PIN    5

#define MAX_DEVICES 8
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

//NTP servers
#define MCNTP "time.windows.com"
#define POOLNTP "pool.ntp.org"
#define POOLNTP1 "0.it.pool.ntp.org"
#define INRIM "time.inrim.it"
#define INRIM1 "ntp1.inrim.it"
#define INRIM2 "ntp2.inrim.it"

MD_Parola matrix = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
RTC_DS3231 rtc;
Adafruit_BME280 bme;
BH1750 light_sensor;

Bounce2::Button screen_button = Bounce2::Button();

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, INRIM);

//Central European Time (Rome)
TimeChangeRule CET = {"CET", Last, Sun, Oct, 3, 60};    // Daylight time = UTC + 1 hour
TimeChangeRule CEST = {"CEST", Last, Sun, Mar, 2, 120};     // Standard time = UTC + 2 hours
Timezone CE(CET, CEST);

//days and months
char days[7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
char months[12][4] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

//display selector and screens
uint8_t displaySelector = 0;
enum screen{
  CLOCK_TEMP,
  DATE,
  HUMIDITY_PRESSURE
};

void setup()
{
  Serial.begin(115200);

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

    //wait for button press
    while(!screen_button.fell()) {
      screen_button.update();
      matrix.synchZoneStart();
      if(matrix.displayAnimate()){
        matrix.displayReset();
      }
    }

    Serial.printf("Button pressed. Trying to sync time with NTP server.\n");

    WiFi.mode(WIFI_STA);

    //scan for open WiFi AP
    uint8_t n_net = WiFi.scanNetworks();
    bool open_ap_found = false;
    char ssid[256];

    if (n_net) {
      Serial.println("Network found!\n");
      for (uint8_t i = 0; i < n_net; ++i) {
        if(WiFi.encryptionType(i) == WIFI_AUTH_OPEN) {
          strcpy(ssid, WiFi.SSID(i).c_str());
          open_ap_found = true;
          break;
        }
      }
    }
    else {
      Serial.println("No network found.\n");
    }

    if(open_ap_found) {
      WiFi.begin(ssid);
      Serial.printf("Connecting to %s ", ssid);

      while(WiFi.status() != WL_CONNECTED && WiFi.status() != WL_CONNECT_FAILED)
        delay(100);

      Serial.printf("\nConnected to %s.\n", ssid);

      timeClient.begin();
      delay(50);
      timeClient.update();
      delay(500);

      if(timeClient.isTimeSet()) {
        rtc.adjust(timeClient.getEpochTime());
        Serial.printf("RTC adjusted with NTP time.\nDisconnecting from %s.\n", ssid);
      }
      else {
        Serial.printf("NTP server error. Time not set.\n");
        rtc.adjust(DateTime("Jan 1 1970", "00:00:00"));
      }

      WiFi.disconnect();
    }
    else {
      Serial.printf("WiFi AP not found. Cannot Sync time.\n");
      rtc.adjust(DateTime("Jan 1 1970", "00:00:00"));
    }
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
}

void print_time_temp() {
  /**
  * @brief
  *  picks up the current time from RTC (which is in DateTime class)
  *  converts it to epochtime
  *  then to local time
  *  then prints the time on the matrix display
  *  formatted as HH:MM SS
  */

  char hh_mm[6];
  char ss[3];
  char temp[10];

  DateTime now = DateTime(CE.toLocal((rtc.now()).unixtime()));

  sprintf(hh_mm, "%02d%c%02d", now.hour(), ((now.second() % 2) ? ':' : ' '), now.minute());
  sprintf(ss, "%02d", now.second());
  sprintf(temp, "%3.1f° C", bme.readTemperature());

  //print time and temperature
  matrix.synchZoneStart();
  if(matrix.displayAnimate()) {
    matrix.displayZoneText(0, ss, PA_CENTER, 75, 0, PA_PRINT);
    matrix.displayZoneText(1, hh_mm, PA_CENTER, 75, 0, PA_PRINT);
    matrix.displayZoneText(2, temp, PA_CENTER, 75, 0, PA_PRINT);
  }
}

void print_date() {
  /**
  * @brief
  * picks up the current time from RTC (which is in DateTime class)
  * converts it to epochtime
  * then to local time
  * then prints the date on the matrix display
  * formatted as DDD DD MMM YYYY
  */
  char ddd_dd[7];
  char mmm_yyyy[9];

  DateTime now = DateTime(CE.toLocal((rtc.now()).unixtime()));

  sprintf(ddd_dd, "%s %02d", days[now.dayOfTheWeek()], now.day());
  sprintf(mmm_yyyy, "%s %d", months[now.month() - 1], now.year());

  //print date
  matrix.synchZoneStart();
  if(matrix.displayAnimate()) {
    matrix.displayZoneText(3, ddd_dd, PA_CENTER, 75, 0, PA_PRINT);
    matrix.displayZoneText(4, mmm_yyyy, PA_CENTER, 75, 0, PA_PRINT);
  }
}

void print_hum_pres() {
  /**
  * @brief
  * picks up the current humidity and pressure from BME280 sensor
  * then prints the humidity and pressure on the matrix display
  * formatted as HHH.H% and PPPP.P
  */

  char hum[9];
  char pres[9];

  sprintf(hum, "H %3.1f%%", bme.readHumidity());
  sprintf(pres, "P%5.1f", bme.readPressure() / 100.0f);

  //print humidity and pressure
  matrix.synchZoneStart();
  if(matrix.displayAnimate()) {
    matrix.displayZoneText(5, hum, PA_RIGHT, 75, 0, PA_PRINT);
    matrix.displayZoneText(6, pres, PA_LEFT, 75, 0, PA_PRINT);
  }
}

void set_intensity() {
  /**
  * @brief
  * picks up the current light level from BH1750 sensor
  * then sets the intensity of the matrix display
  * based on the light level
  * mapped from to 0 to 15 (max level limited to 300 for more sensitivity)
  */
  if(light_sensor.measurementReady())
    matrix.setIntensity(map(constrain(round(light_sensor.readLightLevel()), 0, 300), 0, 300, 0, 15));
}

void loop()
{
  /**
  * @brief
  * updates the screen_button
  * if the button is pressed, changes the displaySelector
  * to display the time, date or humidity and pressure
  * then sets the intensity of the matrix display
  */
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
    matrix.displayShutdown(false);
    while(!screen_button.released())
      screen_button.update();
  }
  set_intensity();
}
