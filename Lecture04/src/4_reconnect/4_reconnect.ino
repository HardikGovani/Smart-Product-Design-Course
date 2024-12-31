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
