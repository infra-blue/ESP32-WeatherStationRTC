#include <Arduino.h>
#include <RTClib.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include <Languages.h>
#include <Config_Parser.h>

#include "Screens.h"

void print_time_temp() {
  char hh_mm[6];
  char ss[3];
  char temp[10];

  sprintf(hh_mm, "%02d%c%02d", current_time.hour(), ((current_time.second() % 2) ? ':' : ' '), current_time.minute());
  sprintf(ss, "%02d", current_time.second());

  if(!conf.fahrenheit)
    sprintf(temp, "%3.1f °C", bme.readTemperature());
  else
    sprintf(temp, "%3.1f °F", (bme.readTemperature() * (9.0 / 5.0)) + 32.0);

  matrix->synchZoneStart();
  if(matrix->displayAnimate()) {
    matrix->displayZoneText(0, ss, PA_CENTER, 75, 0, PA_PRINT);
    matrix->displayZoneText(1, hh_mm, PA_CENTER, 75, 0, PA_PRINT);
    matrix->displayZoneText(2, temp, PA_CENTER, 75, 0, PA_PRINT);
  }
}

void print_date() {
  char ddd_dd[7];
  char mmm_yyyy[9];

  sprintf(ddd_dd, "%s %02d", days[std::string(conf.language)][current_time.dayOfTheWeek()], current_time.day());
  sprintf(mmm_yyyy, "%s %d", months[std::string(conf.language)][current_time.month() - 1], current_time.year());

  matrix->synchZoneStart();
  if(matrix->displayAnimate()) {
    matrix->displayZoneText(3, ddd_dd, PA_CENTER, 75, 0, PA_PRINT);
    matrix->displayZoneText(4, mmm_yyyy, PA_CENTER, 75, 0, PA_PRINT);
  }
}

void print_hum_pres() {
  char hum[9];
  char pres[9];

  if(bme.readHumidity() < 100.0)
    sprintf(hum, "H %3.1f%%", bme.readHumidity());
  else
    sprintf(hum, "H %3.0f%%", bme.readHumidity());

  if((bme.readPressure() / 100.0) > 1000.0)
    sprintf(pres, "P%5.1f", bme.readPressure() / 100.0);
  else
    sprintf(pres, "P %4.1f", bme.readPressure() / 100.0);

  //print humidity and pressure
  matrix->synchZoneStart();
  if(matrix->displayAnimate()) {
    matrix->displayZoneText(5, hum, PA_RIGHT, 75, 0, PA_PRINT);
    matrix->displayZoneText(6, pres, PA_LEFT, 75, 0, PA_PRINT);
  }
}
