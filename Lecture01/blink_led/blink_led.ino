// Blink LED example for ESP32
int ledPin = 2; // Default onboard LED for most ESP32 boards

void setup() {
  pinMode(ledPin, OUTPUT); // Set LED pin as output
}

void loop() {
  digitalWrite(ledPin, HIGH); // Turn LED on
  delay(1000);               // Wait for 1 second
  digitalWrite(ledPin, LOW);  // Turn LED off
  delay(1000);               // Wait for 1 second
}
