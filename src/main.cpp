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

    Serial.println("Scan start.\n");

    int n_net = WiFi.scanNetworks();
    bool ap_found = false;
  
    if (n_net) {
        for (int i = 0; i < n_net; ++i) {
          Serial.println(WiFi.SSID(i));
          if(WiFi.SSID(i) == YOUR_SSID) {
            ap_found = true;
            break;
          }
        }
    }

    Serial.println("AP found.\n");

    if(ap_found) {
      WiFi.begin(YOUR_SSID, YOUR_PASSWORD);

      Serial.printf("Connecting to WiFi.\n");

      while(WiFi.status() != WL_CONNECTED && WiFi.status() != WL_CONNECT_FAILED)
        delay(100);

      Serial.printf("Connected to %s.\n", YOUR_SSID);

      timeClient.begin();
      delay(50);
      timeClient.update();
      delay(500);

      if(timeClient.isTimeSet())
        rtc.adjust(timeClient.getEpochTime());

      WiFi.disconnect();

      Serial.printf("RTC adjusted with NTP time.\n Disconnecting from WiFi.\n");
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
  /**
   * @brief
   *  picks up the current time from RTC (which is in DateTime class)
   *  converts it to epochtime
   *  then to local time and then to DateTime class
   * 
   * @param DateTime
   */
  DateTime now = DateTime(current_timezone->toLocal((rtc.now()).unixtime()));

  char hh_mm[6], ss[3];

  sprintf(hh_mm, "%02d%c%02d", now.hour(), ((now.second() % 2) ? ':' : ' '), now.minute());
  sprintf(ss, "%02d", now.second());

  matrix.setZone(0, 0, 0);
  matrix.setZone(1, 1, 3);

  matrix.setFont(0, font[0]);
  matrix.setFont(1, font[1]);

  if(matrix.displayAnimate()) {
    matrix.displayZoneText(0, ss, PA_LEFT, 75, 0, PA_PRINT, PA_NO_EFFECT);
    matrix.displayZoneText(1, hh_mm, PA_CENTER, 75, 0, PA_PRINT, PA_NO_EFFECT);

    matrix.displayReset(0);
    matrix.displayReset(1);
  }
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