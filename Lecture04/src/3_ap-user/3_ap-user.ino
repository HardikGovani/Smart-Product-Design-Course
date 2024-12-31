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
