# Lecture 03: DHT11 Sensor, Arduino Basics, and ESP32 Wi-Fi

Welcome to the third lecture of the **Smart Product Design Course**! This session focuses on:
1. Introducing the **DHT11 sensor** for temperature and humidity measurement.
2. Exploring **Arduino programming basics** and object structures.
3. Diving into **ESP32 Wi-Fi functionalities** for IoT applications.

---

## Resources
- [Canva Presentation: Lecture 03](https://www.canva.com/design/DAGavY46Wns/mxeMs5W4dUzV68bDgwWm9Q/view?utm_content=DAGavY46Wns&utm_campaign=designshare&utm_medium=link2&utm_source=uniquelinks&utlId=h5d353b81c5)
- [DHT11 Library](https://github.com/dhrubasaha08/DHT11/tree/main)
- [ESP32 Wi-Fi Documentation](https://RandomNerdTutorials.com/esp32-useful-wi-fi-functions-arduino/)

---

## DHT11 Sensor
The **DHT11 sensor** measures temperature and humidity. All examples use **Arduino UNO's digital pin 2** as the default connection for the DHT11 sensor's data pin. You can modify the pin as needed for other boards (e.g., ESP32).

### Examples:
1. **Read Humidity**:
   - Demonstrates reading and displaying the humidity value on the Serial Monitor.

2. **Read Temperature and Humidity**:
   - Displays both temperature and humidity values, providing a complete environmental view.

3. **Read Temperature**:
   - Focuses solely on reading and displaying the temperature.

4. **Read Plot**:
   - Graphically displays temperature and humidity in real time using the Arduino Serial Plotter.

---

### Example Code for DHT11
```cpp
#include <DHT11.h>

// Create an instance of the DHT11 class for GPIO2.
DHT11 dht11(2);

void setup() {
    Serial.begin(9600); // Initialize Serial communication
    // dht11.setDelay(500); // Uncomment to set custom delay for sensor readings.
}

void loop() {
    int temperature = 0;
    int humidity = 0;

    int result = dht11.readTemperatureHumidity(temperature, humidity);
    if (result == 0) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    } else {
        Serial.println(DHT11::getErrorString(result));
    }
}

# ESP32 Wi-Fi Modes and Functionalities

This guide covers the various Wi-Fi features available on the ESP32, including Wi-Fi modes, network scanning, connecting to a network, managing connections, and more.

---

## Wi-Fi Modes
The ESP32 supports three Wi-Fi modes:
1. **Station Mode (`WIFI_STA`)**: Connects the ESP32 to a Wi-Fi router or access point.
2. **Access Point Mode (`WIFI_AP`)**: Creates a Wi-Fi network for other devices to connect to the ESP32.
3. **Station + Access Point Mode (`WIFI_AP_STA`)**: Acts as both a station and an access point simultaneously.

### Set Wi-Fi Mode
```cpp
WiFi.mode(WIFI_STA);      // Station mode
WiFi.mode(WIFI_AP);       // Access Point mode
WiFi.mode(WIFI_AP_STA);   // Station + Access Point mode

# Scan Wi-Fi Networks

Scanning Wi-Fi networks helps to identify available networks and their signal strength. This is useful for debugging connection issues or ensuring your ESP32 is in range of your desired network.

---

## Example: Wi-Fi Network Scan

The following example demonstrates how to scan for nearby Wi-Fi networks using the ESP32:

```cpp
#include <WiFi.h>

void setup() {
    Serial.begin(115200); // Initialize serial communication
    WiFi.mode(WIFI_STA);  // Set ESP32 to station mode
    WiFi.disconnect();    // Disconnect from any previously connected access points
    delay(100);           // Short delay to ensure proper initialization
    Serial.println("Wi-Fi Scan Start");

    // Perform a Wi-Fi network scan
    int n = WiFi.scanNetworks();
    if (n == 0) {
        Serial.println("No networks found");
    } else {
        Serial.println("Networks found:");
        for (int i = 0; i < n; ++i) {
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i)); // Print network SSID
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i)); // Print signal strength (RSSI)
            Serial.println(")");
        }
    }
}

void loop() {
    delay(5000); // Re-scan every 5 seconds
}

# ESP32 Wi-Fi Functionalities

This document provides a comprehensive overview of ESP32 Wi-Fi functionalities, complete with example code snippets for practical applications.

---

## Connect to a Wi-Fi Network

To connect the ESP32 to a Wi-Fi network, use the following example:

### Example: Connect to a Network
```cpp
#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

# Additional ESP32 Wi-Fi Functionalities

This section covers additional Wi-Fi functionalities for the ESP32, including checking signal strength, setting a static IP address, and managing Wi-Fi connections.

---

## Get Wi-Fi Connection Strength

You can check the Wi-Fi signal strength (RSSI) using the following command:

### Example: Get RSSI
```cpp
Serial.println(WiFi.RSSI());

# Set a Static IP Address for ESP32

You can configure a static IP address for the ESP32 to ensure it always has the same IP address on your network. This is particularly useful for devices that need to be easily accessible without checking dynamically assigned IPs.

---

## Example: Static IP Configuration

```cpp
#include <WiFi.h>

// Define your static IP address, gateway, and subnet
IPAddress local_IP(192, 168, 1, 184);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
    Serial.begin(115200);

    // Configure the static IP address
    if (!WiFi.config(local_IP, gateway, subnet)) {
        Serial.println("Failed to configure Static IP");
    }
}


# ESP32 Wi-Fi Functionalities: Disconnect and Reconnect

This section demonstrates how to disconnect from the current Wi-Fi network and reconnect. It also provides an overview of ESP32 Wi-Fi events and additional Wi-Fi features.

---

## Disconnect and Reconnect Wi-Fi

You can disconnect from the current Wi-Fi network and reconnect using the following commands:

### Example: Disconnect and Reconnect
```cpp
WiFi.disconnect();       // Disconnect from the network
WiFi.begin(ssid, password); // Reconnect to the network

# ESP32 Wi-Fi Events and Advanced Functionalities

This document provides an overview of ESP32 Wi-Fi events and additional Wi-Fi features for handling dynamic network states and enhancing connectivity management in IoT projects.

---

## ESP32 Wi-Fi Events

The ESP32 generates Wi-Fi events to handle changes in connection states and other network-related activities.

### Wi-Fi Event Codes

| **Code** | **Event**                           | **Description**                            |
|----------|-------------------------------------|--------------------------------------------|
| 0        | `ARDUINO_EVENT_WIFI_READY`          | ESP32 Wi-Fi ready                          |
| 1        | `ARDUINO_EVENT_WIFI_SCAN_DONE`      | Wi-Fi scan complete                        |
| 2        | `ARDUINO_EVENT_WIFI_STA_START`      | Station start                              |
| 3        | `ARDUINO_EVENT_WIFI_STA_STOP`       | Station stop                               |
| 4        | `ARDUINO_EVENT_WIFI_STA_CONNECTED`  | Station connected to access point          |
| 5        | `ARDUINO_EVENT_WIFI_STA_DISCONNECTED` | Station disconnected from access point     |
| 6        | `ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE` | Auth mode of connected AP changed         |
| 7        | `ARDUINO_EVENT_WIFI_STA_GOT_IP`     | Station got IP address                     |
| 8        | `ARDUINO_EVENT_WIFI_STA_LOST_IP`    | Station lost IP                            |
| 9        | `ARDUINO_EVENT_WIFI_AP_START`       | Access Point start                         |
| 10       | `ARDUINO_EVENT_WIFI_AP_STOP`        | Access Point stop                          |
| 11       | `ARDUINO_EVENT_WIFI_AP_STACONNECTED`| A station connected to ESP32 AP            |
| 12       | `ARDUINO_EVENT_WIFI_AP_STADISCONNECTED` | A station disconnected from ESP32 AP      |

---

## Additional ESP32 Wi-Fi Features

### Reconnect to Wi-Fi After Lost Connection
Use event handling to automatically reconnect to a Wi-Fi network if the connection is lost. This ensures minimal disruption to IoT applications that rely on constant connectivity.

### ESP32 WiFiMulti
The `WiFiMulti` class allows the ESP32 to manage connections to multiple networks efficiently. It prioritizes connections based on signal strength and availability.

### Change ESP32 Hostname
Modify the ESP32's hostname for easy identification on the network. Use the following command to set a custom hostname:
```cpp
WiFi.setHostname("MyESP32Device");

## Instructions for Students

### Bring the Kit
Ensure you have the following components ready for this lecture:
- **ESP32 Development Board**
- **DHT11 Sensor**
- Breadboard, jumper wires, and other prototyping components.

---

### Practice Examples

1. **Test DHT11 Examples**:
   - Implement and run the following examples:
     - **Read Humidity**: Display humidity values in the Serial Monitor.
     - **Read Temperature and Humidity**: Show both temperature and humidity values.
     - **Read Plot**: Use the Arduino Serial Plotter to visualize real-time data.

2. **Scan Wi-Fi Networks**:
   - Use the provided ESP32 code to scan for available Wi-Fi networks.
   - Display the SSIDs and signal strength (RSSI) in the Serial Monitor.

---

### Homework

1. Modify the DHT11 code to:
   - Display temperature and humidity readings every **10 seconds**.
   - Include a status message if the sensor fails to read data.

2. Create an ESP32 sketch to:
   - Connect to your Wi-Fi network using your credentials.
   - Display the connection status and the **IP address** in the Serial Monitor.

3. Research the following ESP32 functionalities for the next lecture:
   - **Setting a Static IP Address**.
   - **Wi-Fi Event Handling** (e.g., reconnecting after disconnection).

---

### Additional Notes
- Ensure your **Arduino IDE** is set up with ESP32 board support. If not, refer to the setup guide [here](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).
- Keep a notebook or digital file to document:
  - Observations from each practical example.
  - Questions or issues encountered during practice.



