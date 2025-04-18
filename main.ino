// Pin del buzzer
const int buzzerPin = 3;

// Pines de los sensores ultrasónicos
const int trigPin1 = 7;
const int echoPin1 = 6;
const int trigPin2 = 5;
const int echoPin2 = 4;
const int trigPin3 = 8;
const int echoPin3 = 9;

// Pines de los leds (cada pin corresponde a un escalón)
const int led1 = 10;
const int led2 = 11;
const int led3 = 12;

// Variables de distancia
long distance1, distance2, distance3;

// Estado previo del sensor
bool sensorWasActive = false;

// Progreso de la canción
int songPart = 0;
const int totalParts = 6;

// Tiempos
unsigned long previousMillis = 0;
const long partInterval = 1000;
unsigned long lastDetectionTime = 0;
const long resetInterval = 15000;

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

int sensorTriggered = 0;

void setup() {
  pinMode(buzzerPin, OUTPUT);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  Serial.begin(9600);
  Serial.println("Iniciando canción global...");
}

void loop() {
  distance1 = measureDistance(trigPin1, echoPin1);
  distance2 = measureDistance(trigPin2, echoPin2);
  distance3 = measureDistance(trigPin3, echoPin3);
  if (distance1 >= 5 && distance1 <= 120) sensorTriggered = 1;
  else if (distance2 >= 5 && distance2 <= 120) sensorTriggered = 2;
  else if (distance3 >= 5 && distance3 <= 120) sensorTriggered = 3;


  bool sensorActive = (sensorTriggered != 0);

  Serial.print("Sensor 1: ");
  Serial.print(distance1);
  Serial.print(" cm, Sensor 2: ");
  Serial.print(distance2);
  Serial.print(" cm, Sensor 3: ");
  Serial.print(distance3);
  Serial.print(" cm - Detección: ");
  Serial.println(sensorActive ? "SI" : "NO");

  if (sensorActive) {
    lastDetectionTime = millis();
  }

  if (sensorActive && !sensorWasActive) {
    Serial.println("Botón de play activado. Reproduciendo parte de la canción...");
    int distance = min(min(distance1, distance2), distance3); // Tomamos la menor para evitar falsos positivos de fondo
    playSongPart(songPart, distance);
    songPart = (songPart + 1) % totalParts;
    previousMillis = millis();
  }

  sensorWasActive = sensorActive;

  if (sensorActive && (millis() - previousMillis >= partInterval)) {
    previousMillis = millis();
  }

  if (millis() - lastDetectionTime >= resetInterval) {
    if (songPart != 0) {
      songPart = 0;
      Serial.println("15 segundos sin detección. Reiniciando canción.");
    }
  }

  sensorTriggered = 0;
  delay(100);

}

// 🎯 FUNCIONES

long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.0344 / 2;
}

void playSongPart(int part, int distance) {
  Serial.print("Reproduciendo parte ");
  Serial.print(part + 1);
  Serial.print(" - Distancia: ");
  Serial.println(distance);

  bool octavaAlta = (distance > 60); // Octava 2 si supera 60 cm

  int note = 0;
  switch (part) {
    case 0: note = octavaAlta ? DO5 : DO4; break;
    case 1: note = octavaAlta ? RE5 : RE4; break;
    case 2: note = octavaAlta ? MI5 : MI4; break;
    case 3: note = octavaAlta ? FA5 : FA4; break;
    case 4: note = octavaAlta ? SOL5 : SOL4; break;
    case 5: note = octavaAlta ? LA5 : LA4; break;
    default: noTone(buzzerPin); return;
  }

  tone(buzzerPin, note, 1000);
  lightsUp(sensorTriggered);
  delay(1000);
  noTone(buzzerPin);
  lightsOff(sensorTriggered);
  Serial.println("Parte reproducida y detenida.");
}

void lightsUp(int step){
  switch (step) {
    case 1: handleLightSwitch(led1, true); break;
    case 2: handleLightSwitch(led2, true); break;
    case 3: handleLightSwitch(led3, true); break;
    default: lightsOff(led1); lightsOff(led2); lightsOff(led3);
  }
}

void handleLightSwitch(int pin, bool turnOn){
  if (turnOn){
    lightsOff(pin);
    delayMicroseconds(100);
    digitalWrite(pin, HIGH);
    return;
  }

  digitalWrite(pin, LOW);
}

void lightsOff(int step){
  switch (step){
    case 1: handleLightSwitch(led1, false); break;
    case 2: handleLightSwitch(led2, false); break;
    case 3: handleLightSwitch(led3, false); break;
  }
}