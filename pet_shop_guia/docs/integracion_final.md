# 🎨 INTEGRACIÓN FINAL Y ESTÉTICA

## ⏳ ESTADO: PENDIENTE

---

## 🎯 OBJETIVOS DE ESTA FASE

Una vez que los **4 módulos funcionan integrados con WiFi**, hay que:

1. ✅ Ordenar el cableado
2. ✅ Independizar de USB (usar batería)
3. ✅ Construir puerta física
4. ✅ Montar ventilador
5. ✅ Pegar botón de auxilio en lugar accesible
6. ✅ Hacer todo presentable

---

## 📦 MATERIALES ADICIONALES (Estética)

| Componente | Uso |
|------------|-----|
| Caja/estructura (cartón rígido, madera o impresión 3D) | Alojamiento del circuito |
| Power Bank o Batería 5V/2A | Alimentación portátil |
| Cable USB → Tipo C (para Power Bank) | Conectar batería al ESP32 |
| Tornillos M3 + tuercas | Fijación |
| Hilo/Pegamento caliente | Sujetar componentes |
| Cartón/Acrílico | Para la puerta |
| Velcro o cinta doble cara | Pegar botón |
| Bridas (zip ties) | Organizar cables |
| Termoencogible | Aislar empalmes |

---

## 🔋 FASE 1: ALIMENTACIÓN INDEPENDIENTE

### Opción A: Power Bank USB

```
Power Bank → Cable USB → ESP32 (Micro-USB)
```

**Ventajas:**
- Fácil de implementar
- Recargable
- No requiere modificación

**Desventajas:**
- Algunos power banks se apagan si el consumo es bajo
- Verificar que sea de "salida continua"

### Opción B: Batería 9V con regulador

```
Batería 9V → Regulador LM7805 → +5V → ESP32 + Componentes
                                  → GND
```

### Opción C: 4 pilas AA (6V)

```
4x Pilas AA → +6V → Puente H L298N (motor)
              → Diodo 1N4007 (caída a 5V) → ESP32
```

---

## 🏗️ FASE 2: ORDENAR CABLEADO

### Pasos:

1. **Etiquetar cada cable** con cinta y plumón:
   - Rojo = +5V
   - Negro = GND
   - Verde = Señal sensor
   - Amarillo = Señal actuador

2. **Agrupar cables por módulo:**
   - Grupo 1: Cables módulo alarma
   - Grupo 2: Cables módulo luz
   - Etc.

3. **Usar bridas (zip ties):**
   - Unir cables del mismo módulo
   - Mantener distancia entre cables de alta corriente (motor) y señales (sensores)

4. **Reemplazar jumpers largos por cables cortos:**
   - Si tienes soldador, hacer empalmes directos
   - Usar termoencogible para aislar

---

## 🚪 FASE 3: PUERTA FÍSICA

### Materiales:
- Cartón rígido o placa de balsa (15x10 cm)
- Pegamento caliente
- Servomotor SG90

### Pasos:

1. **Cortar la puerta:**
   - Rectángulo 10x5 cm

2. **Cortar el marco:**
   - Estructura con abertura del tamaño de la puerta

3. **Pegar servo al marco:**
   - El brazo del servo debe quedar en la parte superior

4. **Pegar puerta al brazo del servo:**
   - Verificar que gire 90° sin chocar

5. **Probar con código:**
   - 0° = puerta cerrada (vertical)
   - 90° = puerta abierta (horizontal)

---

## 🌬️ FASE 4: MONTAJE VENTILADOR

### Opción A: Motor con aspas

1. **Conseguir aspas para motor:**
   - Aspas plásticas pequeñas (3-5 cm)
   - Pegar al eje con pegamento caliente

2. **Fijar motor a la caja:**
   - Hot glue o tornillos
   - Cerca del LM35 para realimentación correcta

### Opción B: Ventilador 5V/12V de PC

1. **Más profesional:**
   - Ventilador 40mm o 80mm
   - Conectar a Puente H L298N
   - Más estable y silencioso

---

## 🆘 FASE 5: BOTÓN DE AUXILIO

### Pasos:

1. **Elegir ubicación:**
   - Visible y accesible
   - Por ejemplo: parte frontal de la caja

2. **Botón grande (opcional):**
   - Reemplazar push button pequeño por uno tipo "panic button"
   - Más visible y satisfactorio

3. **Pegar/atornillar:**
   - Usar velcro para fácil mantenimiento
   - O atornillar permanentemente

4. **Etiquetar:**
   - "AUXILIO" o icono SOS
   - Color rojo llamativo

---

## 📐 FASE 6: ESTRUCTURA FINAL

### Opción A: Caja de cartón

```
┌────────────────────────┐
│   PET SHOP             │  ← Etiqueta superior
│   INTELIGENTE          │
├────────────────────────┤
│  [LED] [TEMP] [LUZ]    │  ← Indicadores frontales
│                        │
│  ╔═══╗                 │
│  ║🚪 ║ ← Puerta servo  │
│  ╚═══╝                 │
│                        │
│   🌬️  ← Ventilador      │
│                        │
│  [⚠️ AUXILIO]            │  ← Botón grande
└────────────────────────┘
```

### Opción B: Caja impresa 3D

Diseñar en TinkerCAD/Fusion 360:
- Compartimentos para cada módulo
- Aberturas para sensores y actuadores
- Tapa removible para mantenimiento

---

## ✅ CHECKLIST FINAL

Antes de presentar el proyecto:

- [ ] Los 4 módulos funcionan en modo automático
- [ ] Los 4 módulos funcionan en modo manual (web)
- [ ] WiFi se conecta sin problemas
- [ ] IP del ESP32 es estable
- [ ] Cables organizados con bridas
- [ ] Conexiones firmes (no se sueltan)
- [ ] Funciona con batería/power bank (sin USB)
- [ ] Puerta abre/cierra correctamente
- [ ] Ventilador gira al detectar calor
- [ ] LED enciende al tapar LDR
- [ ] Botón de auxilio activa alarma
- [ ] Página web se ve bien en celular
- [ ] Caja/estructura terminada y presentable
- [ ] Etiquetas y nombres visibles
- [ ] Foto/video del proyecto para entrega

---

## 📸 EVIDENCIAS PARA ENTREGA

Tomar fotos/videos de:

1. **Sistema completo encendido**
2. **Cada módulo funcionando**
3. **Monitor Serial mostrando datos**
4. **Página web en celular**
5. **Pruebas de control automático**
6. **Pruebas de control manual**
7. **Sistema funcionando con batería**

---

## 🎓 PARA EL DOCUMENTO ACADÉMICO

Recordar incluir en el reporte:

- Diagrama esquemático final
- Tabla de pines GPIO usados
- Código fuente (con comentarios)
- Capturas de pantalla web
- Fotos del montaje físico
- Pruebas y resultados
- Conclusiones individuales y grupal
- Bibliografía en formato APA

---

## 🎉 ¡PROYECTO TERMINADO!

Si llegaste hasta aquí, **felicitaciones**. Has construido un sistema IoT completo con:

- ✅ 4 sensores diferentes
- ✅ 4 actuadores con diferentes etapas de potencia
- ✅ Servidor web local
- ✅ Control híbrido (auto + manual)
- ✅ Diseño físico presentable

**Próximos pasos opcionales:**

- 🚀 Subir datos a la nube (Firebase, ThingSpeak)
- 📱 Crear app móvil con MIT App Inventor
- 🤖 Integrar con Alexa/Google Home
- 📊 Dashboard con gráficos históricos
- 🔐 Agregar autenticación a la web
