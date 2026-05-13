const int PIN_BUTTON = 13;
const int PIN_BUZZER = 2;

unsigned long ultimo_tiempo_lectura = 0;
const unsigned long INTERVALO_DEBOUNCE = 100;
bool boton_presionado_anterior = false;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);
  
  Serial.println("\n========================================");
  Serial.println("MODULO 1: ALARMA (BOTON + BUZZER)");
  Serial.println("========================================");
  Serial.println("Sistema iniciado - Esperando boton...");
}

void loop() {
  unsigned long tiempo_actual = millis();
  
  if (tiempo_actual - ultimo_tiempo_lectura >= INTERVALO_DEBOUNCE) {
    ultimo_tiempo_lectura = tiempo_actual;
    
    int estado_boton = digitalRead(PIN_BUTTON);
    
    if (estado_boton == HIGH && boton_presionado_anterior == false) {
      Serial.println("BOTON PRESIONADO!");
      digitalWrite(PIN_BUZZER, HIGH);
      delay(500);
      digitalWrite(PIN_BUZZER, LOW);
      Serial.println("Alarma desactivada");
    }
    
    boton_presionado_anterior = (estado_boton == HIGH);
  }
  
  delay(50);
}
