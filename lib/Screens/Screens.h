#ifndef SCREENS_H
#define SCREENS_H

#include <RTClib.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

extern MD_Parola matrix;
extern RTC_DS3231 rtc;
extern Adafruit_BME280 bme;

extern char days[7][4];
extern char months[12][4];

enum screen{
  CLOCK_TEMP,
  DATE,
  HUMIDITY_PRESSURE
};

void print_time_temp(DateTime now);
void print_date(DateTime now);
void print_hum_pres();

#endif
