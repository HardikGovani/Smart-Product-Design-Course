# ESP32 Wi-Fi Web Server Examples

## Overview
This document covers different modes of Wi-Fi on ESP32, including practical examples of setting up a web server to control LEDs, read sensor data, and operate a servo motor.

## Wi-Fi Modes in ESP32
ESP32 supports three Wi-Fi modes:

1. **Station Mode (STA)** - Connects to an existing Wi-Fi network.
2. **Access Point Mode (AP)** - Creates a Wi-Fi network for other devices to connect to ESP32.
3. **Dual Mode (AP+STA)** - Operates in both Station and Access Point modes simultaneously.

---

## 1. ESP32 Web Server for LED Control

### **Objective:**
Turn an LED on and off via a web server.

### **Code:**
```cpp
#include <WiFi.h>

const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";
WiFiServer server(80);

const int ledPin = 26;
String header;
String ledState = "off";

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close\n");
            
            if (header.indexOf("GET /led/on") >= 0) {
              digitalWrite(ledPin, HIGH);
              ledState = "on";
            } else if (header.indexOf("GET /led/off") >= 0) {
              digitalWrite(ledPin, LOW);
              ledState = "off";
            }
            
            client.println("<!DOCTYPE html><html><body>");
            client.println("<h1>ESP32 Web Server</h1>");
            client.println("<p>LED is " + ledState + "</p>");
            client.println("<a href='/led/on'><button>ON</button></a>");
            client.println("<a href='/led/off'><button>OFF</button></a>");
            client.println("</body></html>");
            client.println();
            break;
          }
          currentLine = "";
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
  }
}
```

---

## 2. ESP32 Web Server for Servo Motor (Home Door Control)

### **Objective:**
Control a servo motor from a web page to open and close a door.

### **Code:**
```cpp
#include <WiFi.h>
#include <ESP32Servo.h>

const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";
WiFiServer server(80);

Servo myServo;
const int servoPin = 13;

void setup() {
  Serial.begin(115200);
  myServo.attach(servoPin);
  myServo.write(0);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String header;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        header += c;
        if (c == '\n') {
          if (header.indexOf("GET /open") >= 0) {
            myServo.write(90);
          } else if (header.indexOf("GET /close") >= 0) {
            myServo.write(0);
          }
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close\n");
          client.println("<a href='/open'><button>Open Door</button></a>");
          client.println("<a href='/close'><button>Close Door</button></a>");
          client.println();
          break;
        }
      }
    }
    client.stop();
  }
}
```

---

## 3. ESP32 Web Server for DHT11 Sensor Data

### **Objective:**
Read temperature and humidity from a DHT11 sensor and display it on a web page.

### **Code:**
```cpp
#include <WiFi.h>
#include <DHT.h>

const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";
WiFiServer server(80);

#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String header;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        header += c;
        if (c == '\n') {
          float temp = dht.readTemperature();
          float hum = dht.readHumidity();
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close\n");
          client.println("<h1>ESP32 DHT11 Sensor</h1>");
          client.println("<p>Temperature: " + String(temp) + " C</p>");
          client.println("<p>Humidity: " + String(hum) + "%</p>");
          client.println();
          break;
        }
      }
    }
    client.stop();
  }
}
```

---

## Exercise: Remote Alarm System
Modify the LED control code to activate a buzzer instead of an LED when triggered from the web server.

---

This tutorial provides a foundation for ESP32 Wi-Fi applications. 🚀
