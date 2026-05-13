#include <ESP32Servo.h>

const int PIN_OPTOSWITCH = 14;
const int PIN_SERVO = 27;

Servo puerta;
bool puerta_abierta = false;
unsigned long tiempo_apertura = 0;
const unsigned long DURACION_APERTURA = 2000;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(PIN_OPTOSWITCH, INPUT);
  puerta.attach(PIN_SERVO);
  puerta.write(0);
  
  Serial.println("\n========================================");
  Serial.println("MODULO 3: ACCESO (OPTOSWITCH + SERVO)");
  Serial.println("========================================");
  Serial.println("Esperando deteccion...");
}

void loop() {
  int estado = digitalRead(PIN_OPTOSWITCH);
  
  if (estado == HIGH && !puerta_abierta) {
    Serial.println("PASO DETECTADO - Abriendo puerta");
    puerta.write(90);
    puerta_abierta = true;
    tiempo_apertura = millis();
  }
  
  if (puerta_abierta && (millis() - tiempo_apertura >= DURACION_APERTURA)) {
    Serial.println("Cerrando puerta");
    puerta.write(0);
    puerta_abierta = false;
  }
  
  delay(50);
}
