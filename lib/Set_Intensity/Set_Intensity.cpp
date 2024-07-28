#include <Arduino.h>
#include <BH1750.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>

#include "Set_Intensity.h"

void set_intensity() {
  /**
  * @brief AUTO SET INTENSITY
  * picks up the current light level from BH1750 sensor
  * then sets the intensity of the matrix display
  * based on the light level
  * mapped from to 0 to 15 (max level limited to 300 for more sensitivity)
  */
  if(light_sensor.measurementReady())
    matrix.setIntensity(map(constrain(round(light_sensor.readLightLevel()), 0, 300), 0, 300, 0, 15));
}
