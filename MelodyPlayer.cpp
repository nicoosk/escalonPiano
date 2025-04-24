#include "MelodyPlayer.h"
#include <Arduino.h>
#include "LighstController.h"
#include "Config.h"

int songPart = 0;


void initMelodyPlayer() {
    pinMode(BUZZER_PIN, OUTPUT);
    Serial.println("Inicialización del buzzer completada con éxito.");
}

void playSongPart(int part, int distance, int sensorIndex) {
    bool higherOctave = (distance > 60);
    int note = 0;

    switch (part) {
        case 0:
            note = higherOctave ? DO5 : DO4;
            break;
        case 1:
            note = higherOctave ? RE5 : RE4;
            break;
        case 2:
            note = higherOctave ? MI5 : MI4;
            break;
        case 3:
            note = higherOctave ? FA5 : FA4;
            break;
        case 4:
            note = higherOctave ? SOL5 : SOL4;
            break;
        case 5:
            note = higherOctave ? LA5 : LA4;
            break;
        default:
            noTone(BUZZER_PIN);
            return;
    }

    tone(BUZZER_PIN, note, 1000);
    turnOnLights(sensorIndex);
    delay(1000);
    noTone(BUZZER_PIN);
    turnOffLights(sensorIndex);
}

void resetMelody() {
    songPart = 0;
}

int getSongPart() {
    return songPart;
}

void incrementSongPart(){
    songPart = (songPart + 1) % TOTAL_PARTS;
    Serial.print("Parte de la canción incrementada a: ");
    Serial.println(songPart);
}