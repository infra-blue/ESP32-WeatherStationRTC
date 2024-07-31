#include <Arduino.h>
#include <RTClib.h>
#include <WiFi.h>
#include <NTPClient.h>

#include "Set_NTP_Time.h"

void set_NTP_time() {
  /**
   * @brief SET NTP TIME
   * tries to sync the RTC time with NTP server
   * if it finds an open WiFi AP
   */

  WiFiUDP ntpUDP;
  NTPClient timeClient(ntpUDP, conf.ntpServer);

  WiFi.mode(WIFI_STA);
  uint8_t n_net = WiFi.scanNetworks();
  bool open_ap_found = false;
  char ssid[256];
  if (n_net) {
    Serial.println("Network found!\n");
    for (uint8_t i = 0; i < n_net; ++i)
      if(WiFi.encryptionType(i) == WIFI_AUTH_OPEN) {
        strcpy(ssid, WiFi.SSID(i).c_str());
        open_ap_found = true;
        break;
      }
  }
  else
    Serial.println("No network found.\n");

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
