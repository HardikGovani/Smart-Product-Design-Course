# TinkerCad Circuits - Day 8

## Overview
Welcome to Day 8! Today, we will work with LCD displays, sensors, and piezo buzzers to build advanced projects using Arduino. The focus will be on:

- **4-bit LCD (16x2) Interface**
- **I2C 16x2 LCD Scrolling Display**
- **Gas Sensor/Air Quality Monitoring**
- **Force Sensor (FSR)**: Measure force in Newtons and display the value.
- **Flex Sensor**: Measure bending angle and display the result.
- **Piezo Buzzer**: Generate different tones, including melody and piano-like sound effects.

## Practical Exercises

### Practical 1: 4-bit 16x2 LCD - "Hello, World!"

#### Objective
Display "Hello, World!" on a 16x2 LCD using a 4-bit interface.

#### Circuit
1. Connect the 16x2 LCD's data pins (D4-D7) to Arduino pins 7, 8, 9, and 10.
2. Connect RS to pin 12 and EN to pin 11.
3. Connect a 10k potentiometer to adjust contrast.

#### Code
```cpp
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 7, 8, 9, 10);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Hello, World!");
}

void loop() {
}
```

---

### Practical 2: I2C 16x2 LCD - Scrolling Text

#### Objective
Display scrolling text on a 16x2 LCD using the I2C interface.

#### Circuit
1. Connect the I2C LCD's SDA and SCL pins to A4 and A5 (or dedicated SDA/SCL pins).

#### Code
```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin();
  lcd.print("Scrolling Text!");
}

void loop() {
  for (int position = 0; position < 16; position++) {
    lcd.scrollDisplayLeft();
    delay(300);
  }
}
```

---

### Practical 3: Gas Sensor for Air Quality

#### Objective
Monitor air quality and display the gas sensor readings on an I2C LCD.

#### Circuit
1. Connect the gas sensor's analog output to A0.
2. Connect the I2C LCD as described above.

#### Code
```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int gasPin = A0;

void setup() {
  lcd.begin();
  lcd.print("Air Quality:");
}

void loop() {
  int gasValue = analogRead(gasPin);
  float ppm = gasValue * (5.0 / 1023.0) * 100; // Convert to ppm (example formula)

  lcd.setCursor(0, 1);
  lcd.print(ppm);
  lcd.print(" ppm");
  delay(1000);
}
```

---

### Practical 4: Force Sensor (FSR)

#### Objective
Measure force in Newtons using an FSR and display the value on an I2C LCD.

#### Circuit
1. Connect the FSR's analog output to A1.

#### Code
```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int fsrPin = A1;

void setup() {
  lcd.begin();
  lcd.print("Force Sensor:");
}

void loop() {
  int fsrValue = analogRead(fsrPin);
  float force = fsrValue * (5.0 / 1023.0) * 10; // Example formula for Newtons

  lcd.setCursor(0, 1);
  lcd.print(force);
  lcd.print(" N");
  delay(1000);
}
```

---

### Practical 5: Flex Sensor

#### Objective
Measure the bending angle of a flex sensor and display it on an I2C LCD.

#### Circuit
1. Connect the flex sensor's analog output to A2.

#### Code
```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int flexPin = A2;

void setup() {
  lcd.begin();
  lcd.print("Flex Sensor:");
}

void loop() {
  int flexValue = analogRead(flexPin);
  float angle = map(flexValue, 0, 1023, 0, 180);

  lcd.setCursor(0, 1);
  lcd.print(angle);
  lcd.print(" deg");
  delay(1000);
}
```

---

### Practical 6: Piezo Buzzer Melody

#### Objective
Generate a melody using a piezo buzzer.

# Musical Note Frequencies

This document provides a reference for the frequencies of common musical notes. These frequencies can be used to generate tones with a piezo buzzer in Arduino or other projects.

## Common Note Frequencies

| Note | Frequency (Hz) |
|------|----------------|
| C4   | 262            |
| D4   | 294            |
| E4   | 330            |
| F4   | 349            |
| G4   | 392            |
| A4   | 440            |
| B4   | 494            |

## Usage in Arduino

You can use these frequencies with the `tone()` function to play specific musical notes on a piezo buzzer. Example:

```cpp
int buzzer = 3; // Connect piezo buzzer to pin 3

void setup() {
}

void loop() {
  tone(buzzer, 262); // Play note C4
  delay(500);        // Delay for 500 ms
  tone(buzzer, 294); // Play note D4
  delay(500);
  tone(buzzer, 330); // Play note E4
  delay(500);
  noTone(buzzer);    // Stop the buzzer
}
```

## Notes
- These frequencies correspond to the standard Western musical scale.
- You can combine these notes to create melodies, scales, or sound effects in your projects.


#### Circuit
1. Connect the piezo buzzer to pin 3.

#### Code
```cpp
int buzzer = 3;

void setup() {
}

void loop() {
  tone(buzzer, 262); // C note
  delay(500);
  tone(buzzer, 294); // D note
  delay(500);
  tone(buzzer, 330); // E note
  delay(500);
  tone(buzzer, 349); // F note
  delay(500);
  tone(buzzer, 392); // G note
  delay(500);
  noTone(buzzer);
}
```

---

### Practical 7: Piezo Buzzer Piano

#### Objective
Create a mini piano using push buttons and a piezo buzzer.

#### Circuit
1. Connect 5 push buttons to pins 4, 5, 6, 7, and 8.
2. Connect the piezo buzzer to pin 3.

#### Code
```cpp
int buzzer = 3;
int buttons[] = {4, 5, 6, 7, 8};
int notes[] = {262, 294, 330, 349, 392};

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
}

void loop() {
  for (int i = 0; i < 5; i++) {
    if (digitalRead(buttons[i]) == LOW) {
      tone(buzzer, notes[i]);
    }
  }
  noTone(buzzer);
}
```

---

## Homework

### Task 1: Combine Practical 3 and 5
Combine the gas sensor and flex sensor to display both air quality and bending angle on the same I2C LCD.

### Task 2: Advanced Melody
Modify Practical 6 to play a complete melody like "Happy Birthday."

### Task 3: Force-Based Buzzer Control
Use the FSR to control the frequency of a piezo buzzer.

### Task 4: Flex Sensor Piano
Use the flex sensor to adjust the tone of the piezo buzzer dynamically.

---

This repository contains exercises for advanced Arduino projects using sensors and modules:

1. 4-bit LCD Display
2. I2C 16x2 LCD Scrolling
3. Gas Sensor for Air Quality Monitoring
4. Force Sensor (FSR) for Measuring Force
5. Flex Sensor for Bending Angle Measurement
6. Piezo Buzzer for Melody Generation
7. Piezo Buzzer Piano with Buttons

### Files
- `practical1_4bit_lcd.ino`
- `practical2_i2c_lcd.ino`
- `practical3_gas_sensor.ino`
- `practical4_fsr.ino`
- `practical5_flex_sensor.ino`
- `practical6_buzzer_melody.ino`
- `practical7_buzzer_piano.ino`

---
