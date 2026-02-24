#ifndef WEB_INTERFACE_H
#define WEB_INTERFACE_H

#include <Arduino.h>
#include "ClimateStation.h"

class WebInterface {
public:
    static String buildDashboard(WeatherData data) {
        String html = "<!DOCTYPE html><html lang='uk'><head>";
        html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
        html += "<meta http-equiv='refresh' content='5'>";
        html += "<title>ESP32 Meteo</title>";
        html += "<style>";
        html += "body { font-family: sans-serif; background: #1a1a1a; color: white; text-align: center; padding: 20px; }";
        html += ".card { background: #2d2d2d; padding: 20px; border-radius: 15px; margin: 10px auto; max-width: 300px; box-shadow: 0 4px 10px rgba(0,0,0,0.3); border-left: 5px solid #00fbff; }";
        html += ".val { font-size: 2.5em; font-weight: bold; color: #00fbff; }";
        html += ".unit { font-size: 0.5em; color: #888; }";
        html += "</style></head><body>";
        
        html += "<h1>Метеостанція</h1>";
        
        html += "<div class='card'><div>Температура</div><div class='val'>" + String(data.temp, 1) + "<span class='unit'>°C</span></div></div>";
        html += "<div class='card'><div>Вологість</div><div class='val'>" + String(data.hum, 0) + "<span class='unit'>%</span></div></div>";
        html += "<div class='card'><div>Тиск</div><div class='val'>" + String(data.pres, 0) + "<span class='unit'>мм рт.ст.</span></div></div>";
        
        html += "<p style='color: #555;'>Оновлення кожні 5 секунд</p>";
        html += "</body></html>";
        return html;
    }
};

#endif