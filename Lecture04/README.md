# ESP32 Wi-Fi Functionalities

This repository contains five ESP32 programs to demonstrate various Wi-Fi functionalities, including scanning networks, configuring access points, managing connections, and more.

---

## Programs Overview

### 1. **Scan Wi-Fi Networks**
- **Description**: This program scans all available Wi-Fi networks in station mode and prints their SSIDs, signal strengths (RSSI), and encryption types.
- **Usage**:
  - Run this program to identify nearby networks.
  - Displays open and encrypted networks.

```cpp
#include <WiFi.h>

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect(); // Ensure no previous connections
    delay(100);

    Serial.println("Scanning for Wi-Fi networks...");
    int n = WiFi.scanNetworks(); // Perform network scan

    if (n == 0) {
        Serial.println("No networks found");
    } else {
        Serial.println("Networks found:");
        for (int i = 0; i < n; ++i) {
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i)); // Print SSID
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i)); // Print signal strength
            Serial.print(") ");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "Open" : "Encrypted");
        }
    }
}

void loop() {
    // Rescan every 10 seconds
    delay(10000);
}
```
### 2. **Set Custom Configuration for Access Point**
- **Description**: Configures the ESP32 as an Access Point (AP) with a custom static IP, gateway, and subnet mask.
- **Usage**:
  - Use this to create a Wi-Fi network with custom IP configurations.
  - Clients can connect to the custom AP using the SSID and password.

```cpp
#include <WiFi.h>

// Custom configuration
IPAddress local_IP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   // Optional
IPAddress secondaryDNS(8, 8, 4, 4); // Optional

void setup() {
    Serial.begin(115200);

    WiFi.mode(WIFI_AP);
    if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
        Serial.println("Failed to configure Access Point");
    }

    if (WiFi.softAP("Custom_AP", "password123")) {
        Serial.println("Access Point started");
        Serial.print("IP Address: ");
        Serial.println(WiFi.softAPIP());
    } else {
        Serial.println("Failed to start Access Point");
    }
}

void loop() {
    // AP running indefinitely
}
```

### 3. **Access Point with Assigned Local IPs**
- **Description**: Sets up the ESP32 as an Access Point and displays the IP addresses assigned to connected devices.
- **Usage**:
  - Tracks the number of connected devices.
  - Prints details of each connected device.
```cpp
#include <WiFi.h>

void setup() {
    Serial.begin(115200);

    WiFi.mode(WIFI_AP);
    if (WiFi.softAP("ESP32_AP", "12345678")) {
        Serial.println("Access Point started");
        Serial.print("AP IP Address: ");
        Serial.println(WiFi.softAPIP());
    }

    WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
}

void loop() {
    delay(5000);
    Serial.print("Number of connected stations: ");
    Serial.println(WiFi.softAPgetStationNum()); // Get connected stations

    // Optionally print details about connected devices
    for (int i = 0; i < WiFi.softAPgetStationNum(); i++) {
        Serial.printf("Device %d connected\n", i + 1);
    }
}
```

### 4. **Reconnect and Disconnect Network**
- **Description**: Demonstrates how to reconnect or disconnect the ESP32 from a Wi-Fi network programmatically.
- **Usage**:
  - Useful for handling Wi-Fi reconnections in scenarios where the connection is lost.

```cpp
#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("\nConnected to Wi-Fi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    static unsigned long lastReconnectAttempt = millis();

    if (WiFi.status() != WL_CONNECTED && millis() - lastReconnectAttempt > 10000) {
        Serial.println("Reconnecting...");
        WiFi.disconnect();
        WiFi.reconnect();
        lastReconnectAttempt = millis();
    }

    delay(1000);
}

```

### 5. **SoftAP (Access Point + Station Mode)**
- **Description**: Configures the ESP32 in AP+STA (Access Point + Station) mode.
- **Usage**:
  - The ESP32 acts as both a client (station) and a host (access point).
  - Suitable for scenarios where the ESP32 connects to a router but also serves local devices.
