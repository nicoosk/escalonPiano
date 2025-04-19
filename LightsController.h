#ifndef LIGHTS_CONTROLLER_H
#define LIGHTS_CONTROLLER_H
#include <Arduino.h>

void initLights();

void turnOnLights(int index);

void turnOffLights(int index);

void turnOffAllLights();

#endif