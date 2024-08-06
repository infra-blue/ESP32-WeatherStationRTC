#include "Web_Settings.h"

String htmlLoader(const char* filename) {
  String content = "";
  File file = SPIFFS.open(filename, FILE_READ);

  if (!file) {
      Serial.printf("Error opening file: %s\n", filename);
      return content;
  }

  while (file.available())
      content += (char)file.read();

  file.close();
  return content;
}

void handleHome() {
  String html = HOME_HTML;

  char year[] = "0000";
  char month[] = "00";
  char day[] = "00";
  char hour[] = "00";
  char minute[] = "00";
  char second[] = "00";

  sprintf(year, "%04d", current_time.year());
  sprintf(month, "%02d", current_time.month());
  sprintf(day, "%02d", current_time.day());
  sprintf(hour, "%02d", current_time.hour());
  sprintf(minute, "%02d", current_time.minute());
  sprintf(second, "%02d", current_time.second());

  html.replace("{{ TOGGLE_SCREEN }}", String(screen_off ? "Turn On Screen" : "Turn Off Screen"));
  html.replace("{{ TEMP }}", conf.fahrenheit ? String(bme.readTemperature() * 1.8 + 32) : String(bme.readTemperature()));
  html.replace("{{ TEMPUNIT }}", conf.fahrenheit ? "Fahrenheit" : "Celsius");
  html.replace("{{ HUMIDITY }}", String(bme.readHumidity()));
  html.replace("{{ PRESSURE }}", String(bme.readPressure() / 100.0));
  html.replace("{{ DAY }}", day);
  html.replace("{{ MONTH }}", month);
  html.replace("{{ YEAR }}", year);
  html.replace("{{ HOUR }}", hour);
  html.replace("{{ MINUTE }}", minute);
  html.replace("{{ SECOND }}", second);

  server.send(200, "text/html", html);
}

