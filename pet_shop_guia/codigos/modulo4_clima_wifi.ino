#include <WiFi.h>
#include <ESP32Servo.h>

const char* ssid = "TU_WIFI";
const char* password = "TU_PASSWORD";

WiFiServer server(80);

const int PIN_BUTTON = 13;
const int PIN_BUZZER = 2;
const int PIN_LDR = 35;
const int PIN_LED = 32;
const int PIN_OPTOSWITCH = 14;
const int PIN_SERVO = 27;
const int PIN_LM35 = 34;
const int PIN_MOTOR = 25;

const int UMBRAL_OSCURIDAD = 2000;
const float UMBRAL_TEMP_ALTA = 28.0;
const float UMBRAL_TEMP_BAJA = 26.0;
const unsigned long DURACION_APERTURA = 2000;

Servo puerta;

int valor_ldr = 0;
float temperatura = 0;
String motor_modo = "AUTO";
String motor_estado = "OFF";
String led_modo = "AUTO";
String led_estado = "OFF";
String puerta_modo = "AUTO";
String puerta_estado = "CERRADA";
bool puerta_abierta = false;

unsigned long tiempo_apertura = 0;
unsigned long ultimo_lectura_ldr = 0;
unsigned long ultimo_lectura_temp = 0;
unsigned long ultimo_lectura_boton = 0;
bool boton_anterior = false;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_OPTOSWITCH, INPUT);
  pinMode(PIN_MOTOR, OUTPUT);
  analogReadResolution(12);
  
  digitalWrite(PIN_BUZZER, LOW);
  digitalWrite(PIN_LED, LOW);
  digitalWrite(PIN_MOTOR, LOW);
  
  puerta.attach(PIN_SERVO);
  puerta.write(0);
  
  Serial.println("\nPET SHOP COMPLETO");
  Serial.print("WiFi");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nIP:");
  Serial.println(WiFi.localIP());
  server.begin();
}

String generarHTML() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<title>Pet Shop Inteligente</title>";
  html += "<style>body{font-family:Arial;background:linear-gradient(135deg,#667eea,#764ba2);padding:20px;margin:0;min-height:100vh;}";
  html += ".box{background:white;max-width:550px;margin:auto;padding:30px;border-radius:15px;box-shadow:0 10px 40px rgba(0,0,0,0.3);}";
  html += "h1{color:#667eea;text-align:center;font-size:2em;}h2{color:#764ba2;border-bottom:3px solid #667eea;padding-bottom:10px;margin-top:25px;}";
  html += ".info{background:#f0f4ff;padding:15px;margin:10px 0;border-radius:8px;border-left:5px solid #667eea;font-size:1.1em;}";
  html += "button{padding:15px;font-size:16px;border:none;border-radius:8px;cursor:pointer;color:white;font-weight:bold;width:100%;margin:5px 0;}";
  html += ".btn-on{background:#4CAF50;}.btn-off{background:#f44336;}.btn-alarm{background:#ff5722;}.btn-auto{background:#2196F3;}";
  html += ".grid{display:grid;grid-template-columns:1fr 1fr;gap:10px;}.badge{display:inline-block;padding:3px 10px;border-radius:15px;font-size:0.85em;margin-left:10px;}";
  html += ".auto{background:#c8e6c9;color:#2e7d32;}.manual{background:#ffccbc;color:#d84315;}</style></head><body>";
  html += "<div class='box'><h1>🐾 PET SHOP 🐾</h1>";
  
  html += "<h2>📊 Sensores</h2>";
  html += "<div class='info'>🌡️ Temperatura: <b>" + String(temperatura, 1) + "°C</b></div>";
  html += "<div class='info'>💡 Luz: <b>" + String(valor_ldr) + "/4095</b></div>";
  
  html += "<h2>🔔 Alarma</h2>";
  html += "<button class='btn-alarm' onclick=\"f('/ALARM_ON')\">ACTIVAR ALARMA</button>";
  
  html += "<h2>❄️ Ventilador <span class='badge " + String(motor_modo == "AUTO" ? "auto" : "manual") + "'>" + motor_modo + "</span> (" + motor_estado + ")</h2>";
  html += "<div class='grid'>";
  html += "<button class='btn-on' onclick=\"f('/FAN_ON')\">FAN ON</button>";
  html += "<button class='btn-off' onclick=\"f('/FAN_OFF')\">FAN OFF</button>";
  html += "</div>";
  
  html += "<h2>💡 LED <span class='badge " + String(led_modo == "AUTO" ? "auto" : "manual") + "'>" + led_modo + "</span> (" + led_estado + ")</h2>";
  html += "<div class='grid'>";
  html += "<button class='btn-on' onclick=\"f('/LED_ON')\">LED ON</button>";
  html += "<button class='btn-off' onclick=\"f('/LED_OFF')\">LED OFF</button>";
  html += "</div>";
  
  html += "<h2>🚪 Puerta <span class='badge " + String(puerta_modo == "AUTO" ? "auto" : "manual") + "'>" + puerta_modo + "</span> (" + puerta_estado + ")</h2>";
  html += "<div class='grid'>";
  html += "<button class='btn-on' onclick=\"f('/DOOR_OPEN')\">ABRIR</button>";
  html += "<button class='btn-off' onclick=\"f('/DOOR_CLOSE')\">CERRAR</button>";
  html += "</div>";
  
  html += "<h2>🔄 Modo Global</h2>";
  html += "<button class='btn-auto' onclick=\"f('/AUTO')\">VOLVER TODO A AUTOMÁTICO</button>";
  
  html += "</div><script>function f(u){fetch(u).then(()=>location.reload());}setTimeout(()=>location.reload(),5000);</script></body></html>";
  return html;
}

