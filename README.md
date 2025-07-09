# ESP8266 + VL53L0X + KY-040 Interface Module

A modular microcontroller interface combining proximity sensing and rotary input for responsive control environments.

## 📦 Components
- ESP8266 Module (e.g., NodeMCU, ESP-12E)
- VL53L0X Time-of-Flight Sensor
- KY-040 Rotary Encoder with Push Button
- Status LED

## 🧭 Wiring Overview

| Signal | ESP8266 GPIO | Connected Device |
|--------|--------------|------------------|
| SDA    | GPIO4        | VL53L0X          |
| SCL    | GPIO5        | VL53L0X          |
| Encoder A | GPIO12    | KY-040           |
| Encoder B | GPIO13    | KY-040           |
| Button   | GPIO14     | KY-040           |
| LED      | GPIO2      | Indicator        |

## 🧠 Interaction Logic
- **VL53L0X** triggers proximity events
- **KY-040** detects rotational and button-based input
- **LED** provides feedback for input acknowledgement or system states

## 🚀 Firmware Guide
- Platform: Arduino (ESP8266)
- Libraries:
  - `VL53L0X`
  - `ESP8266WiFi` (optional)
  - Debounce logic for encoder
- Pin definitions aligned with schematic

## 🎨 Schematic
![ESP8266 VL53L0X and KY-040 Wiring Diagram](schematic_annotated.png)

## 🛠️ Builder Notes
- Ensure VL53L0X operates at 3.3V
- Add pull-up resistors if encoder signals fluctuate
- Modular for integration into UI nodes or Monolith interactions

## 📄 Attribution
Design by Professor Damian Williamson Grad.  
Schematic and firmware scaffolding by [Willtech](https://github.com/Willtech/Sensor_VL53L0X)