void handleSettings() {
  String html = SETTINGS_HTML;

  html.replace("{{ SSID }}", String(conf.wifi.SSID));
  html.replace("{{ NTP_SERVER }}", String(conf.ntpServer));

  html.replace("{{ ENGLISH }}", String(!strcmp(conf.language, "en") ? " selected" : ""));
  html.replace("{{ ITALIAN }}", String(!strcmp(conf.language, "it") ? " selected" : ""));
  html.replace("{{ SPANISH }}", String(!strcmp(conf.language, "es") ? " selected" : ""));
  html.replace("{{ GERMAN }}", String(!strcmp(conf.language, "de") ? " selected" : ""));
  html.replace("{{ FRENCH }}", String(!strcmp(conf.language, "fr") ? " selected" : ""));

  html.replace("{{ STD_ABBREV }}", String(conf.std.abbrev));

  html.replace("{{ STD_WEEK_0 }}", String(conf.std.week == 0 ? " selected" : ""));
  html.replace("{{ STD_WEEK_1 }}", String(conf.std.week == 1 ? " selected" : ""));
  html.replace("{{ STD_WEEK_2 }}", String(conf.std.week == 2 ? " selected" : ""));
  html.replace("{{ STD_WEEK_3 }}", String(conf.std.week == 3 ? " selected" : ""));
  html.replace("{{ STD_WEEK_4 }}", String(conf.std.week == 4 ? " selected" : ""));

  html.replace("{{ STD_DOW_1 }}", String(conf.std.dow == 1 ? " selected" : ""));
  html.replace("{{ STD_DOW_2 }}", String(conf.std.dow == 2 ? " selected" : ""));
  html.replace("{{ STD_DOW_3 }}", String(conf.std.dow == 3 ? " selected" : ""));
  html.replace("{{ STD_DOW_4 }}", String(conf.std.dow == 4 ? " selected" : ""));
  html.replace("{{ STD_DOW_5 }}", String(conf.std.dow == 5 ? " selected" : ""));
  html.replace("{{ STD_DOW_6 }}", String(conf.std.dow == 6 ? " selected" : ""));
  html.replace("{{ STD_DOW_7 }}", String(conf.std.dow == 7 ? " selected" : ""));

  html.replace("{{ STD_MONTH_1 }}", String(conf.std.month == 1 ? " selected" : ""));
  html.replace("{{ STD_MONTH_2 }}", String(conf.std.month == 2 ? " selected" : ""));
  html.replace("{{ STD_MONTH_3 }}", String(conf.std.month == 3 ? " selected" : ""));
  html.replace("{{ STD_MONTH_4 }}", String(conf.std.month == 4 ? " selected" : ""));
  html.replace("{{ STD_MONTH_5 }}", String(conf.std.month == 5 ? " selected" : ""));
  html.replace("{{ STD_MONTH_6 }}", String(conf.std.month == 6 ? " selected" : ""));
  html.replace("{{ STD_MONTH_7 }}", String(conf.std.month == 7 ? " selected" : ""));
  html.replace("{{ STD_MONTH_8 }}", String(conf.std.month == 8 ? " selected" : ""));
  html.replace("{{ STD_MONTH_9 }}", String(conf.std.month == 9 ? " selected" : ""));
  html.replace("{{ STD_MONTH_10 }}", String(conf.std.month == 10 ? " selected" : ""));
  html.replace("{{ STD_MONTH_11 }}", String(conf.std.month == 11 ? " selected" : ""));
  html.replace("{{ STD_MONTH_12 }}", String(conf.std.month == 12 ? " selected" : ""));

  html.replace("{{ STD_HOUR }}", String(conf.std.hour));
  html.replace("{{ STD_OFFSET }}", String(conf.std.offset));

  html.replace("{{ DLT_ABBREV }}", String(conf.dlt.abbrev));

  html.replace("{{ DLT_WEEK_0 }}", String(conf.dlt.week == 0 ? " selected" : ""));
  html.replace("{{ DLT_WEEK_1 }}", String(conf.dlt.week == 1 ? " selected" : ""));
  html.replace("{{ DLT_WEEK_2 }}", String(conf.dlt.week == 2 ? " selected" : ""));
  html.replace("{{ DLT_WEEK_3 }}", String(conf.dlt.week == 3 ? " selected" : ""));
  html.replace("{{ DLT_WEEK_4 }}", String(conf.dlt.week == 4 ? " selected" : ""));

  html.replace("{{ DLT_DOW_1 }}", String(conf.dlt.dow == 1 ? " selected" : ""));
  html.replace("{{ DLT_DOW_2 }}", String(conf.dlt.dow == 2 ? " selected" : ""));
  html.replace("{{ DLT_DOW_3 }}", String(conf.dlt.dow == 3 ? " selected" : ""));
  html.replace("{{ DLT_DOW_4 }}", String(conf.dlt.dow == 4 ? " selected" : ""));
  html.replace("{{ DLT_DOW_5 }}", String(conf.dlt.dow == 5 ? " selected" : ""));
  html.replace("{{ DLT_DOW_6 }}", String(conf.dlt.dow == 6 ? " selected" : ""));
  html.replace("{{ DLT_DOW_7 }}", String(conf.dlt.dow == 7 ? " selected" : ""));

  html.replace("{{ DLT_MONTH_1 }}", String(conf.dlt.month == 1 ? " selected" : ""));
  html.replace("{{ DLT_MONTH_2 }}", String(conf.dlt.month == 2 ? " selected" : ""));
  html.replace("{{ DLT_MONTH_3 }}", String(conf.dlt.month == 3 ? " selected" : ""));
  html.replace("{{ DLT_MONTH_4 }}", String(conf.dlt.month == 4 ? " selected" : ""));
  html.replace("{{ DLT_MONTH_5 }}", String(conf.dlt.month == 5 ? " selected" : ""));
  html.replace("{{ DLT_MONTH_6 }}", String(conf.dlt.month == 6 ? " selected" : ""));
  html.replace("{{ DLT_MONTH_7 }}", String(conf.dlt.month == 7 ? " selected" : ""));
  html.replace("{{ DLT_MONTH_8 }}", String(conf.dlt.month == 8 ? " selected" : ""));
  html.replace("{{ DLT_MONTH_9 }}", String(conf.dlt.month == 9 ? " selected" : ""));
  html.replace("{{ DLT_MONTH_10 }}", String(conf.dlt.month == 10 ? " selected" : ""));
  html.replace("{{ DLT_MONTH_11 }}", String(conf.dlt.month == 11 ? " selected" : ""));
  html.replace("{{ DLT_MONTH_12 }}", String(conf.dlt.month == 12 ? " selected" : ""));

  html.replace("{{ DLT_HOUR }}", String(conf.dlt.hour));
  html.replace("{{ DLT_OFFSET }}", String(conf.dlt.offset));

  html.replace("{{ BUZZ_SOUND }}", String(conf.buzzSound ? "checked " : ""));
  html.replace("{{ FAHRENHEIT }}", String(conf.fahrenheit ? "checked " : ""));

  server.send(200, "text/html", html);
}

void handleTimeTempScreen() {
  displaySelector = CLOCK_TEMP;
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "Redirecting to /");
}

