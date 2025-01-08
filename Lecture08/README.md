# TinkerCad Circuits - Day 7

## Overview
Welcome to Day 7! Today, we will explore advanced sensors and their applications in Arduino-based systems. The sensors and modules covered include:

### Sensors and Modules
1. **Soil Moisture Sensor**: Measures the moisture content in the soil for applications like auto irrigation.
2. **PIR Sensor**: Detects motion for security or automation purposes.
3. **Ultrasonic Sensor**: Measures distance and can be used for object detection.
4. **LM35 Temperature Sensor**: Measures temperature in Celsius with a linear output.
5. **Gas Sensor**: Detects the presence of specific gases (e.g., methane, LPG).
6. **LCD 16x2**: Displays data, such as sensor readings, on a 16x2 character screen.
7. **Single Seven Segment Display**: Displays numeric values.
8. **Clock Display**: Real-time clock module for displaying current time.

## Practical Exercises

### Practical 1: PIR Sensor with Servo Motor for Door Automation

#### Objective
Use a PIR sensor to detect motion and open/close a door using a servo motor.

#### Circuit
1. Connect the PIR sensor's output to digital pin 2.
2. Connect the servo motor's signal pin to pin 9.

#### Code
```cpp
#include <Servo.h>

Servo doorServo;
int pirPin = 2;
int motionDetected = 0;

void setup() {
  pinMode(pirPin, INPUT);
  doorServo.attach(9);
  doorServo.write(0); // Door closed position
}

void loop() {
  motionDetected = digitalRead(pirPin);
  if (motionDetected) {
    doorServo.write(90); // Open the door
    delay(5000);         // Wait for 5 seconds
    doorServo.write(0);  // Close the door
  }
  delay(200);
}
```

---

### Practical 2: Soil Moisture Sensor for Auto Irrigation

#### Objective
Automatically turn a DC pump on or off based on soil moisture levels.

#### Circuit
1. Connect the soil moisture sensor's output to analog pin A0.
2. Connect a relay module to control the DC pump, with its signal pin connected to pin 8.

#### Code
```cpp
int moisturePin = A0;
int relayPin = 8;
int moistureLevel = 0;
int threshold = 500; // Adjust based on sensor calibration

void setup() {
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  moistureLevel = analogRead(moisturePin);
  Serial.println(moistureLevel);
  if (moistureLevel < threshold) {
    digitalWrite(relayPin, HIGH); // Turn on the pump
  } else {
    digitalWrite(relayPin, LOW);  // Turn off the pump
  }
  delay(1000);
}
```

---

### Practical 3: Ultrasonic Sensor with NeoPixel Strip

#### Objective
Map the distance measured by an ultrasonic sensor to a NeoPixel LED strip.

#### Circuit
1. Connect the ultrasonic sensor's trigger pin to pin 5 and echo pin to pin 6.
2. Connect the NeoPixel data pin to pin 7.

#### Code
```cpp
#include <Adafruit_NeoPixel.h>

#define TRIG_PIN 5
#define ECHO_PIN 6
#define NEOPIXEL_PIN 7
#define NUM_LEDS 20

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  strip.begin();
  strip.show();
  Serial.begin(9600);
}

long measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  return pulseIn(ECHO_PIN, HIGH) * 0.034 / 2; // Convert to cm
}

void loop() {
  long distance = measureDistance();
  int numLeds = map(distance, 0, 100, 0, NUM_LEDS); // Map distance to LEDs
  strip.clear();
  for (int i = 0; i < numLeds; i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0)); // Green LEDs
  }
  strip.show();
  delay(100);
}
```

---

### Advanced Practical 1: LM35 Temperature Sensor

#### Objective
Display temperature readings on an LCD.

#### Circuit
1. Connect the LM35's output to A0.
2. Connect the LCD to the Arduino using I2C or regular pin connections.

#### Code
```cpp
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int tempPin = A0;
float tempC = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Temperature:");
}

void loop() {
  int value = analogRead(tempPin);
  tempC = (value * 5.0 / 1023.0) * 100; // Convert to Celsius
  lcd.setCursor(0, 1);
  lcd.print(tempC);
  lcd.print(" C");
  delay(1000);
}
```

---

### Advanced Practical 2: Gas Sensor

#### Objective
Trigger an alert when gas levels exceed a threshold.

#### Circuit
1. Connect the gas sensor's analog output to A1.

#### Code
```cpp
int gasPin = A1;
int threshold = 300;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int gasLevel = analogRead(gasPin);
  Serial.println(gasLevel);
  if (gasLevel > threshold) {
    Serial.println("Gas detected!");
  }
  delay(500);
}
```

---
