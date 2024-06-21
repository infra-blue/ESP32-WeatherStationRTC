#pragma once

#include <MD_Parola.h>
#include <RTClib.h>
#include <Font_Data.h>
#include <Local_Time.h>


/**
 * @brief
 * sets the intensity of the matrix display to a value between 0 and 15
 * based on the BH1750 sensor value
 */

void auto_set_intensity(MD_Parola matrix);

/**
 * @brief All the screens are defined here
 */

void print_time(MD_Parola matrix, RTC_DS3231 rtc) {
  /**
  * @brief
  *  picks up the current time from RTC (which is in DateTime class)
  *  converts it to epochtime
  *  then to local time and then to DateTime class
  *  then prints the time on the matrix display
  *  formatted as HH:MM:SS
  * 
  * @param matrix the matrix display object
  * @param rtc the RTC object
  */

  DateTime now = DateTime(current_timezone->toLocal((rtc.now()).unixtime()));

  char hh_mm[6], ss[3];

  sprintf(hh_mm, "%02d%c%02d", now.hour(), ((now.second() % 2) ? ':' : ' '), now.minute());
  sprintf(ss, "%02d", now.second());

  matrix.setZone(0, 0, 0);
  matrix.setZone(1, 1, 3);

  matrix.setFont(0, font[0]);
  matrix.setFont(1, font[1]);

  if(matrix.displayAnimate()) {
    matrix.displayZoneText(0, ss, PA_LEFT, 75, 0, PA_PRINT, PA_NO_EFFECT);
    matrix.displayZoneText(1, hh_mm, PA_CENTER, 75, 0, PA_PRINT, PA_NO_EFFECT);

    matrix.displayReset(0);
    matrix.displayReset(1);
  }
}

void print_date(MD_Parola matrix, RTC_DS3231 rtc);
void print_temp(MD_Parola matrix);
void print_hum(MD_Parola matrix);
void print_press(MD_Parola matrix);
void print_air_quality(MD_Parola matrix);