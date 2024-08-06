#ifndef WEB_SETTINGS_H
#define WEB_SETTINGS_H

#define PATH_TO_HOME "/home.html"
#define PATH_TO_SETTINGS "/settings.html"

#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <WebServer.h>
#include <MD_Parola.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_BME280.h>
#include <RTClib.h>

#include <Config_Parser.h>
#include <Set_NTP_Time.h>
#include <Screens.h>

extern bool screen_off;
extern Config conf;
extern WebServer server;
extern MD_Parola* matrix;
extern Adafruit_BME280 bme;
extern RTC_DS3231 rtc;
extern DateTime current_time;
extern uint8_t displaySelector;

extern String HOME_HTML;
extern String SETTINGS_HTML;
String htmlLoader(const char* filename);

void handleHome();
void handleSettings();
void handleNetworkSubmit();
void handleNTPSubmit();
void handleLanguageSubmit();
void handleTimezoneSubmit();
void handleAdditionalSubmit();
void handleTimeTempScreen();
void handleDateScreen();
void handleHumPresScreen();
void handleToggleScreen();
void handleReboot();
void handleUpdateTime();

#endif
