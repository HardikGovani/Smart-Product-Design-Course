# Lecture 02: Understanding Smartness and ESP32 Practical Applications

Welcome to the second lecture of the **Smart Product Design Course**! This session dives into the concept of smartness in products, explores the "10S of Smartness," and covers practical applications with ESP32 focusing on Arduino programming.

---

## Topics Covered

### **1. What is Smartness in Smart Products?**
- **Definition**: Smartness in a product refers to its ability to sense, adapt, and interact intelligently with its environment and users.
- **Core Features of Smart Products**:
  - Sensors for data collection.
  - Actuators for action based on data.
  - Connectivity for communication.
  - Intelligence (AI/ML integration) for decision-making.

### **2. 10S of Smartness**
We discussed the **10S Framework** to define smartness in products:
1. **Sensors and Actuators**: Collecting data and taking action.
2. **Seamless Connectivity**: Reliable communication between devices.
3. **Self-Automation**: Automating repetitive tasks.
4. **Smart Intelligence**: Learning and adapting over time.
5. **Simplified Interaction**: Intuitive and user-friendly interfaces.
6. **Strategic Data Utilization**: Analyzing and using data effectively.
7. **System Integration**: Compatibility with other systems.
8. **Sustainable Efficiency**: Energy efficiency and eco-friendliness.
9. **Scalable Personalization**: Tailored experiences for users.
10. **Swift Feedback**: Real-time insights and control.

### **3. ESP32 Practical Applications**
- **Review of Day 1**: Recap of blinking LED with ESP32.
- **New Topics**:
  - Input/Output programming.
  - Serial communication basics and practical applications.

---

## Resources

1. [Arduino Language Reference](https://docs.arduino.cc/language-reference/)
2. [Canva Presentation: Smartness in Smart Products](https://www.canva.com/design/DAGZvC8GSwE/SifnQp4Xn2HKL2Dp3NDjEQ/view?utm_content=DAGZvC8GSwE&utm_campaign=designshare&utm_medium=link2&utm_source=uniquelinks&utlId=hf0093edd24)
3. [ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)


## Hands-On: Serial Communication with ESP32

### **Objective**
To transmit and receive commands via Serial Communication and use them to control the onboard LED.

### **Steps Performed**
1. **Set Up Serial Communication**:
   - Explained the syntax for `Serial.begin()`, `Serial.print()`, and `Serial.read()` from the [Arduino Language Reference](https://docs.arduino.cc/language-reference/).

2. **Write the Code**:
   ```cpp
   int ledPin = 2; // Onboard LED pin

   void setup() {
     Serial.begin(9600); // Initialize Serial Communication at 9600 baud rate
     pinMode(ledPin, OUTPUT); // Set LED pin as output
   }

   void loop() {
     if (Serial.available()) { // Check if data is available to read
       char command = Serial.read(); // Read the incoming byte
       if (command == '1') {
         digitalWrite(ledPin, HIGH); // Turn LED ON
         Serial.println("LED is ON");
       } else if (command == '0') {
         digitalWrite(ledPin, LOW); // Turn LED OFF
         Serial.println("LED is OFF");
       }
     }
   }

## Arduino Programming References
From the [Arduino Language Reference](https://docs.arduino.cc/language-reference/), we covered:

### Digital I/O:
- `pinMode()`
- `digitalWrite()`
- `digitalRead()`

### Analog I/O:
- `analogRead()`
- `analogWrite()`

### Advanced I/O:
- `shiftIn()`
- `shiftOut()`
- `tone()`

### Interrupts:
- `attachInterrupt()`
- `detachInterrupt()`

### Math Functions:
- `abs()`
- `min()`
- `max()`
- `pow()`
- `sqrt()`

### Bits and Bytes:
- `bitSet()`
- `bitClear()`
- `bitRead()`
- `bitWrite()`

### Time Functions:
- `delay()`
- `millis()`
- `micros()`

### Serial Communication:
- `Serial.begin()`
- `Serial.print()`
- `Serial.read()`

---

## Instructions for Students

### Bring the Kit
- Ensure your hardware kit is ready for the next session:
  - **ESP32 Dev Kit V1**
  - Sensors, actuators, and prototyping components.

### Practice Serial Communication
1. Modify the Serial Communication code:
   - Add additional commands to blink the LED with a delay:
     - **`2`**: Fast blinking.
     - **`3`**: Slow blinking.
2. Document your observations.
3. Review the [Arduino Language Reference](https://docs.arduino.cc/language-reference/) for the topics discussed.

---

## Homework
1. **Toggle LED**:
   - Create a program to toggle the onboard LED with a single command (`t`).
2. **Display LED State**:
   - Implement a feature to display the current LED state ("ON" or "OFF") on the Serial Monitor when a command is received.
