# ESP32 Serial Bluetooth (SerialBT) Guide

## Overview
In this tutorial, we will explore the **ESP32 Serial Bluetooth (SerialBT)** feature, which allows communication between an ESP32 microcontroller and a mobile device via Bluetooth. We will use the **Serial Bluetooth Terminal** app on Android for this communication.

### Mobile App:
[Download Serial Bluetooth Terminal](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal&hl=en_IN)

## Setting Up Serial Bluetooth on ESP32
ESP32 has built-in Bluetooth capabilities, making it easy to use the **Bluetooth Serial (SerialBT)** library for wireless communication.

### Features Covered:
1. ESP32 continuously transmits "Hello World" to the Bluetooth Android app.
2. ESP32 responds to user input (Hi -> Hello conversation and more).
3. LED control via mobile commands.
4. Servo motor control via received commands.
5. Exercise: ESP32 plays a buzzer tone based on the text received from the app.

---

## 1. Continuous "Hello World" Transmission

### Circuit:
- No additional hardware is required.

### Code:
```cpp
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  SerialBT.begin("ESP32_BT"); // Bluetooth device name
}

void loop() {
  SerialBT.println("Hello World");
  delay(1000);
}
```

---

## 2. Hi-Hello Conversation with More Responses

### Code:
```cpp
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
String receivedData;

void setup() {
  SerialBT.begin("ESP32_BT");
}

void loop() {
  if (SerialBT.available()) {
    receivedData = SerialBT.readString();
    receivedData.trim();
    
    if (receivedData == "Hi") {
      SerialBT.println("Hello");
    } else if (receivedData == "How are you?") {
      SerialBT.println("I'm fine, thank you!");
    } else if (receivedData == "What is your name?") {
      SerialBT.println("I am ESP32.");
    } else {
      SerialBT.println("I didn't understand that.");
    }
  }
}
```

---

## 3. LED On/Off via Mobile App

### Circuit:
- Connect an LED to **GPIO 2** (with a 220Ω resistor in series).

### Code:
```cpp
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
const int ledPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  SerialBT.begin("ESP32_BT");
}

void loop() {
  if (SerialBT.available()) {
    String command = SerialBT.readString();
    command.trim();
    
    if (command == "LED ON") {
      digitalWrite(ledPin, HIGH);
      SerialBT.println("LED is ON");
    } else if (command == "LED OFF") {
      digitalWrite(ledPin, LOW);
      SerialBT.println("LED is OFF");
    }
  }
}
```

---

## 4. Servo Motor Control via Mobile App

### Circuit:
- Connect a **Servo Motor (SG90)** signal pin to **GPIO 5**.

### Code:
```cpp
#include "BluetoothSerial.h"
#include <Servo.h>

BluetoothSerial SerialBT;
Servo myServo;

void setup() {
  SerialBT.begin("ESP32_BT");
  myServo.attach(5);
}

void loop() {
  if (SerialBT.available()) {
    String command = SerialBT.readString();
    int angle = command.toInt();
    if (angle >= 0 && angle <= 180) {
      myServo.write(angle);
      SerialBT.println("Servo moved to " + String(angle) + " degrees");
    }
  }
}
```

---

## Exercise: Buzzer Tone Based on Text Sent from Mobile

### Circuit:
- Connect a **Piezo Buzzer** to **GPIO 4**.

### Code:
```cpp
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
const int buzzerPin = 4;

void setup() {
  SerialBT.begin("ESP32_BT");
  pinMode(buzzerPin, OUTPUT);
}

void playTone(int frequency, int duration) {
  tone(buzzerPin, frequency, duration);
  delay(duration);
  noTone(buzzerPin);
}

void loop() {
  if (SerialBT.available()) {
    String command = SerialBT.readString();
    command.trim();
    
    if (command == "A") {
      playTone(440, 500);
    } else if (command == "B") {
      playTone(494, 500);
    } else if (command == "C") {
      playTone(523, 500);
    } else {
      SerialBT.println("Unknown command");
    }
  }
}
```

---

### Exercises
- Modify the buzzer example to generate different melodies based on user input.
- Implement a Bluetooth-controlled fan using a DC motor and an H-Bridge.

---

This tutorial should provide students with a solid understanding of **ESP32 Serial Bluetooth Communication** and practical implementations. 🚀
