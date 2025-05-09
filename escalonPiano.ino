#include "Config.h"
#include "SensorManager.h"
#include "LightsController.h"
#include "MelodyPlayer.h"

int lastDetectionTime = 0;
unsigned long previousMillis = 0;
bool sensorWasActive = false;

void setup(){
  Serial.begin(9600);
  initSensors();
  initLights();
  initMelodyPlayer();
  Serial.println("Sistema inicializado con éxito.");
}

void loop(){
  updateSensorStates();
  int sensorIndex = getActiveSensorIndex();
  
  if (sensorIndex != -1){
    lastDetectionTime = millis();

    if (!sensorWasActive) {
      if (millis() - previousMillis < PART_INTERVAL) {
        return;
      }
      int distance = sensors[sensorIndex].lastDistance;
      playSongPart(getSongPart(), distance, sensorIndex);
      incrementSongPart();
      previousMillis = millis();
    }
    sensorWasActive = true;
  } else {
    sensorWasActive = false;
  }

  int millis2 = millis();
  if (millis2 - lastDetectionTime > RESET_INTERVAL) {
    resetSystem();
    Serial.println(lastDetectionTime);
    Serial.println(millis2);
    Serial.println("Resultado variables: ");
    Serial.print(millis2 - lastDetectionTime); 
    //Serial.println("Canción reiniciada por inactividad.");
  }
}

void resetSystem() {
  resetSensors();
  turnOffAllLights();
  resetMelody();
  lastDetectionTime = millis();
  previousMillis = millis();
  sensorWasActive = false;
}