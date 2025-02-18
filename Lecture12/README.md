# ESP32 Async Web Server – Control Outputs with Arduino IDE (ESPAsyncWebServer Library)

This repository provides a tutorial on how to build an asynchronous web server with the ESP32 board to control its outputs using the ESPAsyncWebServer library.

## Table of Contents
- [Introduction](#introduction)
- [Library Installation](#library-installation)
- [How it Works](#how-it-works)
- [Code Implementation](#code-implementation)
- [Second Example: Timer-Based Control](#second-example-timer-based-control)
- [Exercise: WS2812 Neopixel 4 LED Module](#exercise-ws2812-neopixel-4-led-module)
- [References](#references)

## Introduction
This project demonstrates how to control GPIO outputs of an ESP32 through an asynchronous web server. The web server allows users to toggle GPIOs using simple web requests.

## Library Installation
To build this web server, you need to install the following libraries:
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)

Since these libraries aren’t available through the Arduino Library Manager, you need to copy the downloaded library files into the Arduino `libraries` folder manually or add them via **Sketch > Include Library > Add .ZIP Library** in the Arduino IDE.

## How it Works
When you toggle the buttons on the web interface, the browser sends an HTTP GET request to the ESP32.

- Turning **GPIO 2 ON** triggers an HTTP GET request: `/update?output=2&state=1`, setting GPIO 2 to HIGH.
- Turning **GPIO 2 OFF** triggers an HTTP GET request: `/update?output=2&state=0`, setting GPIO 2 to LOW.

The same logic applies to other GPIOs.

## Code Implementation
### Importing Libraries
```cpp
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
```
This code imports the necessary libraries for handling Wi-Fi connectivity and the asynchronous web server.

### Full ESP32 Web Server Code
[Click here](main_code.ino) to see the full source code.

## Second Example: Timer-Based Control
Instead of directly toggling GPIOs, this example includes a timer slider to specify how long the output remains ON before turning OFF.

### Key Features
- Users can toggle GPIO 2 via a web page.
- A slider allows setting a delay (1 to 20 seconds) before the output turns OFF automatically.
- The web server updates the timer dynamically using HTTP GET requests.

### Code Implementation
[Click here](timer_based_code.ino) to see the full source code.

## Exercise: WS2812 Neopixel 4 LED Module (Optional)
As an additional challenge, students can modify the web server to control a WS2812 Neopixel LED strip.

### Exercise Objectives
- Modify the existing web server to control WS2812 Neopixels.
- Implement an interface to:
  - Select LED colors using RGB sliders.
  - Choose animation effects (blink, fade, rainbow, etc.).
- Use the `Adafruit_NeoPixel` library to manage the WS2812 LEDs.

### Additional Library Required
- [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)

### Example Code Snippet
```cpp
#include <Adafruit_NeoPixel.h>
#define LED_PIN    5  // Change to your Neopixel Data Pin
#define LED_COUNT  4  // Number of LEDs
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void setColor(int r, int g, int b) {
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}
```

Students should integrate this with the ESP32 web server and create an interactive webpage to control the LEDs dynamically.

## References
- [ESPAsyncWebServer GitHub](https://github.com/me-no-dev/ESPAsyncWebServer)
- [AsyncTCP GitHub](https://github.com/me-no-dev/AsyncTCP)
- [Adafruit NeoPixel GitHub](https://github.com/adafruit/Adafruit_NeoPixel)

```cpp

// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// HTML web page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html { font-family: Arial; text-align: center; }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .switch { position: relative; display: inline-block; width: 120px; height: 68px }
    .switch input { display: none }
    .slider { position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px }
    .slider:before { position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; transition: .4s; border-radius: 3px }
    input:checked+.slider { background-color: #b30000 }
    input:checked+.slider:before { transform: translateX(52px) }
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
  %BUTTONPLACEHOLDER%
<script>
function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/update?output=" + element.id + "&state=" + (element.checked ? "1" : "0"), true);
  xhr.send();
}
</script>
</body>
</html>
)rawliteral";

// Function to replace placeholders
String processor(const String& var) {
  if (var == "BUTTONPLACEHOLDER") {
    return "<h4>Output - GPIO 2</h4><label class='switch'><input type='checkbox' onchange='toggleCheckbox(this)' id='2'><span class='slider'></span></label>";
  }
  return String();
}

void setup() {
  Serial.begin(115200);

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html, processor);
  });

  server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request) {
    String inputMessage1, inputMessage2;
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    }
    request->send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {
}
```

```cpp
// Import required libraries
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

const int output = 2;
String timerSliderValue = "10";

AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP Web Server</title>
  <style>
    html { font-family: Arial; text-align: center; }
    h2 { font-size: 2.4rem; }
    p { font-size: 2.2rem; }
    .switch { display: inline-block; width: 120px; height: 68px }
    .switch input { display: none }
    .slider { position: absolute; width: 100%; height: 100%; background-color: #ccc; border-radius: 34px }
    input:checked+.slider { background-color: #2196F3 }
    .slider2 { width: 300px; height: 20px; background: #ccc; outline: none; transition: .2s; }
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
  <p><span id="timerValue">%TIMERVALUE%</span> s</p>
  <input type="range" id="timerSlider" min="1" max="20" value="%TIMERVALUE%" class="slider2" oninput="updateSliderTimer(this)">
  %BUTTONPLACEHOLDER%
<script>
function toggleCheckbox(element) {
  var sliderValue = document.getElementById("timerSlider").value;
  var xhr = new XMLHttpRequest();
  if (element.checked) { 
    xhr.open("GET", "/update?state=1", true); 
    xhr.send();
    setTimeout(function() { xhr.open("GET", "/update?state=0", true); element.checked = false; xhr.send(); }, sliderValue * 1000);
  }
}
function updateSliderTimer(element) {
  document.getElementById("timerValue").innerText = element.value;
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/slider?value=" + element.value, true);
  xhr.send();
}
</script>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);

  pinMode(output, OUTPUT);
  digitalWrite(output, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
  });

  server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request) {
    String inputMessage;
    if (request->hasParam("state")) {
      inputMessage = request->getParam("state")->value();
      digitalWrite(output, inputMessage.toInt());
    }
    request->send(200, "text/plain", "OK");
  });

  server.on("/slider", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("value")) {
      timerSliderValue = request->getParam("value")->value();
    }
    request->send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {
}

```