# 🐾 PET SHOP INTELIGENTE - GUÍA PASO A PASO

## 📋 PROGRESO DEL PROYECTO

- [x] **MÓDULO 1: ALARMA** (Buzzer + Botón) ✅ COMPLETADO
- [x] **MÓDULO 2: ILUMINACIÓN** (LDR + LED)
- [x] **MÓDULO 3: ACCESO** (OptoSwitch + Servomotor)
- [ ] **MÓDULO 4: CLIMA** (LM35 + Motor Ventilador)
- [ ] **INTEGRACIÓN FINAL** (Todo junto + WiFi + Estética)

---

## 🎯 METODOLOGÍA POR MÓDULO

Cada módulo tiene **2 fases:**

1. **FASE A - MANUAL:** Funciona solo con sensor, sin WiFi
2. **FASE B - HÍBRIDA:** Funciona con sensor + control web (ESP32 + HTTP)

**No pases al siguiente módulo hasta que ambas fases funcionen.**

---

## 📦 ESTRUCTURA DE ARCHIVOS

```
pet_shop_guia/
├── README.md                    ← Esta guía
├── codigos/
│   ├── modulo1_alarma_manual.ino       ✅
│   ├── modulo1_alarma_wifi.ino         ✅
│   ├── modulo2_luz_manual.ino
│   ├── modulo2_luz_wifi.ino
│   ├── modulo3_acceso_manual.ino
│   ├── modulo3_acceso_wifi.ino
│   ├── modulo4_clima_manual.ino
│   ├── modulo4_clima_wifi.ino
│   └── proyecto_final_completo.ino
└── docs/
    ├── modulo1_alarma.md        ✅
    ├── modulo2_luz.md
    ├── modulo3_acceso.md
    ├── modulo4_clima.md
    └── integracion_final.md
```

---

## 🛠️ MATERIALES GLOBALES

### Microcontrolador:
- 1x **ESP32** DevKit

### Sensores:
- 1x **Push Button**
- 1x **LM35** (temperatura)
- 1x **LDR** (fotoresistencia)
- 1x **OptoSwitch**

### Actuadores:
- 1x **Buzzer** 5V
- 1x **Motor DC** 6-12V (ventilador)
- 1x **Servomotor** SG90
- 1x **LED** (blanco o rojo)

### Electrónica de Potencia:
- 2x **Transistor NPN** BC547
- 1x **Puente H** L298N
- 4x **Diodos** 1N4007

### Pasivos:
- 3x **Resistencia 1kΩ**
- 2x **Resistencia 10kΩ**
- 1x **Resistencia 330Ω**

### Otros:
- Protoboard
- Cables jumper
- Fuente 5V
- Cable USB

---

## 📊 TABLA GLOBAL DE PINES

```
┌─────────────────────────────────────────────────┐
│ PIN ESP32 │ MÓDULO    │ FUNCIÓN              │
├───────────┼───────────┼──────────────────────┤
│ GPIO 2    │ Alarma    │ Buzzer (salida)      │
│ GPIO 13   │ Alarma    │ Push Button (entrada)│
│           │           │                      │
│ GPIO 32   │ Luz       │ LED (salida PWM)     │
│ GPIO 35   │ Luz       │ LDR (entrada ADC)    │
│           │           │                      │
│ GPIO 14   │ Acceso    │ OptoSwitch (entrada) │
│ GPIO 27   │ Acceso    │ Servomotor (PWM)     │
│           │           │                      │
│ GPIO 34   │ Clima     │ LM35 (entrada ADC)   │
│ GPIO 25   │ Clima     │ Motor IN1 (salida)   │
│ GPIO 26   │ Clima     │ Motor IN2 (salida)   │
└───────────┴───────────┴──────────────────────┘
```

---

## 🚀 ORDEN DE IMPLEMENTACIÓN

### **PASO 1: MÓDULO ALARMA** ✅
- Carga `modulo1_alarma_manual.ino`
- Prueba botón → buzzer
- Cuando funcione: `modulo1_alarma_wifi.ino`

### **PASO 2: MÓDULO LUZ** (siguiente)
- Mantén el buzzer conectado
- Agrega LDR + LED
- Carga `modulo2_luz_manual.ino`
- Prueba: oscuridad → LED enciende
- Cuando funcione: `modulo2_luz_wifi.ino` (combina ambos)

### **PASO 3: MÓDULO ACCESO**
- Mantén buzzer + LED + LDR
- Agrega OptoSwitch + Servo
- Carga `modulo3_acceso_manual.ino`
- Prueba: paso → puerta abre
- Cuando funcione: `modulo3_acceso_wifi.ino` (los 3 juntos)

### **PASO 4: MÓDULO CLIMA**
- Mantén los 3 anteriores
- Agrega LM35 + Motor + Puente H
- Carga `modulo4_clima_manual.ino`
- Prueba: temperatura alta → motor enciende
- Cuando funcione: `modulo4_clima_wifi.ino` (los 4 juntos)

### **PASO 5: ESTÉTICA FINAL**
- Acomodar cables
- Caja para componentes
- Bateria portátil
- Puerta física (cartón/3D)
- Ventilador físico
- Pegar botón de "auxilio"

---

## 💡 RECOMENDACIONES GENERALES

### ✅ DO:
- Probar cada módulo **antes** de pasar al siguiente
- Mantener una **tierra común (GND)** para todo
- Usar **cables de colores diferentes** (rojo = +V, negro = GND)
- Anotar **qué cable va a dónde** para evitar confusiones
- Guardar **fotos** de cada paso

### ❌ DON'T:
- No conectar todo de una vez sin probar
- No mezclar voltajes (3.3V ESP32 vs 5V externos)
- No olvidar resistencias en LEDs (puede quemarlos)
- No conectar motor directo a GPIO (necesita Puente H)
- No subestimar el WiFi (puede tardar en conectar)

---

## 🆘 TROUBLESHOOTING GENERAL

| Problema | Solución |
|----------|----------|
| ESP32 no se detecta | Cambiar cable USB / Puerto COM |
| Serial Monitor en blanco | Velocidad 115200 baud |
| Código no carga | Mantener botón BOOT al cargar |
| Componente no responde | Revisar GND común |
| Lecturas erráticas | Agregar resistencia pull-up/down |

---

## 📞 SIGUIENTE PASO

**¿Listo para el MÓDULO 2 (LUZ)?**

Ver: `docs/modulo2_luz.md`

---

**Última actualización:** Mayo 2026
