#include <WiFi.h>

const char* ssid = "TU_WIFI";
const char* password = "TU_PASSWORD";

WiFiServer server(80);

const int PIN_BUTTON = 13;
const int PIN_BUZZER = 2;
const int PIN_LDR = 35;
const int PIN_LED = 32;
const int UMBRAL_OSCURIDAD = 2000;

int valor_ldr = 0;
String led_modo = "AUTO";
String led_estado = "OFF";

unsigned long ultimo_lectura_ldr = 0;
unsigned long ultimo_lectura_boton = 0;
bool boton_anterior = false;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  analogReadResolution(12);
  
  digitalWrite(PIN_BUZZER, LOW);
  digitalWrite(PIN_LED, LOW);
  
  Serial.println("\nMODULO 1+2: ALARMA + LUZ");
  Serial.print("Conectando WiFi");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nIP: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

String generarHTML() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<title>Pet Shop</title>";
  html += "<style>body{font-family:Arial;background:#667eea;padding:20px;margin:0;}";
  html += ".box{background:white;max-width:500px;margin:auto;padding:30px;border-radius:15px;}";
  html += "h1{color:#667eea;text-align:center;}h2{color:#764ba2;border-bottom:2px solid #667eea;padding-bottom:10px;}";
  html += ".info{background:#f0f4ff;padding:15px;margin:10px 0;border-radius:8px;border-left:4px solid #667eea;}";
  html += "button{padding:15px;font-size:16px;border:none;border-radius:8px;cursor:pointer;color:white;font-weight:bold;width:100%;margin:5px 0;}";
  html += ".btn-on{background:#4CAF50;}.btn-off{background:#f44336;}.btn-alarm{background:#ff5722;}.btn-auto{background:#2196F3;}";
  html += ".grid{display:grid;grid-template-columns:1fr 1fr;gap:10px;}</style></head><body>";
  html += "<div class='box'><h1>PET SHOP</h1>";
  
  html += "<h2>Sensores</h2>";
  html += "<div class='info'>Luz: " + String(valor_ldr) + "/4095</div>";
  
  html += "<h2>Alarma</h2>";
  html += "<button class='btn-alarm' onclick=\"f('/ALARM_ON')\">ACTIVAR ALARMA</button>";
  
  html += "<h2>LED - Modo: " + led_modo + " (" + led_estado + ")</h2>";
  html += "<div class='grid'>";
  html += "<button class='btn-on' onclick=\"f('/LED_ON')\">LED ON</button>";
  html += "<button class='btn-off' onclick=\"f('/LED_OFF')\">LED OFF</button>";
  html += "</div>";
  html += "<button class='btn-auto' onclick=\"f('/AUTO')\">VOLVER A AUTO</button>";
  
  html += "</div><script>function f(u){fetch(u).then(()=>location.reload());}</script></body></html>";
  return html;
}

void loop() {
  unsigned long tiempo = millis();
  
  if (tiempo - ultimo_lectura_boton >= 100) {
    ultimo_lectura_boton = tiempo;
    int estado_boton = digitalRead(PIN_BUTTON);
    if (estado_boton == HIGH && !boton_anterior) {
      Serial.println("BOTON FISICO!");
      digitalWrite(PIN_BUZZER, HIGH);
      delay(500);
      digitalWrite(PIN_BUZZER, LOW);
    }
    boton_anterior = (estado_boton == HIGH);
  }
  
  if (tiempo - ultimo_lectura_ldr >= 500) {
    ultimo_lectura_ldr = tiempo;
    valor_ldr = analogRead(PIN_LDR);
    
    if (led_modo == "AUTO") {
      if (valor_ldr > UMBRAL_OSCURIDAD) {
        int brillo = map(valor_ldr, UMBRAL_OSCURIDAD, 4095, 100, 255);
        analogWrite(PIN_LED, brillo);
        led_estado = "ON";
      } else {
        analogWrite(PIN_LED, 0);
        led_estado = "OFF";
      }
    }
    
    Serial.print("LDR: ");
    Serial.print(valor_ldr);
    Serial.print(" | LED: ");
    Serial.println(led_estado);
  }
  
  WiFiClient client = server.accept();
  if (client) {
    String peticion = client.readStringUntil('\r');
    
    if (peticion.indexOf("/ALARM_ON") > -1) {
      digitalWrite(PIN_BUZZER, HIGH);
      delay(500);
      digitalWrite(PIN_BUZZER, LOW);
    }
    else if (peticion.indexOf("/LED_ON") > -1) {
      led_modo = "MANUAL";
      analogWrite(PIN_LED, 255);
      led_estado = "ON";
    }
    else if (peticion.indexOf("/LED_OFF") > -1) {
      led_modo = "MANUAL";
      analogWrite(PIN_LED, 0);
      led_estado = "OFF";
    }
    else if (peticion.indexOf("/AUTO") > -1) {
      led_modo = "AUTO";
    }
    
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println(generarHTML());
    client.stop();
  }
  
  delay(50);
}
