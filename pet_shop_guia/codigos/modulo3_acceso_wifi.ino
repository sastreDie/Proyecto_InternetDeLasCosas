#include <ESP32Servo.h>
#include <WiFi.h>

// ── WiFi ──
const char* ssid     = "wifidie";
const char* password = "pito1234";
WiFiServer server(80);

// ── Pines ──
const int PIN_BUTTON = 13;
const int PIN_BUZZER = 2;
const int PIN_LDR    = 34;
const int PIN_LED    = 26;
const int PIN_OPTO   = 33;
const int PIN_SERVO  = 18;

// ── Config ──
const int UMBRAL_LDR = 100;

// ── Servo ──
Servo servo;
bool abierto = false;
unsigned long tiempo_apertura = 0;

// ── Buzzer web ──
bool buzzer_web = false;
unsigned long tiempo_buzzer = 0;
const unsigned long DURACION_BUZZER = 1000;

String generarHTML(bool oscuro, bool abierto, int ldr) {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<meta http-equiv='refresh' content='2'>";
  html += "<title>Sistema</title>";
  html += "<style>body{font-family:Arial;text-align:center;background:#1a1a2e;padding:20px;color:white;}";
  html += ".box{background:#16213e;max-width:400px;margin:auto;padding:30px;border-radius:15px;}";
  html += "h1{color:#e94560;}";
  html += ".card{background:#0f3460;border-radius:10px;padding:15px;margin:10px 0;}";
  html += ".on{color:#4ecca3;} .off{color:#e94560;}";
  html += "button{padding:15px 30px;font-size:16px;border:none;border-radius:10px;cursor:pointer;width:100%;margin:5px 0;}";
  html += ".btn-red{background:#e94560;color:white;} .btn-green{background:#4ecca3;color:#1a1a2e;}";
  html += "</style></head><body><div class='box'>";
  html += "<h1>🏠 Sistema</h1>";

  // Estado LDR
  html += "<div class='card'><b>Luz</b><br>LDR: " + String(ldr) + "<br>";
  html += "LED: <span class='" + String(oscuro ? "on" : "off") + "'>" + String(oscuro ? "ON" : "OFF") + "</span></div>";

  // Estado servo
  html += "<div class='card'><b>Acceso</b><br>";
  html += "Puerta: <span class='" + String(abierto ? "on" : "off") + "'>" + String(abierto ? "ABIERTA" : "CERRADA") + "</span></div>";

  // Botones
  html += "<button class='btn-red' onclick=\"fetch('/BUZZER')\">🔔 Timbre</button>";
  html += "<button class='btn-green' onclick=\"fetch('/ABRIR')\">🚪 Abrir puerta</button>";

  html += "</div></body></html>";
  return html;
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_OPTO, INPUT_PULLUP);

  servo.attach(PIN_SERVO);
  servo.write(120);

  Serial.print("Conectando a WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  unsigned long ahora = millis();

  // ── Módulo 1: Timbre físico ──
  bool presionado = digitalRead(PIN_BUTTON) == HIGH;
  if (presionado) {
    tone(PIN_BUZZER, 2500);
  } else if (!buzzer_web) {
    noTone(PIN_BUZZER);
  }

  // ── Buzzer web ──
  if (buzzer_web) {
    tone(PIN_BUZZER, 2500);
    if (ahora - tiempo_buzzer >= DURACION_BUZZER) {
      noTone(PIN_BUZZER);
      buzzer_web = false;
    }
  }

  // ── Módulo 2: Luz ──
  int ldr = analogRead(PIN_LDR);
  bool oscuro = ldr < UMBRAL_LDR;
  digitalWrite(PIN_LED, oscuro ? HIGH : LOW);

  // ── Módulo 3: Acceso físico (opto) ──
  bool bloqueado = digitalRead(PIN_OPTO) == LOW;
  if (bloqueado && !abierto) {
    Serial.println("Opto — Abriendo");
    servo.write(40);
    delay(600);
    servo.write(40);
    abierto = true;
    tiempo_apertura = ahora;
  }
  if (abierto && (ahora - tiempo_apertura >= 3000)) {
    Serial.println("Cerrando");
    servo.write(120);
    delay(600);
    servo.write(120);
    abierto = false;
  }

  // ── Servidor web ──
  WiFiClient client = server.accept();
  if (client) {
    String peticion = client.readStringUntil('\r');
    Serial.println(peticion);

    if (peticion.indexOf("/BUZZER") > -1) {
      Serial.println("Timbre web!");
      buzzer_web = true;
      tiempo_buzzer = ahora;
    }

    if (peticion.indexOf("/ABRIR") > -1 && !abierto) {
      Serial.println("Abriendo web!");
      servo.write(40);
      delay(600);
      servo.write(40);
      abierto = true;
      tiempo_apertura = ahora;
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println(generarHTML(oscuro, abierto, ldr));
    client.stop();
  }

  delay(200);
}
