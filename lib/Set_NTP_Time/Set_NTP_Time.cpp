#include <Arduino.h>
#include <RTClib.h>
#include <WiFi.h>
#include <NTPClient.h>

#include "Set_NTP_Time.h"

void wifi_connetion() {
  /**
   * @brief WIFI CONNECTION
   * 
   * tries to connect to a wifi network
   * if no network is set, it tries to connect to an open access point
   */

  uint8_t n_net = WiFi.scanNetworks();

  if(strcmp(conf.wifi.SSID, "") == 0) {
    bool open_ap_found = false;
    char SSID[256];

    if (n_net) {
      for (uint8_t i = 0; i < n_net; ++i)
        if(WiFi.encryptionType(i) == WIFI_AUTH_OPEN) {
          strlcpy(SSID, WiFi.SSID(i).c_str(), sizeof(SSID));
          open_ap_found = true;
          break;
        }
    }
    else
      Serial.println("No network found.\n");

    if(open_ap_found) {
      WiFi.begin(SSID);
      Serial.printf("Connecting to %s ", SSID);
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

  while(WiFi.status() != WL_CONNECTED && WiFi.status() != WL_CONNECT_FAILED) {
    Serial.print(".");
    delay(100);
  }

  if(WiFi.status() != WL_CONNECT_FAILED) {
    Serial.printf("\nConnected to %s.\n", conf.wifi.SSID);
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else
    Serial.printf("\nError connecting to %s.\n", conf.wifi.SSID);
}

void set_NTP_time() {
  /**
   * @brief SET NTP TIME
   * tries to sync the RTC time with NTP server
  */

  WiFiUDP ntpUDP;
  NTPClient timeClient(ntpUDP, conf.ntpServer);

  timeClient.begin();
  delay(50);
  timeClient.update();
  delay(500);

  if(timeClient.isTimeSet()) {
    rtc.adjust(timeClient.getEpochTime());
    Serial.println("RTC adjusted with NTP time.\n");
  }
  else {
    Serial.println("NTP server error. Time not set.\n");
    rtc.adjust(DateTime(uint32_t(0)));
  }
}
