# 💡 MÓDULO 2: ILUMINACIÓN (LDR + LED)

## ⏳ ESTADO: PENDIENTE

---

## 📦 MATERIALES (NUEVOS)

| Componente | Cantidad | GPIO |
|------------|----------|------|
| LDR (Fotoresistencia) | 1 | GPIO 35 |
| LED (5mm) | 1 | GPIO 32 |
| Resistencia 10kΩ | 1 | (divisor LDR) |
| Resistencia 330Ω | 1 | (limitador LED) |

**Mantén conectado:** todo del Módulo 1 (botón + buzzer)

---

## 🔌 CONEXIÓN FÍSICA

### LDR (GPIO 35) - Divisor de voltaje:
```
+3.3V ──→ LDR ──→ GPIO 35
GPIO 35 ──→ Resistencia 10kΩ ──→ GND
```

### LED (GPIO 32):
```
GPIO 32 ──→ Resistencia 330Ω ──→ LED (+) Ánodo (pata larga)
LED (-) Cátodo (pata corta) ──→ GND
```

---

## 🎨 DIAGRAMA VISUAL

```
        LDR (Divisor)              LED
        
+3.3V                         GPIO 32
  │                             │
 LDR                         R 330Ω
  │                             │
  ├──→ GPIO 35              LED (+)
  │                             │
 R 10kΩ                      LED (-)
  │                             │
 GND                           GND
```

---

## 💻 CÓDIGOS

### FASE A - Manual:
📁 `codigos/modulo2_luz_manual.ino`

Funcionamiento:
- Leer LDR cada 500ms
- Si oscuridad (valor > 2000) → LED enciende
- Si luz (valor < 2000) → LED apaga
- Brillo proporcional a oscuridad

### FASE B - Combinado con Módulo 1:
📁 `codigos/modulo2_luz_wifi.ino`

Incluye:
- Funcionamiento Módulo 1 (alarma)
- Funcionamiento Módulo 2 (luz automática)
- Página web con ambos controles

---

## ✅ PRUEBAS

### FASE A - Manual:
1. Conectar LDR + LED (mantener Módulo 1)
2. Cargar `modulo2_luz_manual.ino`
3. Abrir Monitor Serial
4. Ver lecturas LDR cada 500ms:
   ```
   LDR: 800 (LUZ) - LED apagado
   LDR: 2500 (OSCURO) - LED encendido
   ```
5. **Tapar LDR con la mano** → LED debe encender
6. **Iluminar LDR** → LED debe apagar

### FASE B - WiFi (Módulos 1 + 2):
1. Cargar `modulo2_luz_wifi.ino`
2. Abrir navegador con IP del ESP32
3. Ver:
   - Estado actual LDR
   - Estado LED (auto/manual)
   - Botones para forzar LED ON/OFF
   - Botón alarma del Módulo 1
4. **Probar:**
   - Tapar LDR → LED enciende automático
   - Click "LED OFF" → LED apaga (modo manual)
   - Click "AUTO" → vuelve a automático

---

## 💡 RECOMENDACIONES MÓDULO 2

✅ **LDR sin polaridad**: No importa qué pata va a +V o GND

✅ **LED con polaridad**:
- Pata LARGA = Ánodo (+) = Conectar a GPIO via resistencia
- Pata CORTA = Cátodo (-) = Conectar a GND
- Lado plano = Cátodo (-)

✅ **NUNCA conectar LED sin resistencia** o se quemará

✅ **Resistencia 330Ω**: Adecuada para LED de 5mm a 3.3V

✅ **Valor umbral 2000**: Ajustable según tu ambiente
- Más bajo → enciende con menos oscuridad
- Más alto → necesita más oscuridad

✅ **Probar con linterna del celular**: Para verificar respuesta del LDR

---

## 🆘 TROUBLESHOOTING

| Problema | Solución |
|----------|----------|
| LED no enciende | Verificar polaridad (pata larga = +) |
| LED siempre encendido | Verificar conexión a GND |
| LDR lee siempre 0 | Verificar divisor de voltaje completo |
| LDR lee siempre 4095 | Resistencia 10kΩ desconectada |
| LED muy débil | Bajar resistencia a 220Ω |
| LED muy brillante | Subir resistencia a 470Ω |

---

## ➡️ SIGUIENTE PASO

Una vez que ambas fases funcionen:

**👉 Ir a: `docs/modulo3_acceso.md`**
