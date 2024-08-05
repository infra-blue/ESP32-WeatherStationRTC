#include <Arduino.h>
#include <BH1750.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>

#include "Set_Intensity.h"

void set_intensity() {
  if(light_sensor.measurementReady())
    matrix->setIntensity(map(constrain(round(light_sensor.readLightLevel()), 0, 300), 0, 300, 0, 15));
}
