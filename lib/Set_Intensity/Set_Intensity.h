#ifndef SET_INTENSITY_H
#define SET_INTENSITY_H

#include <BH1750.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>

extern BH1750 light_sensor;
extern MD_Parola matrix;

void set_intensity();

#endif