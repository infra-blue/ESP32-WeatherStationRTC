#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#define PATH_TO_CONF "/config.json"

#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <Timezone.h>

struct I2CADDR {
    uint8_t BME_280;
    uint8_t BH1750;
    uint8_t DS3231;
};

struct MAX7219PINS {
    uint8_t CLK_PIN;
    uint8_t DATA_PIN;
    uint8_t CS_PIN;
};

struct PINS {
    uint8_t BUTTON_PIN;
    uint8_t BUZZER_PIN;
};

struct WIFI_CRED {
    char SSID[32];
    char PASSWORD[32];
};

struct Config {
    TimeChangeRule std;
    TimeChangeRule dlt;
    I2CADDR i2c;
    MAX7219PINS max7219;
    PINS pins;
    char ntpServer[64];
    char language[3];
    bool buzzSound;
    bool fahrenheit;
    WIFI_CRED wifi;
};

void loadConfiguration(Config& config);
void storeConfiguration(Config config);
void printConfiguration(Config config);

#endif