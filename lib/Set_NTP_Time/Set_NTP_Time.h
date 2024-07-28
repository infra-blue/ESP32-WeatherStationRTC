#ifndef SET_NTP_TIME_H
#define SET_NTP_TIME_H

#include <RTClib.h>
#include <NTPClient.h>

extern RTC_DS3231 rtc;
extern NTPClient timeClient;

void set_NTP_time();

#endif