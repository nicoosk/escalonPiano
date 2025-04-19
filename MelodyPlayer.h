#ifndef MELODY_PLAYER_H
#define MELODY_PLAYER_H
#include <Arduino.h>
#include "Config.h"

// Notas octava 1
const int DO4 = 262;
const int RE4 = 294;
const int MI4 = 330;
const int FA4 = 349;
const int SOL4 = 392;
const int LA4 = 440;

// Notas octava 2
const int DO5 = 523;
const int RE5 = 587;
const int MI5 = 659;
const int FA5 = 698;
const int SOL5 = 784;
const int LA5 = 880;

// Progreso de la canción
extern int songPart;

void initMelodyPlayer();

void playSongPart(int part, int distance, int sensorIndex);

void resetMelody();

int getSongPart();

void incrementSongPart();

#endif