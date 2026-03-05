# 🔢 STM32F103 Bare Metal — Button Count LED Blink
### Counter Logic | GPIO Input/Output | Debounce | Real World Applications

<div align="center">

![STM32](https://img.shields.io/badge/MCU-STM32F103C6/C8-03234B?style=for-the-badge&logo=stmicroelectronics&logoColor=white)
![Bare Metal](https://img.shields.io/badge/Bare_Metal-C-FF6600?style=for-the-badge)
![Keil](https://img.shields.io/badge/IDE-Keil_MDK-003366?style=for-the-badge)
![Counter](https://img.shields.io/badge/Logic-Counter%20%2B%20Blink-1565C0?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

</div>

---

## 📌 Project Overview

This project demonstrates **Button Press Counter with LED Blink feedback** using **Bare Metal C** on STM32F103.
Every button press increments a counter and the LED blinks exactly that many times as visual feedback.
This counter logic is the foundation of real-world counting, selection, and control systems.

### ✅ Key Features:
- Pure Bare Metal C — No HAL, No Library
- Direct Register Manipulation
- Press Counter with visual LED feedback
- Software Debounce implemented
- Built-in + External LED control
- Internal Pull-up — No resistor needed
- Compatible with STM32F103C6 and C8 (Blue Pill)

---

## 🛠️ Hardware Used

| Component | Specification |
|-----------|-------------|
| MCU | STM32F103C6/C8T6 (Blue Pill) |
| IDE | Keil MDK uVision |
| Programmer | STM32CubeProgrammer (ST-Link V2) |
| Button | Tactile Push Button |
| LED 1 | Built-in LED (PC13) |
| LED 2 | External LED (PA1) |
| Power | 3.3V / 5V USB |

---

## 🔌 Hardware Connection

```
STM32 Blue Pill      Component
──────────────────────────────────
PA0          →       Button → GND
PA1          →       External LED → GND
PC13         →       Built-in LED (onboard)
GND          →       Common GND
```

### Circuit Diagram:
```
Internal Pull-up (40KΩ):

3.3V
 │
40KΩ (Internal)
 │
PA0 ──────── [Button] ──── GND

PA1 ──────── [LED] ──── GND
              (Active HIGH)

PC13 ──────── [LED] ──── 3.3V
               (Active LOW — Built-in)
```

---

## 💻 Full Code

```c
int main(void)
{
    /* ── RCC Clock Enable ─────────────────────── */
    unsigned int *RCC_APB2ENR = (unsigned int *)(0x40021000 + 0x18);
    *RCC_APB2ENR |= (1 << 2); /* GPIOA Clock ON */
    *RCC_APB2ENR |= (1 << 4); /* GPIOC Clock ON */

    /* ── PC13 → Output Push-Pull (Built-in LED) ─ */
    unsigned int *GPIOC_CRH = (unsigned int *)(0x40011000 + 0x04);
    *GPIOC_CRH &= ~(0xF << 20);
    *GPIOC_CRH |=  (0x2 << 20);

    /* ── PA0 → Input Pull-up (Button) ───────────  */
    /* ── PA1 → Output Push-Pull (External LED) ──  */
    unsigned int *GPIOA_CRL = (unsigned int *)(0x40010800 + 0x00);
    unsigned int *GPIOA_ODR = (unsigned int *)(0x40010800 + 0x0C);
    unsigned int *GPIOA_IDR = (unsigned int *)(0x40010800 + 0x08);
    unsigned int *GPIOC_ODR = (unsigned int *)(0x40011000 + 0x0C);

    /* PA0 → Input Pull-up */
    *GPIOA_CRL &= ~(0xF << 0);
    *GPIOA_CRL |=  (0x8 << 0);
    *GPIOA_ODR |=  (1 << 0);

    /* PA1 → Output 2MHz Push-Pull */
    *GPIOA_CRL &= ~(0xF << 4);
    *GPIOA_CRL |=  (0x2 << 4);

    /* Both LEDs OFF initially */
    *GPIOC_ODR |=  (1 << 13);
    *GPIOA_ODR &= ~(1 << 1);

    unsigned int count = 0; /* Counter variable */

    while(1)
    {
        if(!(*GPIOA_IDR & (1 << 0)))       /* Button pressed */
        {
            for(volatile int i = 0; i < 50000; i++); /* Debounce */

            if(!(*GPIOA_IDR & (1 << 0)))   /* Confirm press */
            {
                count++;                    /* Counter increment */

                /* Wait for button release */
                while(!(*GPIOA_IDR & (1 << 0)));

                /* Blink LED count times */
                for(unsigned int j = 0; j < count; j++)
                {
                    /* LED ON */
                    *GPIOC_ODR &= ~(1 << 13);
                    *GPIOA_ODR |=  (1 << 1);
                    for(volatile int i = 0; i < 200000; i++);

                    /* LED OFF */
                    *GPIOC_ODR |=  (1 << 13);
                    *GPIOA_ODR &= ~(1 << 1);
                    for(volatile int i = 0; i < 200000; i++);
                }
            }
        }
    }
}
```

---

## 🧠 Logic Explanation

### Counter Logic:
```
count = 0 (shuru mein)

Press 1: count++ → count=1 → 1 blink  ✅
Press 2: count++ → count=2 → 2 blinks ✅
Press 3: count++ → count=3 → 3 blinks ✅
Press 4: count++ → count=4 → 4 blinks ✅
Press N: count++ → count=N → N blinks ✅
```

### For Loop Blink:
```c
for(unsigned int j = 0; j < count; j++)
{
    LED ON  → delay
    LED OFF → delay
}

count=3:
j=0: blink 1
j=1: blink 2
j=2: blink 3
Done! ✅
```

### Debounce:
```
Button bounce problem:
1 physical press = 10-20 electrical signals ❌

Solution:
1. Press detect karo
2. 50ms wait karo
3. Dobara check karo
4. Confirm → count++ ✅
```

---

## 🌍 Real World Applications

---

### 🏭 1. Industrial — Production Counter
```
Button ki jagah:          LED/Output ki jagah:
──────────────────────────────────────────────
Proximity Sensor → PA0    7-Segment Display → PA1
IR Sensor        → PA0    LCD Display       → PA1
Limit Switch     → PA0    Relay             → PA1
Conveyor Switch  → PA0    Buzzer            → PA1

Real Examples:
→ Production line item counter
  (Har item pass hone pe count++)
→ Bottle filling machine
  (5 bottles = 5 blinks = tray full)
→ Packaging counter
  (10 items = box full alert)
→ Quality control counter
  (Defect count track)
→ Shift production report
  (Total items produced today)
→ Machine cycle counter
  (Maintenance reminder)
```

---

### 🚗 2. Automotive
```
Button ki jagah:          Output ki jagah:
──────────────────────────────────────────────
Wheel sensor  → PA0       Dashboard LED  → PA1
Hall sensor   → PA0       Buzzer         → PA1
Speed sensor  → PA0       Relay          → PA1

Real Examples:
→ Odometer — distance counter
→ RPM counter — engine speed
→ Lap counter — racing car
→ Gear position indicator
  (Press count = gear number)
→ Parking sensor beep count
  (1 beep = far, 5 beep = very close)
→ Fuel injection pulse counter
→ ABS pulse counter
```

---

### 🏥 3. Medical Devices
```
Button ki jagah:          Output ki jagah:
──────────────────────────────────────────────
Patient button → PA0      Alert LED    → PA1
Foot switch    → PA0      Buzzer       → PA1
Sensor         → PA0      Display      → PA1

Real Examples:
→ Patient call priority system
  (1 press = normal, 3 press = emergency)
→ Medicine dispenser counter
  (Count pills dispensed)
→ Heartbeat pulse counter
  (BPM calculation)
→ Surgical instrument counter
  (Track tools used)
→ IV drip drop counter
  (Flow rate monitoring)
→ Rehabilitation exercise counter
  (Patient exercise count)
→ Inhaler puff counter
  (Medicine dose tracking)
```

---

### 🏠 4. Smart Home / IoT
```
Button ki jagah:          Output ki jagah:
──────────────────────────────────────────────
Wall button   → PA0       Relay → AC load → PA1
Touch sensor  → PA0       LED strip      → PA1
Remote signal → PA0       Motor          → PA1

Real Examples:
→ Multi-press light control
  (1 press = dim, 2 press = medium,
   3 press = bright, 4 press = OFF)
→ Fan speed selection
  (1 press = speed 1, 2 = speed 2,
   3 = speed 3)
→ AC temperature select
  (Press count = temperature setting)
→ Scene selection
  (1 = movie mode, 2 = sleep mode,
   3 = party mode)
→ Alarm snooze counter
  (Max 3 snoozes then force wake)
→ Smart door lock code
  (Press pattern = unlock)
```

---

### 🔒 5. Security Systems
```
Button ki jagah:          Output ki jagah:
──────────────────────────────────────────────
Keypad button → PA0       Siren    → PA1
PIR sensor    → PA0       Lock     → PA1
Door sensor   → PA0       LED      → PA1

Real Examples:
→ PIN code entry system
  (Press count = digit entry)
→ Wrong attempt counter
  (3 wrong = lockout)
→ Access level selection
  (1 press = visitor,
   2 press = staff,
   3 press = admin)
→ Alarm zone counter
  (Which zone triggered)
→ Security round counter
  (Guard check-in points)
→ Safe combination lock
  (Press sequence = open)
```

---

### 🎮 6. Gaming / Entertainment
```
Button ki jagah:          Output ki jagah:
──────────────────────────────────────────────
Game button  → PA0        LED matrix  → PA1
Joystick     → PA0        Buzzer      → PA1
Coin slot    → PA0        Display     → PA1

Real Examples:
→ Score counter in games
→ Life counter (lives remaining)
→ Coin operated machine
  (Insert coins = credit count)
→ Quiz buzzer system
  (First press = answer chance)
→ Reaction time game
  (Count correct responses)
→ Simon says LED pattern
→ Slot machine counter
```

---

### 🌾 7. Agriculture
```
Button ki jagah:          Output ki jagah:
──────────────────────────────────────────────
Float switch  → PA0       Water pump → PA1
Rain sensor   → PA0       Valve      → PA1
Manual button → PA0       Motor      → PA1

Real Examples:
→ Irrigation cycle counter
  (How many times watered today)
→ Fertilizer dose counter
  (Count spray doses)
→ Egg counter in poultry
→ Fruit counting on conveyor
→ Seed planting counter
→ Harvest batch counter
```

---

### 🔬 8. Laboratory / Research
```
Button ki jagah:          Output ki jagah:
──────────────────────────────────────────────
Manual button → PA0       Display  → PA1
Sensor        → PA0       Relay    → PA1
Foot switch   → PA0       Buzzer   → PA1

Real Examples:
→ Sample counter in lab
→ Titration drop counter
  (Drops added in experiment)
→ Colony counter (biology)
→ Particle counter
→ Test repetition counter
→ Calibration cycle counter
```

---

## 📊 Button Ki Jagah Kaunse Sensors:

| Sensor | Signal | Count Trigger | Use Case |
|--------|--------|--------------|----------|
| IR Obstacle FC-51 | LOW | Object pass | Production counter |
| Reed Switch | LOW | Magnet pass | RPM counter |
| Hall Effect | LOW | Magnet | Speed counter |
| PIR Motion | HIGH | Motion detect | People counter |
| Limit Switch | LOW | Mechanical | Position counter |
| Proximity NPN | LOW | Metal detect | Industrial counter |
| Photoelectric | LOW | Beam break | Item counter |
| Vibration SW-420 | LOW | Vibration | Impact counter |
| Float Switch | LOW | Water level | Fill counter |
| Foot Switch | LOW | Foot press | Hands-free count |

---

## 📊 LED Ki Jagah Kya Laga Sakte Hain:

| Output Device | Driver | Real World Use |
|--------------|--------|---------------|
| LED | Direct | Visual count feedback |
| Buzzer | Direct | Audio count feedback |
| 7-Segment Display | 74HC595 | Number display |
| LCD 16x2 | I2C | Text count display |
| OLED Display | I2C/SPI | Graphic counter |
| Relay | Transistor | AC load control |
| Solenoid | MOSFET | Valve/lock count |
| Stepper Motor | A4988 | Count-based rotation |
| Servo Motor | PWM | Position per count |
| DC Motor | L298N | Speed per count |

---

## 💡 Counter Reset Kaise Karein:

```c
/* Long Press se Reset */
if(!(*GPIOA_IDR & (1 << 0)))
{
    for(volatile int i = 0; i < 2000000; i++); /* 2 sec wait */
    
    if(!(*GPIOA_IDR & (1 << 0))) /* Still pressed = Long press */
    {
        count = 0; /* Reset! */
        
        /* 3 fast blinks = reset confirm */
        for(int k = 0; k < 3; k++)
        {
            *GPIOC_ODR &= ~(1 << 13);
            for(volatile int i = 0; i < 100000; i++);
            *GPIOC_ODR |=  (1 << 13);
            for(volatile int i = 0; i < 100000; i++);
        }
    }
}
```

---

## 📋 Register Reference

| Register | Address | Purpose |
|----------|---------|---------|
| RCC_APB2ENR | 0x40021018 | GPIO Clock Enable |
| GPIOA_CRL | 0x40010800 | PA0-PA7 Configure |
| GPIOA_IDR | 0x40010808 | PA Input Read |
| GPIOA_ODR | 0x4001080C | PA Output Write |
| GPIOC_CRH | 0x40011004 | PC8-PC15 Configure |
| GPIOC_ODR | 0x4001100C | PC Output Write |

---

## 🎯 Key Learnings

```
✅ Counter logic — count++ concept
✅ For loop — count baar repeat karna
✅ Debounce — fake press ignore karna
✅ Wait for release — single count per press
✅ Nested loops — blink inside count loop
✅ GPIO Input + Output — same time use
✅ Real world — counter is everywhere!
```

---

## 🚀 How to Flash

```
1. Keil MDK mein code paste karo
2. Device: STM32F103C8
3. Build karo (F7)
4. Hex file generate hoga
5. STM32CubeProgrammer kholo
6. ST-Link connect karo
7. Hex file select → Download ✅
8. Button dabao — LED blinks! 🎉
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

*"Counter Logic = Embedded World ka Backbone!*
*Har counting system isi concept pe bana hai!"* 🔢🔧

</div>
