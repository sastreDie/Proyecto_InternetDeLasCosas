# 🚪 MÓDULO 3: ACCESO (OPTOSWITCH + SERVOMOTOR)

## ⏳ ESTADO: PENDIENTE

---

## 📦 MATERIALES (NUEVOS)

| Componente | Cantidad | GPIO |
|------------|----------|------|
| OptoSwitch | 1 | GPIO 14 |
| Servomotor SG90 | 1 | GPIO 27 |

**Mantén conectado:** todo del Módulo 1 y 2

---

## 🔌 CONEXIÓN FÍSICA

### OptoSwitch (GPIO 14):
```
OptoSwitch Vcc ──→ +3.3V (o +5V según modelo)
OptoSwitch GND ──→ GND
OptoSwitch OUT ──→ GPIO 14
```

### Servomotor SG90 (GPIO 27):
```
Servo Amarillo (Signal) ──→ GPIO 27
Servo Rojo (Vcc) ──→ +5V (¡NO 3.3V!)
Servo Café/Negro (GND) ──→ GND
```

⚠️ **IMPORTANTE:** El servo necesita 5V para girar con fuerza. Si lo conectas a 3.3V puede no funcionar o vibrar.

---

## 🎨 DIAGRAMA VISUAL

```
        OPTOSWITCH                    SERVOMOTOR SG90
        
+3.3V                              +5V
  │                                 │
  ├── Vcc                       Cable Rojo
  │                                 │
 OptoSwitch                       Servo
  │                                 │
  ├── OUT ──→ GPIO 14         Cable Negro/Café
  │                                 │
  └── GND ──→ GND                  GND
                                    
                              GPIO 27 ──→ Cable Amarillo
```

---

## 💻 CÓDIGOS

### FASE A - Manual:
📁 `codigos/modulo3_acceso_manual.ino`

Funcionamiento:
- Leer OptoSwitch continuamente
- Si detecta paso → servo gira a 90° (abre)
- Espera 2 segundos
- Servo vuelve a 0° (cierra)

### FASE B - Combinado con Módulos 1 + 2:
📁 `codigos/modulo3_acceso_wifi.ino`

Incluye:
- Alarma (Módulo 1)
- Luz automática (Módulo 2)
- Acceso con servo (Módulo 3)
- Página web con todos los controles

---

## ✅ PRUEBAS

### FASE A - Manual:
1. Conectar OptoSwitch + Servo (mantener Módulos 1 y 2)
2. Cargar `modulo3_acceso_manual.ino`
3. Abrir Monitor Serial
4. **Pasar mano/objeto por OptoSwitch**
5. ✅ Servo gira a 90° (puerta abre)
6. ✅ Espera 2 segundos
7. ✅ Servo vuelve a 0° (puerta cierra)

### FASE B - WiFi (Módulos 1+2+3):
1. Cargar `modulo3_acceso_wifi.ino`
2. Abrir navegador con IP del ESP32
3. Ver controles para:
   - Alarma
   - LED (auto/manual)
   - Puerta (Abrir/Cerrar manual)
4. **Probar:**
   - Pasar mano → puerta abre auto
   - Click "Abrir Puerta" → puerta abre manual
   - Click "Cerrar Puerta" → puerta cierra manual

---

## 💡 RECOMENDACIONES MÓDULO 3

✅ **Servomotor SG90**:
- Cable Rojo = +5V (ALIMENTACIÓN)
- Cable Café/Negro = GND
- Cable Amarillo/Naranja = SIGNAL (control PWM)

✅ **Librería ESP32Servo**:
- Instalar desde Arduino IDE Library Manager
- Buscar: "ESP32Servo" by Kevin Harrington
- Más confiable que analogWrite() para servos

✅ **Pruebas básicas del servo**:
- Antes de integrar, prueba el servo solo con un sketch simple
- Verifica que llegue a las posiciones 0°, 90°, 180°

✅ **OptoSwitch tipos**:
- Tipo barrera (U): paso entre emisor-receptor activa
- Tipo reflexivo: refleja luz de objeto cercano
- Verificar lógica HIGH/LOW según modelo

✅ **Fuente externa para servo**:
- Si tu ESP32 se reinicia al mover el servo, usa fuente externa 5V
- Conecta GND de fuente externa con GND del ESP32 (tierra común)

---

## 🆘 TROUBLESHOOTING

| Problema | Solución |
|----------|----------|
| Servo no se mueve | Verificar +5V (no 3.3V) |
| Servo vibra solo | Falta corriente - usar fuente externa |
| Servo se mueve aleatorio | Cable de signal mal conectado |
| ESP32 se reinicia con servo | Servo consume mucho - fuente aparte |
| OptoSwitch no detecta | Verificar polaridad y voltaje |
| Lectura OptoSwitch invertida | Cambiar HIGH por LOW en código |

---

## ➡️ SIGUIENTE PASO

Una vez que funcionen los 3 módulos:

**👉 Ir a: `docs/modulo4_clima.md`**
