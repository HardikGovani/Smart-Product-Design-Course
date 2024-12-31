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
