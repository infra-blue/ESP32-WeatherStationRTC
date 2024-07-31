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

  WiFi.begin(conf.wifi.SSID, conf.wifi.PASSWORD);
  Serial.printf("Connecting to %s ", conf.wifi.SSID);

  while(WiFi.status() != WL_CONNECTED && WiFi.status() != WL_CONNECT_FAILED)
    delay(100);

  if(WiFi.status() == WL_CONNECT_FAILED)
    Serial.printf("\nError connecting to %s.\n", conf.wifi.SSID);

  Serial.printf("\nConnected to %s.\n", conf.wifi.SSID);

  timeClient.begin();
  delay(50);
  timeClient.update();
  delay(500);

  if(timeClient.isTimeSet()) {
    rtc.adjust(timeClient.getEpochTime());
    Serial.printf("RTC adjusted with NTP time.\nDisconnecting from %s.\n", conf.wifi.SSID);
  }
  else {
    Serial.printf("NTP server error. Time not set.\n");
    rtc.adjust(DateTime("Jan 1 1970", "00:00:00"));
  }

  WiFi.disconnect();
}
