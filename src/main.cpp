#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include "config.h"
#include "ClimateStation.h"
#include "DisplayModule.h"
#include "WebInterface.h"

ClimateStation station;
DisplayModule myDisplay;
WebServer server(80);

unsigned long lastAlert = 0;
unsigned long lastUpdate = 0;

void setupWiFi();
void handleRoot();

void setup() {
    Serial.begin(115200);

    Wire.begin(I2C_SDA, I2C_SCL);

    if (!station.begin()) {
        Serial.println("BME280 sensor fail!");
        while (1);
    }
    
    if (!myDisplay.begin()) {
        Serial.println("OLED display fail!");
        while (1);
    }

    setupWiFi();

    server.on("/", handleRoot);
    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
    unsigned long currentMillis = millis();

    WeatherData currentData = station.getData();

    if (currentMillis - lastAlert >= ALERT_INTERVAL) {
        if (currentData.temp < TEMP_LOW) {
            myDisplay.showAlert("COLD!");
            lastAlert = currentMillis;
        } else if (currentData.temp > TEMP_HIGH) {
            myDisplay.showAlert("HOT!");
            lastAlert = currentMillis;
        }
    }

    if (currentMillis - lastUpdate >= 1000) {
        myDisplay.showData(currentData);
        lastUpdate = currentMillis;
    }
}


void setupWiFi() {
    LOG_INFO("Connecting to WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        attempts++;
        if (attempts > 20) {
            LOG_ERROR("Failed to connect to WiFi");
            while (1);
        }
    }

    Serial.println("\nWiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void handleRoot() {
    LOG_INFO("Web request from: " + server.client().remoteIP().toString());
    
    String page = WebInterface::buildDashboard(station.getData());
    server.send(200, "text/html", page);
}