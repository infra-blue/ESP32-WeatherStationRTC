#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>
#include <RTClib.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <Timezone.h>
#include "Font_Data.h"

#define CLK_PIN   12
#define DATA_PIN  11
#define CS_PIN    10

#define MAX_DEVICES 4
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

char ssid[] = "clock";
char password[] = "coglione1";

MD_Parola matrix = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
RTC_DS3231 rtc;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org");

TimeChangeRule CET = {"CET", Last, Sun, Oct, 3, 60};    // Daylight time = UTC + 1 hour
TimeChangeRule CEST = {"CEST", Last, Sun, Mar, 2, 120};     // Standard time = UTC + 2 hours
Timezone CE(CET, CEST);

void setup()
{
  Serial.begin(9600);
  if(!matrix.begin(3)) {
    Serial.printf("Error initializing MAX7219.\n");
    while(true);
  }

  if (!rtc.begin()) {
    Serial.println("Could not find RTC! Check circuit.\n");
    while(true);
  }

  if (rtc.lostPower()) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(100);
    }
    timeClient.begin();
    delay(50);
    timeClient.update();
    delay(500);

    if(timeClient.isTimeSet()) {
      time_t now = CE.toLocal(timeClient.getEpochTime());
      rtc.adjust(DateTime(now));
      Serial.print("Time Update.\n");
    }
  }

  matrix.setIntensity(10);
  Serial.printf("%02d/%02d/%d\n%02d:%02d:%02d", (rtc.now()).day(), (rtc.now()).month(), (rtc.now()).year(), (rtc.now()).hour(), (rtc.now()).minute(), (rtc.now()).second());
}
 
void loop() 
{
  char hh_mm[] = "00:00";
  char ss[] = "00";

  matrix.setZone(0, 0, 0);
  matrix.setZone(1, 1, 3);

  matrix.setFont(0, small_num);
  matrix.setFont(1, pixel_font);

  matrix.displayZoneText(0, ss, PA_LEFT, 75, 0, PA_PRINT, PA_NO_EFFECT);
  matrix.displayZoneText(1, hh_mm, PA_CENTER, 75, 0, PA_PRINT, PA_NO_EFFECT);
  
  sprintf(hh_mm, "%02d%c%02d ", (rtc.now()).hour(), (((rtc.now()).second() % 2) ? ':' : ' '), (rtc.now()).minute());
  sprintf(ss, "%02d", (rtc.now()).second());

  matrix.displayAnimate();
  matrix.displayReset(0);
  matrix.displayReset(1);
}