#ifndef SET_NTP_TIME_H
#define SET_NTP_TIME_H

#include <RTClib.h>
#include <NTPClient.h>

#include <Config_Parser.h>

extern Config conf;
extern RTC_DS3231 rtc;

void wifi_connetion();
void set_NTP_time();

#endif