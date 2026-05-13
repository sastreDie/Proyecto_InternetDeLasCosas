const int PIN_LM35 = 34;
const int PIN_MOTOR = 25;

const float UMBRAL_ALTA = 28.0;
const float UMBRAL_BAJA = 26.0;

unsigned long ultimo_lectura = 0;
const unsigned long INTERVALO_LECTURA = 1000;

bool motor_encendido = false;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(PIN_MOTOR, OUTPUT);
  digitalWrite(PIN_MOTOR, LOW);
  analogReadResolution(12);
  
  Serial.println("\n========================================");
  Serial.println("MODULO 4: CLIMA (LM35 + MOTOR)");
  Serial.println("========================================");
}

void loop() {
  unsigned long tiempo = millis();
  
  if (tiempo - ultimo_lectura >= INTERVALO_LECTURA) {
    ultimo_lectura = tiempo;
    
    int adc = analogRead(PIN_LM35);
    float voltaje = (adc / 4095.0) * 3.3;
    float temperatura = voltaje * 100.0;
    
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.print("C - ");
    
    if (temperatura > UMBRAL_ALTA && !motor_encendido) {
      digitalWrite(PIN_MOTOR, HIGH);
      motor_encendido = true;
      Serial.println("MOTOR ON");
    } else if (temperatura < UMBRAL_BAJA && motor_encendido) {
      digitalWrite(PIN_MOTOR, LOW);
      motor_encendido = false;
      Serial.println("MOTOR OFF");
    } else {
      Serial.println(motor_encendido ? "MOTOR ON" : "MOTOR OFF");
    }
  }
  
  delay(50);
}
