#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H
#include <Arduino.h>
#include "Config.h"

void initSensors();

void updateSensorStates();

int getActiveSensorIndex();

void resetSensors();

#endif