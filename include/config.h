#ifndef CONFIG_H
#define CONFIG_H

//credentials for WiFi connection
#include "credentials.h"

// Network settings
#define WIFI_LOCAL_IP  192, 168, 0, 104
#define WIFI_GATEWAY   192, 168, 0, 1
#define WIFI_SUBNET    255, 255, 255, 0

// Hardware I2C pins and addresses
#define I2C_SDA 21
#define I2C_SCL 22
#define OLED_ADDR 0x3C
#define BME_ADDR 0x76

// temperature thresholds and alert settings
#define TEMP_LOW 15.0
#define TEMP_HIGH 24.0
#define ALERT_INTERVAL 15000

// logging levels
#define DEBUG_MODE true

#define LOG_INFO(msg) if (DEBUG_MODE) { Serial.print("[INFO] "); Serial.println(msg); }
#define LOG_ERROR(msg) if (DEBUG_MODE) { Serial.print("[ERROR] "); Serial.println(msg); }

#endif