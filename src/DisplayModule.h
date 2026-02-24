#ifndef DISPLAY_MODULE_H
#define DISPLAY_MODULE_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>          
#include "config.h"        
#include "ClimateStation.h" 

class DisplayModule {
private:
    Adafruit_SSD1306 display;

public:
    DisplayModule() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {}

    bool begin() {
        return display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    }

    void showData(WeatherData data) {
        display.clearDisplay();
        display.setTextColor(SSD1306_WHITE);
        display.setTextSize(1);
        display.setCursor(20, 0);
        display.print("IOT STATION");
        display.drawLine(0, 10, 128, 10, SSD1306_WHITE);
        
        display.setCursor(0, 18);
        display.print("Temp: "); 
        display.setTextSize(2); 
        display.print(data.temp, 1);
        
        display.setTextSize(1);
        display.setCursor(0, 40);
        display.print("Hum: "); 
        display.print(data.hum, 0); 
        display.print("%");
        
        display.setCursor(0, 54);
        display.print("IP: "); 
        display.print(WiFi.localIP().toString());
        display.display();
    }

    void showAlert(String msg) {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        
        int16_t x1, y1;
        uint16_t w, h;
        display.getTextBounds(msg, 0, 0, &x1, &y1, &w, &h);
        display.setCursor((SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2);
        
        display.print(msg);
        display.display();
    }
};

#endif