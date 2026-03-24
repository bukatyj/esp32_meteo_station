#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include "config.h"
#include "ClimateStation.h"
#include "WebInterface.h"

ClimateStation station;
WebServer server(80);

unsigned long lastAlert = 0;
unsigned long lastUpdate = 0;

void setupWiFi();
void handleRoot();

void setup() {
    Serial.begin(115200);

    Wire.begin(I2C_SDA, I2C_SCL);

    if (!station.begin()) {           
        LOG_ERROR("BME280 init failed!");
        while (1) delay(1000);
    }

    setupWiFi();

    server.on("/", handleRoot);
    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
    unsigned long currentMillis = millis();

    WeatherData currentData = station.getData();}
}


void setupWiFi() {
    LOG_INFO("Connecting to WiFi...");

    WiFi.config(local_IP, gateway, subnet);
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