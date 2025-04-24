#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

#define NUM_SENSORS 3

// Rangos validos de detección
const int MIN_DETETION_DISTANCE = 5;
const int MAX_DETETION_DISTANCE = 120;

// Tiempos del sistema (milis)
const unsigned long PART_INTERVAL = 1000;
const unsigned long RESET_INTERVAL = 15000;

// Buzzer
const int BUZZER_PIN = 3;

// Partes totales de la canción
const int TOTAL_PARTS = 6;

// Esta es la estructura del sensor. Representa al sensor ultrasónico con su propio led
struct Sensor {
  int trigPin;
  int echoPin;
  int ledPin;
  long lastDistance;
  bool isActive;

  Sensor(int t, int e, int l) :
    trigPin(t), echoPin(e), ledPin(l), lastDistance(0), isActive(false) {}
};

extern Sensor sensors[NUM_SENSORS];

#endif 
