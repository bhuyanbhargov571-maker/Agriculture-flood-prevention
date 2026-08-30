# 🌧️ Smart Rainwater Management & Crop Protection System

> **An Arduino-based smart system designed to protect agricultural fields from excessive rainfall while conserving rainwater for future use.**

---

## 📌 About the Project:

For the competition, we developed a **Smart Rainwater Management & Crop Protection System** to address a common agricultural problem: **excessive water accumulation in farm fields during heavy rainfall**.

The system detects excess water and automatically activates a water pump to transfer the collected water into an **underground or overground storage tank**. This helps protect crops from waterlogging while also conserving rainwater for future use.

---

## 🎯 Main Theme:

### 🌱 Protect Crops • 💧 Conserve Water

The main goal of this project is to:

* Prevent crops from being damaged by excessive rainfall.
* Detect excess water in agricultural fields.
* Automatically remove excess water using a water pump.
* Store the collected rainwater for future use.
* Display the water/rain level on an LCD.
* Create a simple and affordable smart-agriculture solution.

---

## 🧠 How It Works

The system uses multiple sensors and an Arduino Uno to monitor the agricultural field.

### Working Process

```text
        🌧️ Heavy Rainfall
               ↓
       💧 Water Accumulates
               ↓
       Water Level Sensor
               ↓
        Arduino Uno
               ↓
      Ultrasonic Sensor
               ↓
     Water Level Too High?
          ↙          ↘
        YES           NO
         ↓             ↓
   Relay Activated   Pump OFF
         ↓
    💧 Water Pump
         ↓
 Underground / Overground
       Storage Tank
```

### Relay Activation Logic

The pump is activated only when:

1. The digital sensor detects water availability.
2. The ultrasonic sensor detects that the water level has reached the defined threshold.

In the current program, the distance threshold is:

```cpp
#define DISTANCE_LIMIT_CM 20
```

If the measured distance is **less than 20 cm** and the digital sensor is active, the relay turns ON and operates the pump.

---

## 🔧 Components Used

| No. | Component               | Purpose                                      |
| --- | ----------------------- | -------------------------------------------- |
| 1   | **Arduino Uno**         | Main controller                              |
| 2   | **Ultrasonic Sensor**   | Measures water level/distance                |
| 3   | **Water Level Sensor**  | Detects water/rain level                     |
| 4   | **16×2 I2C LCD Module** | Displays system status and rain level        |
| 5   | **Relay Module**        | Controls the water pump                      |
| 6   | **NodeMCU ESP8266**     | Provides an option for IoT/remote monitoring |
| 7   | **Water Pump**          | Transfers excess water to a storage tank     |

---

## ⚡ Pin Configuration

### Arduino Uno

| Component          | Arduino Pin |
| ------------------ | ----------- |
| Digital Sensor     | D2          |
| Ultrasonic TRIG    | D9          |
| Ultrasonic ECHO    | D10         |
| Relay              | D7          |
| Water Level Sensor | A0          |
| LCD SDA            | A4          |
| LCD SCL            | A5          |

---

## 💻 Software & Libraries

The project is programmed using **Arduino C/C++**.

### Required Libraries

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
```

### Software

* Arduino IDE
* Arduino C/C++
* I2C LCD Library

---

## 🖥️ LCD Display

The LCD provides real-time information about the system.

### When water/rain is detected:

```text
Rain Alert
Rain Level: XX%
```

### When there is no alert:

```text
No Alert
Rain Level: XX%
```

---

## 🔌 Relay & Pump Logic

The relay module used in this project is **active LOW**.

Therefore:

```cpp
LOW  → Relay ON
HIGH → Relay OFF
```

The program starts with the pump OFF:

```cpp
digitalWrite(RELAY_PIN, HIGH);
```

The pump is activated using:

```cpp
digitalWrite(RELAY_PIN, relayActive ? LOW : HIGH);
```

---

## 📊 Sensor Data

The system reads three important values:

### 1. Digital Sensor

Determines whether water is available/detected.

```cpp
bool isAvailable = digitalRead(DIGITAL_SENSOR_PIN) == HIGH;
```

### 2. Water Level Sensor

Reads an analog value from **0–1023** and converts it into an approximate percentage:

```cpp
int analogPercent = map(analogRaw, 0, 1023, 0, 100);
```

### 3. Ultrasonic Sensor

Measures the distance between the sensor and the water surface.

```cpp
return (duration * 0.0343) / 2.0;
```

---

## 🌊 Why This Project Matters

Heavy rainfall can cause **waterlogging**, which can seriously affect agricultural fields.

Instead of allowing excess water to remain in the field, this system attempts to:

**Detect → Pump → Store → Reuse**

This provides two major benefits:

### 🌱 Crop Protection

Removing excess water can help reduce the risk of crop damage caused by water accumulation.

### 💧 Rainwater Conservation

Instead of simply wasting excess rainwater, the system transfers it to a storage tank where it can potentially be reused for agricultural purposes.

---

## 🚀 Future Improvements

This project can be expanded into a more advanced **IoT-based smart agriculture system**.

Possible improvements include:

* 📱 Mobile application for monitoring
* 🌐 Real-time IoT water-level monitoring
* 📡 Remote pump control
* ☁️ Cloud-based data storage
* 📊 Online rainfall and water-level graphs
* 🔔 Automatic alerts when water reaches critical levels
* ☀️ Solar-powered operation
* 🤖 Automated irrigation using stored rainwater
* 📍 Multiple field monitoring using multiple sensors

---

## 🏆 Science Model Competition

**Event:** Science Model Competition
**Venue:** Bahona College
**Date:** June 3rd, 2026

### Project Focus

> **Protecting agricultural crops from excessive rainfall while conserving and reusing excess rainwater.**

This project gave us an opportunity to combine **electronics, programming, sensors, automation, and environmental sustainability** into one practical model.

---

## 👨‍💻 Technologies Used

```text
Arduino
C/C++
Arduino IDE
Ultrasonic Sensor
Water Level Sensor
I2C LCD
Relay Automation
ESP8266 / NodeMCU
Water Pump
Embedded Systems
```

---

## 📁 Project Structure

```text
Smart-Rainwater-Management/
│
├── README.md
├── Smart_Rainwater_Management.ino
└── images/
    └── project-model.jpg
```

---

## 🤝 Team Project

This project was developed **together with my classmates** for the Science Model Competition at Bahona College.

It was a great learning experience in:

* Embedded programming
* Electronics
* Sensor integration
* Automation
* Problem solving
* Sustainable agriculture

---

## 💡 Conclusion

The **Smart Rainwater Management & Crop Protection System** demonstrates how simple electronics and automation can be used to address real-world agricultural problems.

By automatically detecting excess water and transferring it to a storage tank, the project combines **crop protection with rainwater conservation**.

> **“Don't let excess rainwater become a problem — turn it into a resource.”** 🌧️💧🌱

---

### ⭐ If you find this project interesting, consider giving this repository a star!

**Built with ❤️, curiosity, and a vision for smarter and more sustainable agriculture.**
