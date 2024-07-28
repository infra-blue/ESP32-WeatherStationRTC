#include <Arduino.h>
#include <RTClib.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include "Screens.h"

void print_time_temp(DateTime now) {
  /**
  * @brief TIME AND TEMPERATURE
  *  picks up the current time from RTC (which is in DateTime class)
  *  converts it to epochtime
  *  then to local time
  *  then prints the time on the matrix display
  *  formatted as HH:MM SS
  * 
  *  then picks up the temperature from BME280 sensor
  *  and prints it on the matrix display
  * 
  *  the seconds are blinking every second
  * 
  *  a beep sound is generated every hour with the buzzer
  */

  char hh_mm[6];
  char ss[3];
  char temp[10];

  sprintf(hh_mm, "%02d%c%02d", now.hour(), ((now.second() % 2) ? ':' : ' '), now.minute());
  sprintf(ss, "%02d", now.second());
  sprintf(temp, "%3.1f °C", bme.readTemperature());

  //print time and temperature
  matrix.synchZoneStart();
  if(matrix.displayAnimate()) {
    matrix.displayZoneText(0, ss, PA_CENTER, 75, 0, PA_PRINT);
    matrix.displayZoneText(1, hh_mm, PA_CENTER, 75, 0, PA_PRINT);
    matrix.displayZoneText(2, temp, PA_CENTER, 75, 0, PA_PRINT);
  }
}

void print_date(DateTime now) {
  /**
  * @brief DATE
  * picks up the current time from RTC (which is in DateTime class)
  * converts it to epochtime
  * then to local time
  * then prints the date on the matrix display
  * formatted as DDD DD MMM YYYY
  */
  char ddd_dd[7];
  char mmm_yyyy[9];

  sprintf(ddd_dd, "%s %02d", days[now.dayOfTheWeek()], now.day());
  sprintf(mmm_yyyy, "%s %d", months[now.month() - 1], now.year());

  //print date
  matrix.synchZoneStart();
  if(matrix.displayAnimate()) {
    matrix.displayZoneText(3, ddd_dd, PA_CENTER, 75, 0, PA_PRINT);
    matrix.displayZoneText(4, mmm_yyyy, PA_CENTER, 75, 0, PA_PRINT);
  }
}

void print_hum_pres() {
  /**
  * @brief HUMIDITY AND PRESSURE
  * picks up the current humidity and pressure from BME280 sensor
  * then prints the humidity and pressure on the matrix display
  * formatted as HHH.H% and PPPP.P
  */

  char hum[9];
  char pres[9];

  if(bme.readHumidity() < 100.0)
    sprintf(hum, "H %3.1f%%", bme.readHumidity());
  else
    sprintf(hum, "H %3.0f%%", bme.readHumidity());

  if((bme.readPressure() / 100.0) < 1000.0)
    sprintf(pres, "P %4.1f", bme.readPressure() / 100.0);
  else
    sprintf(pres, "P%5.1f", bme.readPressure() / 100.0);

  //print humidity and pressure
  matrix.synchZoneStart();
  if(matrix.displayAnimate()) {
    matrix.displayZoneText(5, hum, PA_RIGHT, 75, 0, PA_PRINT);
    matrix.displayZoneText(6, pres, PA_LEFT, 75, 0, PA_PRINT);
  }
}
