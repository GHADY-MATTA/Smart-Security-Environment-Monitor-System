# 🔐 Smart Security & Environment Monitor System (ESP8266 + Blynk + Google Assistant)

This project is a full-featured smart home security and monitoring system powered by the **ESP8266**. It integrates:

- 🔢 **PIN-based keypad lock**
- 🔄 **Servo-controlled door lock**
- 🌡️ **DHT11 temperature & humidity sensor**
- 💧 **Soil moisture monitoring**
- 🚨 **Motion detection with RGB LED alerts**
- 🌈 **RGB LED feedback**
- 📱 **Remote monitoring & control via Blynk**
- 🎙️ **Voice control with Google Assistant + Google Home**

---

## 📸 Demo

![Demo GIF](mpu-working.gif)

---

## 🚀 Features

| Component            | Function                                                                 |
|----------------------|--------------------------------------------------------------------------|
| `Keypad`             | 4x4 matrix for secure PIN entry                                          |
| `Servo Motor`        | Controls lock/unlock mechanism                                           |
| `DHT11 Sensor`       | Monitors temperature and humidity                                        |
| `Moisture Sensor`    | Checks soil/water level to trigger alerts                               |
| `Motion Sensor`      | Detects movement and activates RGB LED patterns                         |
| `RGB LED`            | Displays different states using colors                                   |
| `Blynk App`          | Real-time data display + remote control                                  |
| `Google Assistant`   | Turn ON/OFF devices via voice commands                                   |
| `Google Home`        | Integrated with Blynk via IFTTT or Webhooks for seamless automation     |

---

## 🧠 System Overview

- Secure your space with a **4-digit PIN**.
- Get notified and control your home via **Blynk mobile app**.
- Use **voice commands** like:
  > “Hey Google, turn on the pump” or “turn off alarm lights”
- Fully automated logic to lock/unlock doors, trigger alerts, and monitor environment conditions.

---

## 🧰 Hardware Used

- ESP8266 NodeMCU
- 4x4 Keypad
- Servo motor (SG90 or similar)
- DHT11 Sensor
- Moisture sensor
- PIR Motion sensor
- RGB LED (or 3 LEDs for R/G/B)
- Optional: Relay for appliances
- Internet (Wi-Fi)

---

## 🧪 How It Works

1. 🔐 **Startup**: User is prompted to enter a PIN. If correct, system unlocks the door via servo.
2. 🌡️ **Environmental Sensors**:
   - DHT11 → Logs temp/humidity to Blynk
   - Moisture sensor → Triggers alerts
3. 🚨 **Security**:
   - Motion triggers RGB warning cycles.
   - Alarm is enabled/disabled with a secure PIN.
4. 📱 **Remote Control**:
   - Real-time dashboard via **Blynk app**
   - Voice commands via **Google Assistant** (through Blynk or IFTTT)

---

## 🔗 Integration

### Blynk Setup

- Use virtual pins:
  - `V0`: Temperature
  - `V1`: Humidity
  - `V2`: Moisture status
  - `V3`: LED or pump control (can be toggled by Google)

### Google Assistant Integration

1. Create an IFTTT applet:
   - **Trigger**: Google Assistant voice command
   - **Action**: Webhook → Blynk API call
2. Example:
   - `https://blynk.cloud/external/api/update?token=YOUR_TOKEN&V3=1` to turn ON pump
   - `...&V3=0` to turn it OFF

---

## 💻 Code Example (Excerpt)

```cpp
Blynk.virtualWrite(V0, temperature);
Blynk.virtualWrite(V1, humidity);

BLYNK_WRITE(V3) {
  int value = param.asInt();
  digitalWrite(pumpPin, value);
}
