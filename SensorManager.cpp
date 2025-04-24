#include "SensorManager.h"
#include <Arduino.h>
#include "Config.h"

Sensor sensors[NUM_SENSORS] = {
    {7, 6, 12}, // Sensor 1
    {5, 4, 11}, // Sensor 2
    {8, 9, 10}  // Sensor 3
};

void initSensors() {
    for (Sensor &sensor : sensors) {
        pinMode(sensor.trigPin, OUTPUT);
        pinMode(sensor.echoPin, INPUT);
        pinMode(sensor.ledPin, OUTPUT);
        digitalWrite(sensor.ledPin, LOW);
    }
    Serial.println("Inicialización de sensores completado con éxito.");
}

void updateSensorStates(){
    for (Sensor &sensor : sensors) {
        digitalWrite(sensor.trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(sensor.trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(sensor.trigPin, LOW);

        long duration = pulseIn(sensor.echoPin, HIGH);
        sensor.lastDistance = duration * 0.344 / 2;

        sensor.isActive = (sensor.lastDistance >= MIN_DETETION_DISTANCE && sensor.lastDistance <= MAX_DETETION_DISTANCE);
    }
}

int getActiveSensorIndex(){
    for (Sensor &sensor : sensors) {
        if (sensor.isActive) {
            return &sensor - sensors;
        }
    }

    return -1;
}

void resetSensors(){
    for (Sensor &sensor : sensors) {
        sensor.isActive = false;
        sensor.lastDistance = 0;
    }
}