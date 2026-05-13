const int PIN_LDR = 35;
const int PIN_LED = 26;
const int UMBRAL = 100;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  int ldr = analogRead(PIN_LDR);
  bool oscuro = ldr < UMBRAL;

  digitalWrite(PIN_LED, oscuro ? HIGH : LOW);
  Serial.print("LDR: ");
  Serial.print(ldr);
  Serial.println(oscuro ? " — LED ON" : " — LED OFF");

  delay(500);
}
