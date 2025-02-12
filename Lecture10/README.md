# ESP32 Bluetooth: BLE vs Classic Bluetooth

## Comparison: ESP32 BLE vs Classic Bluetooth

| Feature                | BLE (Bluetooth Low Energy) | Classic Bluetooth |
|-----------------------|-------------------------|------------------|
| **Power Consumption** | Low                      | High             |
| **Data Transfer Rate** | Lower (1 Mbps max)       | Higher (Up to 3 Mbps) |
| **Range**             | ~10m (can extend to 100m with special configurations) | ~10m |
| **Pairing**           | No pairing required      | Requires pairing |
| **Latency**           | Lower                    | Higher            |
| **Use Cases**         | Sensor data, IoT, Wearables | Audio streaming, File transfer, HID devices |

## BLE vs Classic Bluetooth Use Cases

### **BLE (Bluetooth Low Energy) Applications:**
- Smartwatches & Wearable devices
- Health & fitness sensors (heart rate, glucose monitors, etc.)
- IoT devices like temperature & humidity sensors
- Asset tracking & location beacons
- Low-power communication for smart home automation

### **Classic Bluetooth Applications:**
- Wireless audio streaming (headphones, speakers, etc.)
- File transfer (Bluetooth file sharing)
- Wireless keyboards & mice
- Game controllers
- Hands-free calling (car Bluetooth systems)

---

# BLE Programming on ESP32

## **1. Simple BLE Code (Hello ESP32)**
### **Objective:**
Broadcast "Hello ESP32" via BLE. Students will use a mobile Android BLE app to check the data.

### **Code:**
```cpp
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer* pServer = nullptr;
BLEService* pService = nullptr;
BLECharacteristic* pCharacteristic = nullptr;

void setup() {
  Serial.begin(115200);
  BLEDevice::init("ESP32_BLE_Server");

  // Create a BLE Server
  pServer = BLEDevice::createServer();

  // Create a BLE Service
  pService = pServer->createService(BLEUUID((uint16_t)0x180F));

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
      BLEUUID((uint16_t)0x2A19),
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
  );

  // Set Initial Value
  pCharacteristic->setValue("Hello ESP32");

  // Start the Service
  pService->start();

  Serial.println("BLE Server is running...");
}

void loop() {
  delay(1000);
}
```

---

## **2. Button Input to Check BLE Data on Mobile App**
### **Objective:**
Pressing a button on ESP32 will send a BLE notification to the mobile app.

### **Circuit:**
- Connect a push-button to GPIO **4**.

### **Code:**
```cpp
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLECharacteristic *pCharacteristic;
const int buttonPin = 4;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  BLEDevice::init("ESP32_BLE_Button");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(BLEUUID((uint16_t)0x180A));
  pCharacteristic = pService->createCharacteristic(
                     BLEUUID((uint16_t)0x2A56),
                     BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  pService->start();
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    pCharacteristic->setValue("Button Pressed");
    pCharacteristic->notify();
    Serial.println("Sent: Button Pressed");
    delay(500);
  }
}
```

---

## **3. Read Temperature & Humidity via BLE (DHT11 Sensor)**
### **Objective:**
ESP32 reads temperature and humidity from a **DHT11 sensor** and transmits it over BLE.

### **Circuit:**
- **DHT11** Data Pin → **GPIO 5**

### **Code:**
```cpp
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <DHT.h>

#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

BLECharacteristic *pCharacteristic;

void setup() {
  Serial.begin(115200);
  dht.begin();
  BLEDevice::init("ESP32_BLE_DHT11");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(BLEUUID((uint16_t)0x1809));
  pCharacteristic = pService->createCharacteristic(
                     BLEUUID((uint16_t)0x2A6E),
                     BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  pService->start();
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  String data = "Temp: " + String(temp) + "C, Hum: " + String(hum) + "%";
  pCharacteristic->setValue(data.c_str());
  pCharacteristic->notify();
  Serial.println("Sent: " + data);
  delay(2000);
}
```

---

## **4. MIT App Inventor BLE App for Students**
### **Objective:**
Students can use an **MIT App Inventor-based BLE App** to receive ESP32 sensor data.

### **Download Ready-Made BLE App:**
🔗 [BLE Temperature & Humidity App](https://drive.google.com/file/d/1v3ZzJZ3U6bYiLg3O9q43kxsEMCJkDUpq/view?usp=sharing)

### **Steps to Use the App:**
1. Download and install the app from the link above.
2. Enable Bluetooth on your Android device.
3. Connect to the ESP32 device.
4. View real-time **temperature and humidity** readings.

---

This tutorial provides a solid foundation for ESP32 BLE development. 🚀
