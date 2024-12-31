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
