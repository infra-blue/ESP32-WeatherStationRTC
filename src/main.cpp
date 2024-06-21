#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>
#include <RTClib.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <Timezone.h>

#include <defines.h>
#include <Font_Data.h>
#include <Local_Time.h>

#include <Screens.h>

MD_Parola matrix = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
RTC_DS3231 rtc;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, INRIM);

void setup()
{
  Serial.begin(115200);

  if(!matrix.begin(8)) {
    Serial.printf("Error initializing MAX7219.\n");
    while(true);
  }

  if (!rtc.begin()) {
    Serial.printf("Could not find RTC! Check circuit.\n");
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

      while(WiFi.status() != WL_CONNECTED && WiFi.status() != WL_CONNECT_FAILED)
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

void loop()
{
  print_time(matrix, rtc);
}

/*
#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
*/

/*
  matrix.setZoneEffect(0, 1, PA_FLIP_UD);
  matrix.setZoneEffect(1, 1, PA_FLIP_UD);
  matrix.setZoneEffect(0, 1, PA_FLIP_LR);
  matrix.setZoneEffect(1, 1, PA_FLIP_LR);
*/