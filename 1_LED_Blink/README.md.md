# 💡 STM32F103 Bare Metal — LED Blink
### GPIO Output | Direct Register Access | No HAL | No Library | Real World Applications

<div align="center">

![STM32](https://img.shields.io/badge/MCU-STM32F103C6/C8-03234B?style=for-the-badge&logo=stmicroelectronics&logoColor=white)
![Bare Metal](https://img.shields.io/badge/Bare_Metal-C-FF6600?style=for-the-badge)
![Keil](https://img.shields.io/badge/IDE-Keil_MDK-003366?style=for-the-badge)
![GPIO](https://img.shields.io/badge/GPIO-Output-1565C0?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

</div>

---

## 📌 Project Overview

This is the **"Hello World"** of Embedded Systems — LED Blink using **Bare Metal C** on STM32F103.
No HAL, No Library — Pure direct register manipulation.
This simple concept is the foundation of every embedded system in the world!

### ✅ Key Features:
- Pure Bare Metal C — No HAL, No Library
- Direct Register Access
- RCC Clock configuration
- GPIO Output configuration
- Software delay implementation
- Built-in LED (PC13) control
- Compatible with STM32F103C6 and C8 (Blue Pill)

---

## 🛠️ Hardware Used

| Component | Specification |
|-----------|-------------|
| MCU | STM32F103C6/C8T6 (Blue Pill) |
| IDE | Keil MDK uVision |
| Programmer | STM32CubeProgrammer (ST-Link V2) |
| LED | Built-in LED (PC13) |
| Power | 3.3V / 5V USB |

---

## 🔌 Hardware Connection

```
STM32 Blue Pill
───────────────────────────
PC13 → Built-in LED (Onboard)
       No external connection needed!

Optional External LED:
PA1  → 330Ω → LED → GND
```

### Circuit Diagram:
```
STM32
PC13 ──────── [Built-in LED] ──── 3.3V
              (Active LOW)

PA1 ─────────[330Ω]──── [LED] ──── GND
              (Active HIGH — Optional)
```

---

## 💻 Full Code

```c
int main(void)
{
    /* ── RCC Clock Enable ─────────────────────── */
    /* GPIOC clock ON karo */
    unsigned int *RCC_APB2ENR = (unsigned int *)(0x40021000 + 0x18);
    *RCC_APB2ENR |= (1 << 4); /* GPIOC Clock Enable */

    /* ── PC13 → Output Push-Pull (LED) ────────── */
    unsigned int *GPIOC_CRH = (unsigned int *)(0x40011000 + 0x04);
    unsigned int *GPIOC_ODR = (unsigned int *)(0x40011000 + 0x0C);

    *GPIOC_CRH &= ~(0xF << 20); /* Clear PC13 bits */
    *GPIOC_CRH |=  (0x2 << 20); /* Output 2MHz Push-Pull */

    /* ── LED Blink Loop ───────────────────────── */
    while(1)
    {
        *GPIOC_ODR &= ~(1 << 13); /* LED ON  (Active LOW) */
        for(volatile int i = 0; i < 500000; i++); /* Delay */

        *GPIOC_ODR |=  (1 << 13); /* LED OFF */
        for(volatile int i = 0; i < 500000; i++); /* Delay */
    }
}
```

---

## 🧠 Code Explanation

### Step 1 — RCC Clock Enable:
```
STM32 mein GPIO use karne se pehle
uska clock ON karna padta hai!

RCC_APB2ENR register:
Bit 4 = GPIOC clock enable

*RCC_APB2ENR |= (1 << 4);
→ GPIOC clock ON ✅
```

### Step 2 — GPIO Configure:
```
GPIOC_CRH register:
PC13 = bits [23:20]

MODE13[1:0] = 10 → Output 2MHz
CNF13[1:0]  = 00 → Push-Pull

*GPIOC_CRH &= ~(0xF << 20); → Clear
*GPIOC_CRH |=  (0x2 << 20); → Set ✅
```

### Step 3 — LED Toggle:
```
PC13 Active LOW:

*GPIOC_ODR &= ~(1 << 13); → PC13 = 0 → LED ON
*GPIOC_ODR |=  (1 << 13); → PC13 = 1 → LED OFF
```

### Delay Function:
```c
for(volatile int i = 0; i < 500000; i++);

volatile → Compiler optimize nahi karega
500000   → ~500ms delay at 8MHz
           Increase = slow blink
           Decrease = fast blink
```

---

## 🌍 Real World Applications

> **"LED Blink = GPIO Toggle = Digital Output Control"**
> Jo LED ko control karta hai — wahi concept se
> duniya ki har embedded device chalti hai! 💡

---

### 🏭 1. Industrial Automation
```
LED ki jagah:           Use Case:
────────────────────────────────────────
Relay Module    →   Machine ON/OFF
Solenoid Valve  →   Fluid flow control
Pneumatic Valve →   Air pressure control
Motor Driver    →   Conveyor belt control
Indicator Light →   Status display panel

Real Examples:
→ Factory machine status indicator
→ Production line running indicator
→ Fault/Error warning light
→ Process complete indicator
→ Emergency stop indicator
→ Automatic packaging machine timing
```

---

### 🚗 2. Automotive Systems
```
LED ki jagah:           Use Case:
────────────────────────────────────────
Turn Signal     →   Indicator blink ✅
Hazard Light    →   Emergency blink ✅
Brake Light     →   Brake indicator
DRL Light       →   Daytime running
Dashboard LED   →   Warning indicators

Real Examples:
→ Car turn signal (60 blinks/min)
→ Hazard warning lights
→ Seat belt reminder blink
→ Low fuel warning blink
→ Check engine light blink
→ ABS indicator blink
→ Battery warning blink
```

---

### 🏥 3. Medical Devices
```
LED ki jagah:           Use Case:
────────────────────────────────────────
Status LED      →   Device working ✅
Alarm LED       →   Patient alert
Heartbeat LED   →   Pulse indicator
Battery LED     →   Low battery warn
Power LED       →   Device ON indicator

Real Examples:
→ Pulse oximeter heartbeat LED
→ ECG machine status blink
→ Ventilator alarm indicator
→ Medicine reminder blink
→ Hospital bed call light
→ Defibrillator ready indicator
→ IV drip rate indicator
```

---

### 📡 4. Communication Systems
```
LED ki jagah:           Use Case:
────────────────────────────────────────
TX LED          →   Data sending ✅
RX LED          →   Data receiving ✅
Link LED        →   Connection status
Error LED       →   Packet error
Activity LED    →   Network activity

Real Examples:
→ Router TX/RX blinking LEDs
→   WiFi connected indicator
→ Modem data transfer blink
→ Ethernet link status
→ Bluetooth pairing blink
→ GSM signal blink
→ LoRa packet indicator
```

---

### 🤖 5. Robotics
```
LED ki jagah:           Use Case:
────────────────────────────────────────
Status LED      →   Robot running ✅
Motor PWM       →   Speed control
Servo PWM       →   Position control
Buzzer          →   Audio alert
Eye LEDs        →   Expression show

Real Examples:
→ Robot power ON indicator
→ Battery low warning blink
→ Obstacle detected blink
→ Mission complete blink
→ Robot arm position indicator
→ Autonomous mode indicator
→ Charging status blink
```

---

### 🏠 6. Smart Home / IoT
```
LED ki jagah:           Use Case:
────────────────────────────────────────
Relay → AC Bulb →   Smart light ✅
Relay → Fan     →   Smart fan
MOSFET → LED    →   RGB light strip
Buzzer          →   Smart doorbell
Status LED      →   WiFi connected

Real Examples:
→ Smart bulb blinking effect
→ WiFi connecting indicator
→ Doorbell flash effect
→ Motion detected flash
→ Smart switch status
→ OTA update progress blink
→ Night mode indicator
```

---

### ⚡ 7. Power Electronics
```
LED ki jagah:           Use Case:
────────────────────────────────────────
MOSFET Gate     →   PWM switching ✅
Relay Coil      →   Load switching
Optocoupler     →   Isolated control
Gate Driver     →   Inverter control
Buck Converter  →   PWM regulation

Real Examples:
→ Buck converter PWM switching
→ Inverter gate signal
→ Battery charger control
→ Solar MPPT switching
→ Motor speed PWM control
→ LED driver dimming
→ Power supply regulation
```

---

### 🌾 8. Agriculture / Smart Farming
```
LED ki jagah:           Use Case:
────────────────────────────────────────
Water Pump Relay →  Irrigation ✅
Solenoid Valve   →  Drip system
Grow Light       →  Plant lighting
Heater Relay     →  Greenhouse heat
Fan Relay        →  Ventilation

Real Examples:
→ Timed irrigation system
→ Greenhouse lighting cycle
→ Poultry lighting timer
→ Fish tank aerator timer
→ Automatic feeding system
→ Frost protection heater
→ Mushroom farm humidity control
```

---

### 🔒 9. Security Systems
```
LED ki jagah:           Use Case:
────────────────────────────────────────
Siren/Buzzer    →   Intruder alarm ✅
Strobe Light    →   Visual alarm
Camera          →   Recording indicator
Lock Relay      →   Door control
Flash LED       →   Deterrent light

Real Examples:
→ Burglar alarm strobe
→ CCTV recording indicator
→ Door lock timer
→ Safe unlocking indicator
→ Perimeter light flash
→ Panic alarm blink
```

---

## 📊 LED ki Jagah Kya Laga Sakte Hain:

| Output Device | Driver Needed | Current | Example Use |
|--------------|--------------|---------|------------|
| LED | Direct | 10-20mA | Status indicator |
| Buzzer (Active) | Direct | 20mA | Alert sound |
| Relay 5V | Transistor BC547 | 50mA | AC load control |
| DC Motor | L298N | 2A | Robot movement |
| Servo Motor | Direct PWM | 500mA | Position control |
| MOSFET Load | Gate resistor | 10A+ | High power switching |
| LED Strip | MOSFET IRF540 | 3A | Lighting effect |
| Solenoid | MOSFET + Diode | 1A | Valve control |
| Heating Element | MOSFET | 5A | Temperature control |
| AC Bulb/Fan | Relay | 10A | Home automation |

---

## 💡 Blink Speed = Real World Timing:

```c
/* Fast Blink — 100ms */
for(volatile int i = 0; i < 100000; i++);
/* Use: Emergency alarm, Error indicator */

/* Normal Blink — 500ms */
for(volatile int i = 0; i < 500000; i++);
/* Use: Status indicator, Heartbeat */

/* Slow Blink — 1000ms */
for(volatile int i = 0; i < 1000000; i++);
/* Use: Standby mode, Sleep indicator */

/* Car Indicator — ~800ms */
for(volatile int i = 0; i < 800000; i++);
/* Use: Turn signal (60 blinks/min) */
```

---

## ⚠️ GPIO Current Limit:

```
STM32 GPIO max current = 25mA per pin

LED Direct connect:
3.3V → 330Ω → LED → GND
Current = (3.3 - 2.0) / 330 = ~4mA ✅ Safe!

For high power loads:
Always use driver circuit!
GPIO → Driver IC → Load
```

---

## 📋 Register Reference

| Register | Address | Purpose |
|----------|---------|---------|
| RCC_APB2ENR | 0x40021018 | GPIO Clock Enable |
| GPIOC_CRH | 0x40011004 | PC8-PC15 Configure |
| GPIOC_ODR | 0x4001100C | PC Output Write |

### GPIO Mode Bits:
```
PC13 → CRH bits [23:20]

MODE[1:0] CNF[1:0]  = Mode
─────────────────────────────
  10        00      = Output 2MHz Push-Pull ✅
  11        00      = Output 50MHz Push-Pull
  00        01      = Input Floating
  00        10      = Input Pull-up/Pull-down
```

---

## 🚀 How to Flash

```
1. Keil MDK mein code paste karo
2. Device select: STM32F103C8
3. Build karo (F7)
4. Hex file generate hoga:
   Objects/project.hex
5. STM32CubeProgrammer kholo
6. ST-Link connect karo
7. Hex file select karo
8. Download click karo ✅
9. LED blink shuru! 💡
```

> ⚠️ Clone Blue Pill boards mein Keil direct flash nahi hota!
> STM32CubeProgrammer use karo — perfectly works! ✅

---

## 🎯 Key Learnings

```
✅ RCC clock enable — GPIO use se pehle zaroori
✅ CRH/CRL register — GPIO configure karta hai
✅ ODR register — GPIO output control karta hai
✅ Active LOW — PC13 mein LOW = LED ON
✅ volatile — Hardware register ke liye zaroori
✅ GPIO Toggle — Embedded world ka foundation
```

---

## 👨‍💻 Developer

**Ramsudarshan Maurya**
🎓 B.Tech ECE — AKTU Lucknow (2025)
🏢 Embedded Systems Intern — UniConverge Technologies, Noida
📚 IoT Trainee — IoT Academy, Noida
🏆 RoboRace 1st Prize | Published Researcher IJRPR

[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=flat&logo=linkedin)](https://linkedin.com/in/ramsudarshanmaurya)
[![GitHub](https://img.shields.io/badge/GitHub-181717?style=flat&logo=github)](https://github.com/Ramsudarshanmaurya)

---

## 📄 License

MIT License — Free to use, modify and distribute.

---

<div align="center">

**⭐ Agar helpful laga toh Star zaroor do! ⭐**

*"LED Blink = Embedded World ka Hello World!*
*Is ek concept se hi duniya ki har device chalti hai!"* 💡🔧

</div>
