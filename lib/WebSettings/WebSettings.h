#ifndef WEBSETTINGS_H
#define WEBSETTINGS_H

#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <WebServer.h>
#include <MD_Parola.h>

#include <Config_Parser.h>
#include <Set_NTP_Time.h>

extern bool screen_off;
extern Config conf;
extern WebServer server;
extern MD_Parola* matrix;

void handleRoot();
void handleNetworkSubmit();
void handleNTPSubmit();
void handleLanguageSubmit();
void handleTimezoneSubmit();
void handleAdditionalSubmit();
void handleToggleScreen();
void handleUpdateTime();

#endif