void loop() {
  unsigned long tiempo = millis();
  
  if (tiempo - ultimo_lectura_boton >= 100) {
    ultimo_lectura_boton = tiempo;
    int estado_boton = digitalRead(PIN_BUTTON);
    if (estado_boton == HIGH && !boton_anterior) {
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
  }
  
  if (tiempo - ultimo_lectura_temp >= 1000) {
    ultimo_lectura_temp = tiempo;
    int adc = analogRead(PIN_LM35);
    float voltaje = (adc / 4095.0) * 3.3;
    temperatura = voltaje * 100.0;
    
    if (motor_modo == "AUTO") {
      if (temperatura > UMBRAL_TEMP_ALTA && motor_estado == "OFF") {
        digitalWrite(PIN_MOTOR, HIGH);
        motor_estado = "ON";
      } else if (temperatura < UMBRAL_TEMP_BAJA && motor_estado == "ON") {
        digitalWrite(PIN_MOTOR, LOW);
        motor_estado = "OFF";
      }
    }
    
    Serial.print("T:");
    Serial.print(temperatura);
    Serial.print(" L:");
    Serial.print(valor_ldr);
    Serial.print(" M:");
    Serial.print(motor_estado);
    Serial.print(" LED:");
    Serial.println(led_estado);
  }
  
  if (puerta_modo == "AUTO") {
    int estado_opto = digitalRead(PIN_OPTOSWITCH);
    if (estado_opto == HIGH && !puerta_abierta) {
      puerta.write(90);
      puerta_abierta = true;
      puerta_estado = "ABIERTA";
      tiempo_apertura = millis();
    }
    
    if (puerta_abierta && (millis() - tiempo_apertura >= DURACION_APERTURA)) {
      puerta.write(0);
      puerta_abierta = false;
      puerta_estado = "CERRADA";
    }
  }
  
  WiFiClient client = server.accept();
  if (client) {
    String peticion = client.readStringUntil('\r');
    
    if (peticion.indexOf("/ALARM_ON") > -1) {
      digitalWrite(PIN_BUZZER, HIGH);
      delay(500);
      digitalWrite(PIN_BUZZER, LOW);
    }
    else if (peticion.indexOf("/FAN_ON") > -1) {
      motor_modo = "MANUAL";
      digitalWrite(PIN_MOTOR, HIGH);
      motor_estado = "ON";
    }
    else if (peticion.indexOf("/FAN_OFF") > -1) {
      motor_modo = "MANUAL";
      digitalWrite(PIN_MOTOR, LOW);
      motor_estado = "OFF";
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
    else if (peticion.indexOf("/DOOR_OPEN") > -1) {
      puerta_modo = "MANUAL";
      puerta.write(90);
      puerta_estado = "ABIERTA";
      puerta_abierta = true;
    }
    else if (peticion.indexOf("/DOOR_CLOSE") > -1) {
      puerta_modo = "MANUAL";
      puerta.write(0);
      puerta_estado = "CERRADA";
      puerta_abierta = false;
    }
    else if (peticion.indexOf("/AUTO") > -1) {
      motor_modo = "AUTO";
      led_modo = "AUTO";
      puerta_modo = "AUTO";
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
