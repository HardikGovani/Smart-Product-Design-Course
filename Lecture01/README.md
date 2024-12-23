# Lecture 01: Introduction to SBCs, Arduino, and ESP32

Welcome to the first lecture of the **Smart Product Design Course**! This session focuses on understanding the fundamentals of single-board computers (SBCs), microcontrollers, and a hands-on introduction to the ESP32 microcontroller.

---

## Topics Covered

### **1. Single Board Computers (SBCs)**
We explored the concept of Single Board Computers and discussed popular examples from leading companies:
- **NVIDIA SBCs**: Designed for AI and robotics applications.
- **Intel SBCs**: Suitable for general-purpose computing and edge devices.
- **AMD SBCs**: Focused on industrial IoT and embedded systems.
- **Raspberry Pi**: Affordable and versatile SBC for education and prototyping.

### **2. Introduction to Arduino**
- **Overview**: Arduino is an open-source platform based on microcontrollers for prototyping electronic projects.
- **Arduino Board Variants**:
  - Arduino Uno (ATmega328P).
  - Arduino Nano.
  - Arduino Mega.
  - Arduino Due.
  - Arduino MKR series.
- **Structure of an Arduino Board**:
  - Power pins, digital pins, analog pins.
  - Reset button, USB interface, voltage regulators.

### **3. Arduino Pinout and Architecture**
- **Pinout**: Explanation of GPIO (General Purpose Input/Output), PWM pins, analog pins.
- **Internal Architecture**:
  - ATmega328P microcontroller.
  - Memory structure: Flash, SRAM, and EEPROM.

### **4. ESP Series Microcontrollers**
- **Overview of ESP Boards**:
  - ESP8266: Budget-friendly Wi-Fi-enabled microcontroller.
  - ESP32: Dual-core, Wi-Fi + Bluetooth-enabled microcontroller with high performance.
- **ESP32 Pinout**:
  - GPIO mapping, analog and digital pins.
  - Special functions: ADC, DAC, PWM, I2C, SPI, UART.
- **Internal Architecture of ESP32**:
  - Dual-core Tensilica Xtensa LX6 processor.
  - Integrated Wi-Fi and Bluetooth module.
  - Support for deep sleep mode for power efficiency.

---

## Hands-On: Blinking an LED with Arduino IDE
We performed a practical demonstration to blink an LED using the Arduino IDE and ESP32.

### **Steps Performed**
1. **Set Up Arduino IDE**:
   - Installed the Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software).
   - Added ESP32 board support:
     - Go to `File > Preferences` and add this URL in "Additional Board Manager URLs":
       ```
       https://dl.espressif.com/dl/package_esp32_index.json
       ```
     - Installed ESP32 boards from `Tools > Board > Boards Manager`.

2. **Write and Upload Code**:
   ```cpp
   // Blink LED example for ESP32
   int ledPin = 2; // Onboard LED pin for most ESP32 boards

   void setup() {
     pinMode(ledPin, OUTPUT); // Set LED pin as output
   }

   void loop() {
     digitalWrite(ledPin, HIGH); // Turn LED on
     delay(1000);               // Wait for 1 second
     digitalWrite(ledPin, LOW);  // Turn LED off
     delay(1000);               // Wait for 1 second
   }

   ## PPT
View the presentation for this lecture here:  
[Canva Presentation: Introduction to SBCs and ESP32](https://www.canva.com/design/DAGaFg3P0lY/v-k6KEFTbCdkch6BeSIkzA/view?utm_content=DAGaFg3P0lY&utm_campaign=designshare&utm_medium=link2&utm_source=uniquelinks&utlId=h69fb54b8e3)

---

## Uploaded the Code to ESP32
- Observed the onboard LED blinking.

---

## Explanation of `setup()` and `loop()`
### `setup()`
- Runs once at the start of the program.
- Used to initialize pins, variables, and settings.

### `loop()`
- Executes repeatedly.
- Used for the main logic of the program.

---

## Instructions for Students
### Bring the Kit
- Ensure you have the hardware kit for the next session.
  - **Kit Includes**:
    - **ESP32 Dev Kit V1**.
    - Sensors: **DHT11, Ultrasonic, etc.**.
    - Actuators: **Servo Motor, Buzzer, etc.**.
    - Prototyping components: **breadboard, jumper wires, etc.**.

### Set Up Arduino IDE
- Install the IDE and set up ESP32 board support if not already done.
- Refer to the steps provided above or visit the [Arduino Setup Guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).

---

## Homework
1. Modify the LED blinking program:
   - Change the blinking interval to **500ms**.
   - Use a second GPIO pin to blink another LED alternately.
2. Document your observations and share them in the class repository.
