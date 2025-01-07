# TinkerCad Circuits - Day 6

## Overview
Welcome to Day 6! Today, we will explore advanced Arduino features, focusing on:

- Arduino Serial Communication
- Analog Read and Analog Write
- Arduino ADC with a Potentiometer
- PWM (Pulse Width Modulation) for LED Brightness Control
- Servo Motor Control
- Vibration Motor
- LDR (Light Dependent Resistor)

### Practical Exercises:
1. Control a Servo Motor with a Potentiometer
2. LED Brightness Control using PWM
3. LDR-based Lamp ON/OFF
4. RGB LED Control
5. NeoPixel LED Strip Control with Potentiometer

## Practical 1: Control Servo Motor with Potentiometer

### Objective
Use a potentiometer to control the angle of a servo motor.

### Circuit
1. Connect the servo motor's signal pin to pin 9 of the Arduino.
2. Connect the potentiometer's middle pin to A0, one side to 5V, and the other to GND.

### Code
```cpp
#include <Servo.h>

Servo myServo;
int potPin = A0; // Potentiometer connected to A0
int potValue = 0;
int angle = 0;

void setup() {
  myServo.attach(9); // Servo attached to pin 9
  Serial.begin(9600); // Start Serial Communication
}

void loop() {
  potValue = analogRead(potPin); // Read potentiometer value
  angle = map(potValue, 0, 1023, 0, 180); // Map to servo angle
  myServo.write(angle); // Move servo
  Serial.println(angle); // Print angle to Serial Monitor
  delay(50);
}
```

---

## Practical 2: LED Brightness Control using PWM

### Objective
Control the brightness of an LED using a potentiometer and PWM.

### Circuit
1. Connect the LED's positive terminal to pin 6 via a 220-ohm resistor.
2. Connect the potentiometer as described in Practical 1.

### Code
```cpp
int potPin = A0;
int ledPin = 6;
int potValue = 0;
int brightness = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  potValue = analogRead(potPin);
  brightness = map(potValue, 0, 1023, 0, 255); // Map to PWM range
  analogWrite(ledPin, brightness); // Control LED brightness
  Serial.println(brightness);
  delay(50);
}
```

---

## Practical 3: LDR-based Lamp ON/OFF

### Objective
Turn an LED on or off based on the light intensity detected by an LDR.

### Circuit
1. Connect the LDR to A0 and GND, with a 10k-ohm pull-down resistor to GND.
2. Connect the LED to pin 13 via a 220-ohm resistor.

### Code
```cpp
int ldrPin = A0;
int ledPin = 13;
int threshold = 500;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);
  if (ldrValue < threshold) {
    digitalWrite(ledPin, HIGH); // Turn the LED on
  } else {
    digitalWrite(ledPin, LOW); // Turn the LED off
  }
  delay(100);
}
```

---

## Practical 4: RGB LED Control

### Objective
Control the color of an RGB LED using three potentiometers.

### Circuit
1. Connect the RGB LED's red, green, and blue pins to pins 9, 10, and 11, each with a 220-ohm resistor.
2. Connect three potentiometers to A0, A1, and A2.

### Code
```cpp
int redPin = 9;
int greenPin = 10;
int bluePin = 11;
int redPot = A0;
int greenPot = A1;
int bluePot = A2;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int redValue = analogRead(redPot);
  int greenValue = analogRead(greenPot);
  int blueValue = analogRead(bluePot);

  analogWrite(redPin, map(redValue, 0, 1023, 0, 255));
  analogWrite(greenPin, map(greenValue, 0, 1023, 0, 255));
  analogWrite(bluePin, map(blueValue, 0, 1023, 0, 255));

  delay(50);
}
```

---

## Practical 5: NeoPixel LED Strip Control with Potentiometer

### Objective
Control the brightness and color of a NeoPixel LED strip using a potentiometer.

### Circuit
1. Connect the NeoPixel data pin to pin 6.
2. Use a 470-ohm resistor between the data pin and the strip.
3. Connect a potentiometer as described in Practical 1.

### Code
```cpp
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_LEDS 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
int potPin = A0;

void setup() {
  strip.begin();
  strip.show();
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);
  int brightness = map(potValue, 0, 1023, 0, 255);

  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(brightness, 0, 255 - brightness));
  }

  strip.show();
  delay(50);
}
```

---

## Homework

### Task 1: Advanced Servo Control
Use a potentiometer to control the servo motor, but introduce acceleration and deceleration effects using a delay proportional to the difference between the previous and current positions.

### Task 2: Create a Night Lamp
Using an LDR, turn on an RGB LED with a soft red color in low light and a green color in bright light.

### Task 3: Custom NeoPixel Pattern
Create a pattern on the NeoPixel strip where LEDs light up in a rainbow effect as the potentiometer value changes.

---

