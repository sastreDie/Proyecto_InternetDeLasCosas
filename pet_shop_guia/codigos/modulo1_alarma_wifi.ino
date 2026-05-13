#include <WiFi.h>

const char* ssid = "TU_WIFI";
const char* password = "TU_PASSWORD";

WiFiServer server(80);

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
  
  Serial.println("\nMODULO 1: ALARMA WiFi");
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

String generarHTML() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<title>Alarma</title>";
  html += "<style>body{font-family:Arial;text-align:center;background:#667eea;padding:20px;}";
  html += ".box{background:white;max-width:400px;margin:auto;padding:30px;border-radius:15px;}";
  html += "h1{color:#667eea;}button{padding:20px 40px;font-size:18px;border:none;border-radius:10px;";
  html += "background:#f44336;color:white;cursor:pointer;width:100%;margin:10px 0;}";
  html += "button:hover{background:#da190b;}</style></head><body>";
  html += "<div class='box'><h1>ALARMA</h1>";
  html += "<button onclick=\"fetch('/ALARM_ON').then(()=>location.reload())\">ACTIVAR ALARMA</button>";
  html += "</div></body></html>";
  return html;
}

void loop() {
  unsigned long tiempo_actual = millis();
  
  if (tiempo_actual - ultimo_tiempo_lectura >= INTERVALO_DEBOUNCE) {
    ultimo_tiempo_lectura = tiempo_actual;
    
    int estado_boton = digitalRead(PIN_BUTTON);
    
    if (estado_boton == HIGH && boton_presionado_anterior == false) {
      Serial.println("BOTON FISICO!");
      digitalWrite(PIN_BUZZER, HIGH);
      delay(500);
      digitalWrite(PIN_BUZZER, LOW);
    }
    
    boton_presionado_anterior = (estado_boton == HIGH);
  }
  
  WiFiClient client = server.accept();
  if (client) {
    String peticion = client.readStringUntil('\r');
    Serial.println(peticion);
    
    if (peticion.indexOf("/ALARM_ON") > -1) {
      Serial.println("ALARMA WEB!");
      digitalWrite(PIN_BUZZER, HIGH);
      delay(500);
      digitalWrite(PIN_BUZZER, LOW);
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
