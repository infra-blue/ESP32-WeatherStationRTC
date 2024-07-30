#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

#include "Config_Parser.h"
#define PATH_TO_CONF "/config.json"

void loadConfiguration(Config& config) {
  File file = SPIFFS.open(PATH_TO_CONF, "r");
  JsonDocument conf;

  DeserializationError error = deserializeJson(conf, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

  strlcpy(config.std.abbrev,
          conf["STD_TIME"]["abbrev"] | "STD",
          sizeof(config.std.abbrev));

  config.std.week = conf["STD_TIME"]["week"] | 1;
  config.std.dow = conf["STD_TIME"]["dow"] | 1;
  config.std.month = conf["STD_TIME"]["month"] | 1;
  config.std.hour = conf["STD_TIME"]["hour"] | 1;
  config.std.offset = conf["STD_TIME"]["offset"] | 0;

  strlcpy(config.dlt.abbrev,
          conf["DL_TIME"]["abbrev"] | "DLT",
          sizeof(config.dlt.abbrev));

  config.dlt.week = conf["DL_TIME"]["week"] | 1;
  config.dlt.dow = conf["DL_TIME"]["dow"] | 1;
  config.dlt.month = conf["DL_TIME"]["month"] | 1;
  config.dlt.hour = conf["DL_TIME"]["hour"] | 1;
  config.dlt.offset = conf["DL_TIME"]["offset"] | 0;

  config.i2c.BME_280 = conf["I2C_ADDR"]["BME_280"] | 118;
  config.i2c.BH1750 = conf["I2C_ADDR"]["BH1750"] | 35;
  config.i2c.DS3231 = conf["I2C_ADDR"]["DS3231"] | 104;

  config.max7219.CLK_PIN = conf["MAX7219_PINS"]["CLK_PIN"] | 18;
  config.max7219.DATA_PIN = conf["MAX7219_PINS"]["DATA_PIN"] | 23;
  config.max7219.CS_PIN = conf["MAX7219_PINS"]["CS_PIN"] | 5;

  config.pins.BUTTON_PIN = conf["PINS"]["BUTTON_PIN"] | 0;
  config.pins.BUZZER_PIN = conf["PINS"]["BUZZER_PIN"] | 14;

  strlcpy(config.ntpServer,
          conf["NTP_SERVER"] | "pool.ntp.org",
          sizeof(config.ntpServer));

  strlcpy(config.language,
          conf["LANGUAGE"] | "en",
          sizeof(config.language));

  config.buzzSound = conf["BUZZ_SOUND"] | true;

  config.fahrenheit = conf["FAHRENHEIT"] | false;

  strlcpy(config.wifi.SSID,
          conf["WIFI"]["SSID"] | "",
          sizeof(config.wifi.SSID));

  strlcpy(config.wifi.PASSWORD,
          conf["WIFI"]["PASSWORD"] | "",
          sizeof(config.wifi.PASSWORD));

  file.close();
}