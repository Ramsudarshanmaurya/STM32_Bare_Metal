# ⚡ STM32F103 Bare Metal Programming
### Direct Register Access | No HAL | No Library | Keil MDK | Real Hardware Tested

<div align="center">

![STM32](https://img.shields.io/badge/MCU-STM32F103C6/C8-03234B?style=for-the-badge&logo=stmicroelectronics&logoColor=white)
![Bare Metal](https://img.shields.io/badge/Programming-Bare_Metal_C-FF6600?style=for-the-badge)
![Keil](https://img.shields.io/badge/IDE-Keil_MDK-003366?style=for-the-badge)
![Hardware](https://img.shields.io/badge/Tested-Real_Hardware-green?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-brightgreen?style=for-the-badge)

</div>

---

## 📌 About This Repository

This repository contains **STM32F103 Bare Metal C programs** written without HAL or any library.
All programs use **direct register manipulation** — the real way of embedded programming.
Every program is **tested on real hardware** (Blue Pill STM32F103C8).

> **"Bare Metal = Direct Hardware Control = Real Embedded Engineering!"**

---

## 🛠️ Hardware Setup

| Component | Details |
|-----------|---------|
| MCU Board | STM32F103C6/C8T6 — Blue Pill |
| IDE | Keil MDK uVision 5 |
| Programmer | ST-Link V2 + STM32CubeProgrammer |
| Input | Push Button |
| Output | Built-in LED (PC13) + External LED (PA1) |
| Power | 5V USB / 3.3V |

### ⚠️ Flash Note:
```
Clone Blue Pill boards mein:
→ Keil direct flash → "Not genuine ST device" error
→ Solution: STM32CubeProgrammer use karo ✅
→ Build in Keil → Hex generate → Flash via CubeProgrammer
```

---

## 📁 Repository Structure

```
STM32_Bare_Metal/
├── 📂 1_LED_Blink/
│   ├── 1_blink_led.c
│   ├── README.md
│   └── 📂 media/
│       ├── led_blink.jpg
│       └── led_blink.mp4
│
├── 📂 2_Button_LED/
│   ├── 2_button_led.c
│   ├── README.md
│   └── 📂 media/
│       ├── button_led.jpg
│       └── button_led.mp4
│
├── 📂 3_Button_Toggle/
│   ├── 3_button_toggle.c
│   ├── README.md
│   └── 📂 media/
│       ├── button_toggle.jpg
│       └── button_toggle.mp4
│
├── 📂 4_Button_Count/
│   ├── 4_button_count.c
│   ├── README.md
│   └── 📂 media/
│       ├── button_count.jpg
│       └── button_count.mp4
│
└── 📄 README.md  ← You are here!
```

---

## 📚 Programs List

### ✅ 1. LED Blink
```
File     : 1_LED_Blink/1_blink_led.c
Pin      : PC13 (Built-in LED)
Logic    : GPIO Output — Toggle with delay
Concept  : RCC Clock + GPIO Config + ODR
```
**What it does:** Built-in LED blinks every 500ms — the "Hello World" of STM32!

---

### ✅ 2. Button Press → LED ON
```
File     : 2_Button_LED/2_button_led.c
Input    : PA0 (Button — Internal Pull-up)
Output   : PC13 + PA1 (Built-in + External LED)
Logic    : GPIO Input read → GPIO Output control
Concept  : IDR register + Pull-up + Active LOW
```
**What it does:** Press button → Both LEDs ON. Release → Both LEDs OFF.

---

### ✅ 3. Button Toggle LED
```
File     : 3_Button_Toggle/3_button_toggle.c
Input    : PA0 (Button)
Output   : PC13 + PA1 (Both LEDs)
Logic    : XOR Toggle + Debounce + Wait release
Concept  : led_state ^= 1 toggle logic
```
**What it does:** 1st press → LEDs ON. 2nd press → LEDs OFF. Toggle every press.

---

### ✅ 4. Button Count → LED Blink
```
File     : 4_Button_Count/4_button_count.c
Input    : PA0 (Button)
Output   : PC13 + PA1 (Both LEDs)
Logic    : count++ per press → blink count times
Concept  : Counter + nested for loop + debounce
```
**What it does:** Press 1→1 blink, Press 2→2 blinks, Press N→N blinks!

---

## 🔌 Pin Reference

| Pin | Mode | Connected To |
|-----|------|-------------|
| PC13 | Output (Active LOW) | Built-in LED |
| PA0 | Input Pull-up | Push Button → GND |
| PA1 | Output (Active HIGH) | External LED → GND |

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

## 🧠 Key Concepts Covered

```
✅ RCC Clock Enable        — GPIO use se pehle zaroori
✅ CRL/CRH Register        — GPIO pin configure karta hai
✅ IDR Register            — Input pin state padhna
✅ ODR Register            — Output pin control karna
✅ Active LOW Logic        — PC13 mein LOW = LED ON
✅ Internal Pull-up        — No external resistor needed
✅ Software Debounce       — Fake button press ignore
✅ XOR Toggle Logic        — led_state ^= 1
✅ Counter Logic           — count++ per press
✅ Volatile Keyword        — Hardware register safety
```

---

## 🚀 How to Use

```
Step 1: Clone this repository
        git clone https://github.com/Ramsudarshanmaurya/STM32_Bare_Metal

Step 2: Open Keil MDK

Step 3: New Project → Select STM32F103C8

Step 4: Add .c file from any folder

Step 5: Build (F7) → Hex file generate

Step 6: Open STM32CubeProgrammer
        → Connect ST-Link
        → Select hex file
        → Download ✅

Step 7: Test on hardware! 🎉
```

---

## 🌍 Real World Relevance

```
Program 1 — LED Blink:
→ Status indicators, PWM switching,
  relay control, automotive signals

Program 2 — Button LED:
→ Machine start/stop, door bell,
  manual override systems

Program 3 — Button Toggle:
→ Smart switches, fan control,
  light dimmer, security systems

Program 4 — Button Count:
→ Production counter, floor selector,
  menu navigation, multi-press control
```

---

## 👨‍💻 Developer

**Ramsudarshan Maurya**
🎓 B.Tech ECE — AKTU Lucknow (2025) | CGPA: 7.4
🏢 Embedded Systems Intern — UniConverge Technologies, Noida
📚 IoT Trainee — IoT Academy, Noida
🏆 RoboRace Competition 1st Prize — BIT Gorakhpur
📄 Published Researcher — IJRPR Journal Vol 6, Issue 4, April 2025

[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=flat&logo=linkedin&logoColor=white)](https://linkedin.com/in/ramsudarshanmaurya)
[![GitHub](https://img.shields.io/badge/GitHub-181717?style=flat&logo=github&logoColor=white)](https://github.com/Ramsudarshanmaurya)
[![Gmail](https://img.shields.io/badge/Gmail-D14836?style=flat&logo=gmail&logoColor=white)](mailto:ramsudarshanmaurya@gmail.com)

---

## 📄 License

MIT License — Free to use, modify and distribute with attribution.

---

<div align="center">

**⭐ Agar helpful laga toh Star zaroor do! ⭐**

*"Bare Metal Programming = Real Embedded Engineering!*
*No shortcuts — Direct Hardware Control!"* ⚡🔧

</div>
