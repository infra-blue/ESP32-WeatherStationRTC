#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

#include "Config_Parser.h"
#define PATH_TO_CONF "/config.json"

void printConfiguration(Config config) {
    Serial.printf("Standard TimeChangeRule:\n");
    Serial.printf("  Abbreviation: %s\n", config.std.abbrev);
    Serial.printf("  Week: %d\n", config.std.week);
    Serial.printf("  Day of Week: %d\n", config.std.dow);
    Serial.printf("  Month: %d\n", config.std.month);
    Serial.printf("  Hour: %d\n", config.std.hour);
    Serial.printf("  Offset: %d\n", config.std.offset);
    
    Serial.printf("Daylight TimeChangeRule:\n");
    Serial.printf("  Abbreviation: %s\n", config.dlt.abbrev);
    Serial.printf("  Week: %d\n", config.dlt.week);
    Serial.printf("  Day of Week: %d\n", config.dlt.dow);
    Serial.printf("  Month: %d\n", config.dlt.month);
    Serial.printf("  Hour: %d\n", config.dlt.hour);
    Serial.printf("  Offset: %d\n", config.dlt.offset);
    
    Serial.printf("I2C Addresses:\n");
    Serial.printf("  BME_280: %d\n", config.i2c.BME_280);
    Serial.printf("  BH1750: %d\n", config.i2c.BH1750);
    Serial.printf("  DS3231: %d\n", config.i2c.DS3231);
    
    Serial.printf("MAX7219 Pins:\n");
    Serial.printf("  CLK_PIN: %d\n", config.max7219.CLK_PIN);
    Serial.printf("  DATA_PIN: %d\n", config.max7219.DATA_PIN);
    Serial.printf("  CS_PIN: %d\n", config.max7219.CS_PIN);
    
    Serial.printf("Other Pins:\n");
    Serial.printf("  BUTTON_PIN: %d\n", config.pins.BUTTON_PIN);
    Serial.printf("  BUZZER_PIN: %d\n", config.pins.BUZZER_PIN);
    
    Serial.printf("NTP Server: %s\n", config.ntpServer);
    Serial.printf("Language: %s\n", config.language);
    Serial.printf("Buzzer Sound: %s\n", config.buzzSound ? "true" : "false");
    Serial.printf("Fahrenheit: %s\n", config.fahrenheit ? "true" : "false");
    
    Serial.printf("WiFi Credentials:\n");
    Serial.printf("  SSID: %s\n", config.wifi.SSID);
    Serial.printf("  Password: %s\n", config.wifi.PASSWORD);
}

void loadConfiguration(Config& config) {
  File file = SPIFFS.open(PATH_TO_CONF, FILE_READ);
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

void storeConfiguration(Config config) {
  SPIFFS.remove(PATH_TO_CONF);

  File file = SPIFFS.open(PATH_TO_CONF, FILE_WRITE);
  if (!file) {
    Serial.println(F("Failed to create file"));
    return;
  }

  JsonDocument conf;

  conf["STD_TIME"]["abbrev"] = config.std.abbrev;
  conf["STD_TIME"]["week"] = config.std.week;
  conf["STD_TIME"]["dow"] = config.std.dow;
  conf["STD_TIME"]["month"] = config.std.month;
  conf["STD_TIME"]["hour"] = config.std.hour;
  conf["STD_TIME"]["offset"] = config.std.offset;

  conf["DL_TIME"]["abbrev"] = config.dlt.abbrev;
  conf["DL_TIME"]["week"] = config.dlt.week;
  conf["DL_TIME"]["dow"] = config.dlt.dow;
  conf["DL_TIME"]["month"] = config.dlt.month;
  conf["DL_TIME"]["hour"] = config.dlt.hour;
  conf["DL_TIME"]["offset"] = config.dlt.offset;

  conf["I2C_ADDR"]["BME_280"] = config.i2c.BME_280;
  conf["I2C_ADDR"]["BH1750"] = config.i2c.BH1750;
  conf["I2C_ADDR"]["DS3231"] = config.i2c.DS3231;

  conf["MAX7219_PINS"]["CLK_PIN"] = config.max7219.CLK_PIN;
  conf["MAX7219_PINS"]["DATA_PIN"] = config.max7219.DATA_PIN;
  conf["MAX7219_PINS"]["CS_PIN"] = config.max7219.CS_PIN;

  conf["PINS"]["BUTTON_PIN"] = config.pins.BUTTON_PIN;
  conf["PINS"]["BUZZER_PIN"] = config.pins.BUZZER_PIN;

  conf["NTP_SERVER"] = config.ntpServer;
  conf["LANGUAGE"] = config.language;
  conf["BUZZ_SOUND"] = config.buzzSound;
  conf["FAHRENHEIT"] = config.fahrenheit;

  conf["WIFI"]["SSID"] = config.wifi.SSID;
  conf["WIFI"]["PASSWORD"] = config.wifi.PASSWORD;

  if (serializeJson(conf, file) == 0) {
    Serial.println(F("Failed to write to file"));
  }

  file.close();
}
