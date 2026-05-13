# 🔔 MÓDULO 1: ALARMA (BUZZER + BOTÓN)

## ✅ ESTADO: COMPLETADO

---

## 📦 MATERIALES

| Componente | Cantidad | GPIO |
|------------|----------|------|
| Push Button | 1 | GPIO 13 |
| Buzzer 5V | 1 | GPIO 2 |
| Transistor BC547 | 1 | - |
| Resistencia 1kΩ | 1 | (base transistor) |
| Resistencia 10kΩ | 1 | (pull-down botón) |
| Cables jumper | varios | - |

---

## 🔌 CONEXIÓN FÍSICA

### Botón (GPIO 13):
```
+3.3V ──→ Pin 1 del botón
Pin 2 del botón ──→ GPIO 13
GPIO 13 ──→ Resistencia 10kΩ ──→ GND  (pull-down)
```

### Buzzer (GPIO 2):
```
GPIO 2 ──→ Resistencia 1kΩ ──→ BASE (Transistor BC547)
+5V ──→ Buzzer (+)
Buzzer (-) ──→ COLECTOR (Transistor)
EMISOR (Transistor) ──→ GND
```

---

## 🎨 DIAGRAMA VISUAL

```
        BOTÓN                       BUZZER + TRANSISTOR
                                    
+3.3V                              +5V
  │                                 │
  ├─── Pin 1                       Buzzer (+)
  │                                 │
  └─── Pin 2 ──→ GPIO 13           Buzzer (-)
                  │                  │
                  R 10kΩ            COLECTOR
                  │                  │
                 GND                BC547
                                     │
                                   EMISOR
                                     │
GPIO 2 ──→ R 1kΩ ──→ BASE ────────────
                                     │
                                    GND
```

---

## 💻 CÓDIGOS

### FASE A - Manual (sin WiFi):
📁 `codigos/modulo1_alarma_manual.ino`

### FASE B - Con WiFi (control remoto):
📁 `codigos/modulo1_alarma_wifi.ino`

---

## ✅ PRUEBAS

### FASE A - Manual:
1. Cargar `modulo1_alarma_manual.ino`
2. Abrir Monitor Serial (115200 baud)
3. Ver mensaje de bienvenida
4. **Presionar botón físico**
5. ✅ Buzzer suena 500ms
6. ✅ Monitor muestra: "BOTÓN PRESIONADO!"

### FASE B - WiFi:
1. Cargar `modulo1_alarma_wifi.ino`
2. Editar ssid/password
3. Esperar conexión WiFi
4. Anotar IP del Monitor Serial
5. Abrir navegador: `http://<IP>`
6. ✅ Ver página web
7. **Click "ACTIVAR ALARMA"**
8. ✅ Buzzer suena
9. **Presionar botón físico** también
10. ✅ Buzzer suena (ambos métodos funcionan)

---

## 💡 RECOMENDACIONES MÓDULO 1

✅ **Resistencia 10kΩ pull-down**: Sin ella, el GPIO 13 lee valores aleatorios

✅ **Transistor BC547**: Verificar orden de patas:
- Vista de frente (lado plano hacia ti):
- Izquierda = Base
- Centro = Colector
- Derecha = Emisor

✅ **Buzzer activo**: Usa un buzzer "activo" que ya tiene oscilador interno. Si es "pasivo" necesitas generar la frecuencia con `tone()`.

✅ **Probar buzzer directo primero**: Si no suena con transistor, prueba conectar buzzer directo a GPIO 2 y GND. Si así suena, el problema es el transistor.

---

## 🆘 TROUBLESHOOTING

| Problema | Causa | Solución |
|----------|-------|----------|
| Buzzer no suena | Transistor mal conectado | Verificar BASE-COLECTOR-EMISOR |
| Botón detecta solo | Sin resistencia pull-down | Agregar 10kΩ entre GPIO 13 y GND |
| Buzzer suena solo | Botón sin alimentación | Verificar +3.3V en botón |
| Lecturas erráticas | Cables sueltos | Apretar conexiones protoboard |

---

## ➡️ SIGUIENTE PASO

Una vez que ambas fases funcionen:

**👉 Ir a: `docs/modulo2_luz.md`**
