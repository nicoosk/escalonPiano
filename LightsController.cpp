#include "LightsController.h"
#include <Arduino.h>
#include "Config.h"

void initLights(){
    for (Sensor &sensor : sensors) {
        pinMode(sensor.ledPin, OUTPUT);
        digitalWrite(sensor.ledPin, LOW);
    }
    Serial.println("Inicialización de luces led completada con éxito.");
}

void turnOnLights(int index){
    for (Sensor &sensor : sensors) {
        if (&sensor - sensors == index) {
            digitalWrite(sensor.ledPin, HIGH);
            Serial.print("Sensor ");
            Serial.print(index);
            Serial.println(" activado.");
        }
    }
}

void turnOffLights(int index){
    for (Sensor &sensor : sensors) {
        if (&sensor - sensors == index) {
            digitalWrite(sensor.ledPin, LOW);
            Serial.print("Sensor ");
            Serial.print(index);
            Serial.println(" desactivado.");
        }
    }
}

void turnOffAllLights(){
    for (Sensor &sensor : sensors) {
        digitalWrite(sensor.ledPin, LOW);
    }
    Serial.println("Todos los sensores han sido desactivados.");
}