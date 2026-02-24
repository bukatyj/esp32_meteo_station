#ifndef CLIMATE_STATION_H
#define CLIMATE_STATION_H

#include <Arduino.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include "config.h"

struct WeatherData {
    float temp;
    float hum;
    float pres;
};

class ClimateStation {
private:
    Adafruit_BME280 bme;
public:
    bool begin() {
        // initialize the BME280 sensor
        return bme.begin(BME_ADDR); 
    }

    WeatherData getData() {
        WeatherData data;
        data.temp = bme.readTemperature();
        data.hum = bme.readHumidity();
        data.pres = bme.readPressure() / 133.3223684;
        return data;
    }
};

#endif