void handleDateScreen() {
  displaySelector = DATE;
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "Redirecting to /");
}

void handleHumPresScreen() {
  displaySelector = HUMIDITY_PRESSURE;
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "Redirecting to /");
}

void handleToggleScreen() {
  screen_off = !screen_off;

  if (screen_off)
    matrix->displayShutdown(true);
  else
    matrix->displayShutdown(false);

  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "Redirecting to /");
}

void handleReboot() {
  server.sendHeader("Location", "/", true);
  delay(1000);
  ESP.restart();
}

void handleNetworkSubmit() {
  if (server.method() == HTTP_POST) {
    strncpy(conf.wifi.SSID, server.arg("ssid").c_str(), sizeof(conf.wifi.SSID) - 1);
    strncpy(conf.wifi.PASSWORD, server.arg("password").c_str(), sizeof(conf.wifi.PASSWORD) - 1);
    storeConfiguration(conf);
    server.sendHeader("Location", "/settings", true);
    server.send(302, "text/plain", "Redirecting to /settings");
  } else {
    server.send(405, "text/html", "<html><body><h1>Method Not Allowed</h1></body></html>");
  }
}

void handleNTPSubmit() {
  if (server.method() == HTTP_POST) {
    strncpy(conf.ntpServer, server.arg("ntpServer").c_str(), sizeof(conf.ntpServer) - 1);
    storeConfiguration(conf);
    server.sendHeader("Location", "/settings", true);
    server.send(302, "text/plain", "Redirecting to /settings");
  } else {
    server.send(405, "text/html", "<html><body><h1>Method Not Allowed</h1></body></html>");
  }
}

void handleLanguageSubmit() {
  if (server.method() == HTTP_POST) {
    strncpy(conf.language, server.arg("language").c_str(), sizeof(conf.language) - 1);
    storeConfiguration(conf);
    server.sendHeader("Location", "/settings", true);
    server.send(302, "text/plain", "Redirecting to /settings");
  } else {
    server.send(405, "text/html", "<html><body><h1>Method Not Allowed</h1></body></html>");
  }
}

void handleTimezoneSubmit() {
  if (server.method() == HTTP_POST) {
    strncpy(conf.std.abbrev, server.arg("stdAbbrev").c_str(), sizeof(conf.std.abbrev) - 1);
    conf.std.abbrev[sizeof(conf.std.abbrev) - 1] = '\0';  // Null-terminate the string
    conf.std.week = server.arg("stdWeek").toInt();
    conf.std.dow = server.arg("stdDOW").toInt();
    conf.std.month = server.arg("stdMonth").toInt();
    conf.std.hour = server.arg("stdHour").toInt();
    conf.std.offset = server.arg("stdOffset").toInt();
    strncpy(conf.dlt.abbrev, server.arg("dltAbbrev").c_str(), sizeof(conf.dlt.abbrev) - 1);
    conf.dlt.abbrev[sizeof(conf.dlt.abbrev) - 1] = '\0';  // Null-terminate the string
    conf.dlt.week = server.arg("dltWeek").toInt();
    conf.dlt.dow = server.arg("dltDOW").toInt();
    conf.dlt.month = server.arg("dltMonth").toInt();
    conf.dlt.hour = server.arg("dltHour").toInt();
    conf.dlt.offset = server.arg("dltOffset").toInt();
    storeConfiguration(conf);
    server.sendHeader("Location", "/settings", true);
    server.send(302, "text/plain", "Redirecting to /settings");
  } else {
    server.send(405, "text/html", "<html><body><h1>Method Not Allowed</h1></body></html>");
  }
}

void handleAdditionalSubmit() {
  if (server.method() == HTTP_POST) {
    conf.buzzSound = server.hasArg("buzzSound");
    conf.fahrenheit = server.hasArg("fahrenheit");
    storeConfiguration(conf);
    server.sendHeader("Location", "/settings", true);
    server.send(302, "text/plain", "Redirecting to /settings");
  } else {
    server.send(405, "text/html", "<html><body><h1>Method Not Allowed</h1></body></html>");
  }
}

void handleUpdateTime() {
  wifi_connetion();
  set_NTP_time();
  Serial.println("Disconnecting from WiFi.\n");
  WiFi.disconnect();

  if (server.method() == HTTP_POST) {
    server.sendHeader("Location", "/settings", true);
    server.send(302, "text/plain", "Redirecting to /settings");
  }
  else {
    server.send(405, "text/html", "<html><body><h1>Method Not Allowed</h1></body></html>");
    return;
  }
}
