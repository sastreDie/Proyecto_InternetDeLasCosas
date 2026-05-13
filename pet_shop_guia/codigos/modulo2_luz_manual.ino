const int PIN_LDR = 35;
const int PIN_LED = 32;
const int UMBRAL_OSCURIDAD = 2000;

unsigned long ultimo_tiempo_lectura = 0;
const unsigned long INTERVALO_LECTURA = 500;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(PIN_LED, OUTPUT);
  analogReadResolution(12);
  digitalWrite(PIN_LED, LOW);
  
  Serial.println("\n========================================");
  Serial.println("MODULO 2: LUZ (LDR + LED)");
  Serial.println("========================================");
}

void loop() {
  unsigned long tiempo_actual = millis();
  
  if (tiempo_actual - ultimo_tiempo_lectura >= INTERVALO_LECTURA) {
    ultimo_tiempo_lectura = tiempo_actual;
    
    int valor_ldr = analogRead(PIN_LDR);
    
    Serial.print("LDR: ");
    Serial.print(valor_ldr);
    
    if (valor_ldr > UMBRAL_OSCURIDAD) {
      int brillo = map(valor_ldr, UMBRAL_OSCURIDAD, 4095, 100, 255);
      analogWrite(PIN_LED, brillo);
      Serial.print(" (OSCURO) - LED ON brillo: ");
      Serial.println(brillo);
    } else {
      analogWrite(PIN_LED, 0);
      Serial.println(" (LUZ) - LED OFF");
    }
  }
  
  delay(50);
}
