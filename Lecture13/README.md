# ESP32 with MPU6050 - Introduction & Exercises

## **Lecture 13: Playing with MPU6050 on ESP32**
This repository covers working with **MPU6050** (a 6-axis IMU sensor) using **ESP32**, including raw data acquisition, gyro data display, and real-world applications like controlling objects in computer applications via serial/BLE.

---
## **🔹 Table of Contents**
1. [Introduction to MPU6050](#introduction-to-mpu6050)
2. [Installing Libraries](#installing-libraries)
3. [Raw Accelerometer Data](#raw-accelerometer-data)
4. [Gyroscope Data](#gyroscope-data)
5. [Gyroscope Data Visualization](#gyroscope-data-visualization)
6. [Control Objects in PC Apps (BLE Keyboard)](#control-objects-in-pc-apps-ble-keyboard)
7. [Sensor Fusion Exercise](#sensor-fusion-exercise)
8. [References](#references)

---
## **🔹 Introduction to MPU6050**
MPU6050 is a 6-axis motion tracking device combining **3-axis accelerometer** and **3-axis gyroscope** into a single package. It is commonly used in robotics, drones, and motion detection projects.

### **Pinout Connections (ESP32 with MPU6050)**
| MPU6050 | ESP32 |
|---------|-------|
| VCC     | 3.3V  |
| GND     | GND   |
| SCL     | GPIO 22 |
| SDA     | GPIO 21 |

---
## **🔹 Installing Libraries**
Ensure the following libraries are installed correctly:
1. **MPU6050 Library** (Adafruit or Jeff Rowberg’s Library)
2. **Wire.h** (Built-in in Arduino)

### **Library Installation Steps:**
- **Automatic (Recommended)**: Install via Arduino Library Manager:
  - Open **Arduino IDE** → **Sketch** → **Include Library** → **Manage Libraries** → Search for "MPU6050"
  - Install **Adafruit MPU6050** or **MPU6050_tockn**
  
- **Manual Installation**:
  - Download [MPU6050 Library](https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050)
  - Extract & place it in `Arduino/libraries/`

---
## **🔹 Raw Accelerometer Data**
The following code reads raw **accelerometer** values (X, Y, Z) from the MPU6050.

```cpp
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    mpu.initialize();
    if (!mpu.testConnection()) {
        Serial.println("MPU6050 connection failed!");
        while (1);
    }
}

void loop() {
    int16_t ax, ay, az;
    mpu.getAcceleration(&ax, &ay, &az);
    Serial.print("Accelerometer: X="); Serial.print(ax);
    Serial.print(" | Y="); Serial.print(ay);
    Serial.print(" | Z="); Serial.println(az);
    delay(500);
}
```

---
## **🔹 Gyroscope Data**
The gyroscope measures angular velocity, useful for rotation-based projects.

```cpp
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    mpu.initialize();
}

void loop() {
    int16_t gx, gy, gz;
    mpu.getRotation(&gx, &gy, &gz);
    Serial.print("Gyroscope: X="); Serial.print(gx);
    Serial.print(" | Y="); Serial.print(gy);
    Serial.print(" | Z="); Serial.println(gz);
    delay(500);
}
```

---
## **🔹 Gyroscope Data Visualization**
We use **Processing** (Java-based visualization tool) to display gyroscope rotation.

1. **Install Processing IDE**: [Download](https://processing.org/download/)
2. **Create a new Processing sketch**
3. **Paste the following code:**

```java
import processing.serial.*;
Serial myPort;
float x, y, z;

void setup() {
    size(600, 600, P3D);
    myPort = new Serial(this, "COM5", 115200);  // Change COM Port
    myPort.bufferUntil('\n');
}

void draw() {
    background(200);
    translate(width/2, height/2, -200);
    rotateX(radians(x));
    rotateY(radians(y));
    rotateZ(radians(z));
    box(100);
}

void serialEvent(Serial myPort) {
    String data = myPort.readStringUntil('\n');
    if (data != null) {
        String[] values = split(data, ',');
        if (values.length == 3) {
            x = float(values[0]);
            y = float(values[1]);
            z = float(values[2]);
        }
    }
}
```

---
## **🔹 Control Objects in PC Apps (BLE Keyboard)**
We use the **ESP32 BLE Keyboard Library** to send motion-based keypresses.

1. **Install `ESP32 BLE Keyboard` library**
2. **Use the following ESP32 Code:**

```cpp
#include <BleKeyboard.h>
#include <Wire.h>
#include <MPU6050.h>

BleKeyboard bleKeyboard("ESP32_Motion_Controller");
MPU6050 mpu;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    mpu.initialize();
    bleKeyboard.begin();
}

void loop() {
    int16_t ax, ay, az;
    mpu.getAcceleration(&ax, &ay, &az);
    
    if (ax > 5000) { bleKeyboard.write(KEY_UP_ARROW); }
    if (ax < -5000) { bleKeyboard.write(KEY_DOWN_ARROW); }
    if (ay > 5000) { bleKeyboard.write(KEY_RIGHT_ARROW); }
    if (ay < -5000) { bleKeyboard.write(KEY_LEFT_ARROW); }
    
    delay(500);
}
```

Now, the **ESP32 sends arrow key presses** when tilted.

---
## **🔹 Sensor Fusion Exercise**
To improve motion accuracy, students will implement **sensor fusion** combining Accelerometer & Gyroscope using the **Madgwick Filter**.

1. **Install MadgwickAHRS Library**
2. **Use the following sample code**

```cpp
#include <MadgwickAHRS.h>
Madgwick filter;
float ax, ay, az, gx, gy, gz;

void loop() {
    // Read sensor values
    filter.updateIMU(gx, gy, gz, ax, ay, az);
    Serial.print("Roll: "); Serial.print(filter.getRoll());
    Serial.print(" Pitch: "); Serial.print(filter.getPitch());
    Serial.print(" Yaw: "); Serial.println(filter.getYaw());
    delay(100);
}
```

---
## **🔹 References**
- [MPU6050 Datasheet](https://invensense.tdk.com/products/motion-tracking/6-axis/mpu-6050/)
- [ESP32 BLE Keyboard Library](https://github.com/T-vK/ESP32-BLE-Keyboard)
- [Madgwick Filter](https://x-io.co.uk/open-source-imu-and-ahrs-algorithms/)

Happy Coding! 🚀
