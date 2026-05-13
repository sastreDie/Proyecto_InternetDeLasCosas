# 🌡️ MÓDULO 4: CLIMA (LM35 + MOTOR VENTILADOR)

## ⏳ ESTADO: PENDIENTE

---

## 📦 MATERIALES (NUEVOS)

| Componente | Cantidad | GPIO |
|------------|----------|------|
| Sensor LM35 | 1 | GPIO 34 |
| Motor DC 6-12V | 1 | - |
| Puente H L298N | 1 | GPIO 25 (IN1) + GND (IN2) |
| Diodos 1N4007 | 4 | (protección) |

**Mantén conectado:** todo de los Módulos 1, 2 y 3

---

## 🔌 CONEXIÓN FÍSICA

### LM35 (GPIO 34):
```
LM35 Vcc (Pin 1) ──→ +5V
LM35 OUT (Pin 2) ──→ GPIO 34
LM35 GND (Pin 3) ──→ GND
```

⚠️ **Vista frontal del LM35** (lado plano hacia ti):
- Pin izquierdo = Vcc
- Pin central = OUT
- Pin derecho = GND

### Puente H L298N (Control Motor):
```
L298N IN1 ──→ GPIO 25
L298N IN2 ──→ GND  (siempre LOW, motor solo gira un sentido)
L298N ENA ──→ +5V (o jumper puesto)

L298N +12V ──→ Fuente externa 12V (+)
L298N GND ──→ Fuente externa GND + GND ESP32 (tierra común)
L298N +5V ──→ NO conectar (sale del regulador interno)

L298N OUT1 ──→ Motor (+)
L298N OUT2 ──→ Motor (-)
```

⚠️ **TIERRA COMÚN:** El GND del L298N DEBE estar conectado al GND del ESP32.

---

## 🎨 DIAGRAMA VISUAL

```
        LM35 (Temperatura)              MOTOR + PUENTE H
        
+5V                                 +12V Externa
  │                                   │
LM35 Pin 1                       L298N +12V
  │                                   │
LM35 Pin 2 ──→ GPIO 34            L298N IN1 ──→ GPIO 25
  │                                   │
LM35 Pin 3 ──→ GND               L298N IN2 ──→ GND
                                      │
                                  L298N GND ──→ GND comun
                                      │
                                  OUT1 ──→ Motor (+)
                                  OUT2 ──→ Motor (-)
```

---

## 💻 CÓDIGOS

### FASE A - Manual:
📁 `codigos/modulo4_clima_manual.ino`

Funcionamiento:
- Leer LM35 cada 1 segundo
- Convertir a °C: `temp = (ADC * 3.3 / 4095) * 100`
- Si temp > 28°C → motor enciende (GPIO 25 HIGH)
- Si temp < 26°C → motor apaga (histéresis)

### FASE B - Combinado con TODOS los módulos:
📁 `codigos/modulo4_clima_wifi.ino`

Sistema completo con:
- Módulo 1: Alarma
- Módulo 2: Luz auto
- Módulo 3: Acceso
- Módulo 4: Clima
- Página web con todos los controles

---

## ✅ PRUEBAS

### FASE A - Manual:
1. Conectar LM35 + Puente H + Motor (mantener anteriores)
2. Cargar `modulo4_clima_manual.ino`
3. Abrir Monitor Serial
4. Ver lecturas:
   ```
   Temperatura: 24.5°C - Motor OFF
   Temperatura: 28.2°C - Motor ON
   Temperatura: 25.8°C - Motor OFF (histéresis)
   ```
5. **Calentar LM35 con tu dedo** (~10 segundos)
6. ✅ Temperatura sube
7. ✅ Motor enciende cuando T > 28°C
8. ✅ Motor apaga cuando T < 26°C

### FASE B - WiFi (TODOS los módulos):
1. Cargar `modulo4_clima_wifi.ino`
2. Abrir navegador con IP del ESP32
3. Ver dashboard completo:
   - Temperatura actual
   - Luz actual
   - Estado motor (auto/manual)
   - Estado LED (auto/manual)
   - Estado Puerta
   - Botones para todo
4. **Probar TODO:**
   - Calentar LM35 → motor auto
   - Click "Motor ON" → motor manual
   - Tapar LDR → LED auto
   - Pasar mano OptoSwitch → puerta auto
   - Botón físico → alarma
   - Click web → alarma

---

## 💡 RECOMENDACIONES MÓDULO 4

✅ **LM35 calibración**:
- Verificar lectura a temperatura ambiente (~25°C)
- Si lee muy diferente, verificar voltaje de referencia
- ESP32 usa 3.3V, por lo que: `temp = ADC * 3.3 * 100 / 4095`

✅ **Puente H L298N**:
- Lleva 12V para alimentar motor
- El regulador interno da 5V (no usar si ya tienes 5V)
- Si solo necesitas un sentido: IN2 a GND, IN1 controlado por ESP32

✅ **Motor DC**:
- Verificar voltaje nominal (6V, 9V, 12V)
- Si motor es muy potente, puede necesitar fuente separada
- **Siempre poner diodos** en el motor (back-EMF)

✅ **Diodos de protección**:
- 1N4007 entre OUT1 y OUT2
- Protegen al Puente H de picos de tensión cuando motor se apaga

✅ **Histéresis 26-28°C**:
- Evita que motor se prenda/apague constantemente
- Margen de 2°C es típico
- Ajustable según necesidad

✅ **Fuente externa para motor**:
- USB no da suficiente corriente para motor + ESP32
- Usa fuente 12V 2A para el Puente H
- Conecta GND de fuente con GND de ESP32

---

## 🆘 TROUBLESHOOTING

| Problema | Solución |
|----------|----------|
| LM35 lee 0°C o muy bajo | Verificar +5V y polaridad |
| LM35 lee temperaturas locas | Resistencia o cable suelto |
| Motor no gira | Verificar +12V en Puente H |
| Motor gira al revés | Cambiar OUT1 ↔ OUT2 |
| ESP32 se reinicia con motor | Falta tierra común o fuente débil |
| Motor débil | Aumentar voltaje fuente |
| Picos al apagar motor | Verificar diodos 1N4007 |

---

## ➡️ SIGUIENTE PASO

Una vez que funcionen los 4 módulos:

**👉 Ir a: `docs/integracion_final.md`**
