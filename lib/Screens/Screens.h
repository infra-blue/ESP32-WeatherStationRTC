#ifndef SCREENS_H
#define SCREENS_H

#include <RTClib.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include <unordered_map>
#include <vector>
#include <string>

extern MD_Parola matrix;
extern RTC_DS3231 rtc;
extern Adafruit_BME280 bme;
extern DateTime current_time;

extern std::unordered_map<std::string, std::vector<std::string>> months;
extern std::unordered_map<std::string, std::vector<std::string>> days;

enum screen{
  CLOCK_TEMP,
  DATE,
  HUMIDITY_PRESSURE
};

void print_time_temp();
void print_date();
void print_hum_pres();

#endif
