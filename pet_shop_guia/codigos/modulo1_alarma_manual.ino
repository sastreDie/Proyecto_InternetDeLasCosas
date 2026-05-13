const int PIN_BUTTON = 13;
const int PIN_BUZZER = 2;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
}

void loop() {
  bool presionado = digitalRead(PIN_BUTTON) == HIGH;
  if (presionado) {
    tone(PIN_BUZZER, 2500);  // tweak this number
  } else {
    noTone(PIN_BUZZER);
  }
}
