#include <Arduino.h>
#include <RTClib.h>
#include <WiFi.h>
#include <NTPClient.h>

#include "Set_NTP_Time.h"

void set_NTP_time() {
  /**
   * @brief SET NTP TIME
   * tries to sync the RTC time with NTP server
   */

  WiFiUDP ntpUDP;
  NTPClient timeClient(ntpUDP, conf.ntpServer);
  uint8_t n_net = WiFi.scanNetworks();

  char ssid[256];
  strlcpy(ssid, conf.wifi.SSID, sizeof(ssid));

  if(strcmp(conf.wifi.SSID, "") == 0) {
    bool open_ap_found = false;

    if (n_net) {
      Serial.println("Network found!\n");
      for (uint8_t i = 0; i < n_net; ++i)
        if(WiFi.encryptionType(i) == WIFI_AUTH_OPEN) {
          strlcpy(ssid, WiFi.SSID(i).c_str(), sizeof(ssid));
          open_ap_found = true;
          break;
        }
    }
    else
      Serial.println("No network found.\n");

    if(open_ap_found) {
      WiFi.begin(ssid);
      Serial.printf("Connecting to %s ", ssid);
    }
    else {
      Serial.println("No open network found.\n");
      return;
    }
  }
  else if((strcmp(conf.wifi.SSID, "") != 0) && (strcmp(conf.wifi.PASSWORD, "") == 0)) {
    WiFi.begin(conf.wifi.SSID);
    Serial.printf("Connecting to %s ", conf.wifi.SSID);
  }
  else {
    WiFi.begin(conf.wifi.SSID, conf.wifi.PASSWORD);
    Serial.printf("Connecting to %s ", conf.wifi.SSID);
  }

  while(WiFi.status() != WL_CONNECTED && WiFi.status() != WL_CONNECT_FAILED)
    delay(100);

  if(WiFi.status() == WL_CONNECT_FAILED)
    Serial.printf("\nError connecting to %s.\n", ssid);

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
