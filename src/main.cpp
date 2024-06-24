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

#include <cmath>

#include <defines.h>
#include <Font_Data.h>

#ifndef BME280_ADDR
#define BME280_ADDR 0x76
#endif

#ifndef BH1750_ADDR
#define BH1750_ADDR 0x23
#endif

#ifndef DS3231_ADDRESS
#define DS3231_ADDRESS 0x68
#endif

#define CLK_PIN   18
#define DATA_PIN  23
#define CS_PIN    5

#define MAX_DEVICES 8
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW


MD_Parola matrix = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
RTC_DS3231 rtc;
Adafruit_BME280 bme;
BH1750 lux;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, INRIM);

//Central European Time (Rome)
TimeChangeRule CET = {"CET", Last, Sun, Oct, 3, 60};    // Daylight time = UTC + 1 hour
TimeChangeRule CEST = {"CEST", Last, Sun, Mar, 2, 120};     // Standard time = UTC + 2 hours
Timezone CE(CET, CEST);

Timezone current_timezone = CE;

char days[7][4] = {"DOM", "LUN", "MAR", "MER", "GIO", "VEN", "SAB"};
char months[12][4] = {"GEN", "FEB", "MAR", "APR", "MAG", "GIU", "LUG", "AGO", "SET", "OTT", "NOV", "DIC"};

void setup()
{
  Serial.begin(115200);

  if(!matrix.begin(8)) {
    Serial.printf("Error initializing MAX7219.\n");
    while(true);
  }

  if (!rtc.begin(&Wire)) {
    Serial.printf("Could not find RTC! Check circuit.\n");
    while(true);
  }

  if (!bme.begin(BME280_ADDR, &Wire)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while(true);
  }

  if(!lux.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, BH1750_ADDR, &Wire)) {
    Serial.println("Could not find a valid BH1750 sensor, check wiring!");
    while(true);
  }

  if (rtc.lostPower()) {
    Serial.printf("RTC lost power, trying to set the time.\n");

    WiFi.mode(WIFI_STA);

    Serial.printf("Scan start.\n");

    int n_net = WiFi.scanNetworks();
    bool ap_found = false;

    if (n_net)
       for (int i = 0; i < n_net; ++i)
          if(WiFi.SSID(i) == YOUR_SSID) {
            ap_found = true;
            break;
          }

    if(ap_found) {
      Serial.printf("AP found.\n");

      WiFi.begin(YOUR_SSID, YOUR_PASSWORD);

      Serial.printf("Connecting to WiFi.\n");

      while(WiFi.status() != WL_CONNECTED && WiFi.status())
        delay(100);

      Serial.printf("Connected to %s.\n", YOUR_SSID);

      timeClient.begin();
      delay(50);
      timeClient.update();
      delay(500);

      if(timeClient.isTimeSet()) {
        rtc.adjust(timeClient.getEpochTime());
        Serial.printf("RTC adjusted with NTP time.\n Disconnecting from WiFi.\n");
      }
      else {
        Serial.printf("NTP server error. Time not set.\n");
        rtc.adjust(DateTime("Jan 1 2000", "00:00:00"));
      }

      WiFi.disconnect();
    }
    else {
      Serial.printf("WiFi AP not found. Cannot Sync time.\n");
      rtc.adjust(DateTime("Jan 1 2000", "00:00:00"));
    }
  }

  matrix.setIntensity(10);
}

void print_screen_1() {
  /**
  * @brief
  *  picks up the current time from RTC (which is in DateTime class)
  *  converts it to epochtime
  *  then to local time and then to DateTime class
  *  then prints the time on the matrix display
  *  formatted as HH:MM:SS
  */

  char hh_mm[6];
  char ss[3];
  char temp[10];

  DateTime now = DateTime(current_timezone.toLocal((rtc.now()).unixtime()));

  sprintf(hh_mm, "%02d%c%02d", now.hour(), ((now.second() % 2) ? ':' : ' '), now.minute());
  sprintf(ss, "%02d", now.second());
  sprintf(temp, "%2.1f C°", bme.readTemperature());

  matrix.setZone(0, 7, 7);
  matrix.setZone(1, 4, 6);
  matrix.setZone(2, 0, 3);

  matrix.setZoneEffect(0, 1, PA_FLIP_UD);
  matrix.setZoneEffect(1, 1, PA_FLIP_UD);
  matrix.setZoneEffect(0, 1, PA_FLIP_LR);
  matrix.setZoneEffect(1, 1, PA_FLIP_LR);

  matrix.setFont(0, small_num);
  matrix.setFont(1, pixel_font);
  matrix.setFont(2, pixel_font);

  if(matrix.displayAnimate()) {
    matrix.displayZoneText(0, ss, PA_CENTER, 75, 0, PA_PRINT, PA_NO_EFFECT);
    matrix.displayZoneText(1, hh_mm, PA_CENTER, 75, 0, PA_PRINT, PA_NO_EFFECT);
    matrix.displayZoneText(2, temp, PA_CENTER, 75, 0, PA_PRINT, PA_NO_EFFECT);

    matrix.displayReset(0);
    matrix.displayReset(1);
    matrix.displayReset(2);
  }
}

void print_screen_2() {
  /**
   * @brief
   */

  char ddd_dd[7];
  char mmm_yyyy[9];

  DateTime now = DateTime(current_timezone.toLocal((rtc.now()).unixtime()));

  sprintf(ddd_dd, "%s %02d", days[now.dayOfTheWeek()], now.day());
  sprintf(mmm_yyyy, "%s %d", months[now.month() - 1], now.year());

  matrix.setZone(3, 4, 7);
  matrix.setZone(4, 0, 3);

  matrix.setZoneEffect(3, 1, PA_FLIP_UD);
  matrix.setZoneEffect(3, 1, PA_FLIP_LR);

  matrix.setFont(3, small_num);
  matrix.setFont(4, small_num);

  if(matrix.displayAnimate()) {
    matrix.displayZoneText(3, ddd_dd, PA_CENTER, 75, 0, PA_PRINT, PA_NO_EFFECT);
    matrix.displayZoneText(4, mmm_yyyy, PA_CENTER, 75, 0, PA_PRINT, PA_NO_EFFECT);

    matrix.displayReset(3);
    matrix.displayReset(4);
  }
}

void print_screen_3() {
  /**
   * @brief
   */

  char hum[8];
  char pres[8];

  sprintf(hum, "H%3.1f%%", bme.readHumidity());
  sprintf(pres, "P%5.1f", bme.readPressure() / 100.0F);

  matrix.setZone(5, 4, 7);
  matrix.setZone(6, 0, 3);

  matrix.setZoneEffect(5, 1, PA_FLIP_UD);
  matrix.setZoneEffect(5, 1, PA_FLIP_LR);

  matrix.setFont(5, pixel_font);
  matrix.setFont(6, pixel_font);

  if(matrix.displayAnimate()) {
    matrix.displayZoneText(5, hum, PA_CENTER, 75, 0, PA_PRINT, PA_NO_EFFECT);
    matrix.displayZoneText(6, pres, PA_CENTER, 75, 0, PA_PRINT, PA_NO_EFFECT);

    matrix.displayReset(5);
    matrix.displayReset(6);
  }
}

void set_intensity() {
  /**
   * @brief
   * 
   */
  if(lux.measurementReady())
    matrix.setIntensity(int(round(lux.readLightLevel())) % 16);
}

void loop()
{
  print_screen_1();
  set_intensity();
  delay(50);
}