```cpp  

#include <WiFi.h>
void setup() {
Serial.begin(115200);

WiFi.mode(WIFI_AP_STA); // Set AP + Station mode
WiFi.softAP("SoftAP_ESP32", "mypassword");

Serial.print("SoftAP IP Address: ");
Serial.println(WiFi.softAPIP());
}

void loop() {
delay(5000);
Serial.println("SoftAP running...");
}
```
---

## Setup Instructions

1. **Requirements**:
   - ESP32 development board.
   - Arduino IDE with ESP32 board support installed.

2. **Steps to Run**:
   - Clone this repository:
     ```bash
     git clone https://github.com/your-username/esp32-wifi-examples.git
     cd esp32-wifi-examples
     ```
   - Open the desired `.ino` file in the Arduino IDE.
   - Update any placeholders (e.g., `ssid`, `password`) with your network details.
   - Compile and upload the code to your ESP32.

3. **Output**:
   - Use the Serial Monitor to view the output of each program.
   - Set the baud rate to `115200` for proper output display.
   

---

# Summary of `WiFi.h` Functions

This section provides a brief overview of the `WiFi.h` functions used in the five example programs.

---

## Functions Overview

### **1. Wi-Fi Initialization and Setup**
- `WiFi.begin(ssid, password)`: Connects the ESP32 to a Wi-Fi network using the provided SSID and password.
- `WiFi.mode(mode)`: Sets the Wi-Fi mode. Modes include:
  - `WIFI_STA`: Station mode.
  - `WIFI_AP`: Access Point mode.
  - `WIFI_AP_STA`: Station + Access Point mode.

---

### **2. Scanning Wi-Fi Networks**
- `WiFi.scanNetworks()`: Scans for available Wi-Fi networks and returns the number of networks found.
- `WiFi.SSID(index)`: Retrieves the SSID of a scanned network.
- `WiFi.RSSI(index)`: Gets the signal strength (RSSI) of a scanned network.
- `WiFi.encryptionType(index)`: Returns the encryption type of a scanned network.

---

### **3. Connection Management**
- `WiFi.status()`: Checks the current Wi-Fi connection status. Key statuses include:
  - `WL_CONNECTED`: Successfully connected to a network.
  - `WL_DISCONNECTED`: Not connected.
- `WiFi.disconnect()`: Disconnects from the current Wi-Fi network.
- `WiFi.reconnect()`: Attempts to reconnect to the last known Wi-Fi network.

---

### **4. Access Point Configuration**
- `WiFi.softAP(ssid, password)`: Configures the ESP32 as an Access Point with the given SSID and password.
- `WiFi.softAPConfig(local_IP, gateway, subnet)`: Sets a static IP configuration for the Access Point.
- `WiFi.softAPgetStationNum()`: Retrieves the number of connected devices to the Access Point.
- `WiFi.softAPIP()`: Gets the IP address of the Access Point.

---

### **5. Network Details**
- `WiFi.localIP()`: Retrieves the local IP address of the ESP32 when connected to a network.
- `WiFi.RSSI()`: Gets the signal strength of the connected network.

---

### **6. Advanced Features**
- `WiFi.setHostname(hostname)`: Sets a custom hostname for the ESP32.
- `WiFi.onEvent(callback)`: Registers a callback function to handle Wi-Fi events.

---

This concise summary covers all the key `WiFi.h` functions used in the example programs. Refer to the [ESP32 Wi-Fi Documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/wifi.html) for more details.


## File Structure

```plaintext
esp32-wifi-examples/
├── 1_scan_networks.ino          # Scan Wi-Fi networks and print details
├── 2_custom_access_point.ino    # Configure Access Point with custom IP
├── 3_access_point_ip.ino        # Print assigned IPs for connected clients
├── 4_reconnect_disconnect.ino   # Reconnect and disconnect from Wi-Fi
├── 5_softap_mode.ino            # Set up SoftAP mode
