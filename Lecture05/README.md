# TinkerCad Circuits - Day 5

## Overview
Welcome to Day 5 of learning TinkerCad circuits and Arduino programming! Today, we will cover the basics of Arduino GPIO (General Purpose Input/Output), including:

- GPIO syntax
- Pull-up and pull-down resistors
- Basic Arduino syntax

We will practice these concepts using four examples:

1. LED Blinking
2. Switch-controlled LED Blinking
3. LED Pattern Sequencing
4. Multi-input Control (Switch and Button)

Students will have homework to reinforce these concepts.


## Example 1: LED Blinking

### Objective
Learn how to make an LED blink on and off at regular intervals using Arduino.

### Circuit
1. Connect an LED to digital pin 13 through a 220-ohm resistor.
2. Connect the other terminal of the resistor to the ground (GND).

### Code
```cpp
// Example 1: LED Blinking

void setup() {
  pinMode(13, OUTPUT); // Set pin 13 as output
}

void loop() {
  digitalWrite(13, HIGH); // Turn the LED on
  delay(1000);            // Wait for 1 second
  digitalWrite(13, LOW);  // Turn the LED off
  delay(1000);            // Wait for 1 second
}
```

---

## Example 2: Switch-controlled LED Blinking

### Objective
Control an LED using a push-button switch.

### Circuit
1. Connect a push-button switch to digital pin 2 with a pull-up resistor.
2. Connect an LED to digital pin 13 through a 220-ohm resistor.

### Code
```cpp
// Example 2: Switch-controlled LED Blinking

const int switchPin = 2;
const int ledPin = 13;

void setup() {
  pinMode(switchPin, INPUT_PULLUP); // Set pin 2 as input with pull-up resistor
  pinMode(ledPin, OUTPUT);          // Set pin 13 as output
}

void loop() {
  if (digitalRead(switchPin) == LOW) { // Check if the button is pressed
    digitalWrite(ledPin, HIGH);        // Turn the LED on
  } else {
    digitalWrite(ledPin, LOW);         // Turn the LED off
  }
}
```

---

## Example 3: LED Pattern Sequencing

### Objective
Create a pattern with three LEDs.

### Circuit
1. Connect three LEDs to digital pins 8, 9, and 10, each through a 220-ohm resistor.

### Code
```cpp
// Example 3: LED Pattern Sequencing

const int ledPins[] = {8, 9, 10};

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT); // Set pins as output
  }
}

void loop() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPins[i], HIGH); // Turn on the LED
    delay(500);                    // Wait for 0.5 seconds
    digitalWrite(ledPins[i], LOW);  // Turn off the LED
  }
}
```

---

## Example 4: Multi-input Control (Switch and Button)

### Objective
Use a switch and a push-button to control two LEDs.

### Circuit
1. Connect a switch to digital pin 2 with a pull-up resistor.
2. Connect a button to digital pin 3 with a pull-up resistor.
3. Connect two LEDs to digital pins 12 and 13, each through a 220-ohm resistor.

### Code
```cpp
// Example 4: Multi-input Control

const int switchPin = 2;
const int buttonPin = 3;
const int led1Pin = 12;
const int led2Pin = 13;

void setup() {
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
}

void loop() {
  if (digitalRead(switchPin) == LOW) {
    digitalWrite(led1Pin, HIGH); // Turn on LED1
  } else {
    digitalWrite(led1Pin, LOW);
  }

  if (digitalRead(buttonPin) == LOW) {
    digitalWrite(led2Pin, HIGH); // Turn on LED2
    delay(1000);                 // Wait for 1 second
    digitalWrite(led2Pin, LOW);
  }
}
```

---

## Homework

### Task 1: Modify Example 3
Change the LED pattern to include a delay of 300ms between turning off one LED and turning on the next.

### Task 2: Add a New Feature to Example 4
Use a potentiometer to control the brightness of LED1 (use PWM on pin 12).

### Task 3: Documentation
Document the circuit diagrams, code explanations, and observations for each example in your own words.

---


