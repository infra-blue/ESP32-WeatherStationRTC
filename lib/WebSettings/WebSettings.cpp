#include "WebSettings.h"

void handleSettings() {
    String html = R"(
    <!DOCTYPE HTML>
    <html>
      <head>
        <title>ESP32 Settings</title>
        <style>
          body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 20px;
            background-color: #222;
            color: #fff;
          }
          h1 {
            text-align: center;
            font-size: 2em;
            color: white;
            margin-bottom: 20px;
          }
          form {
            margin-top: 20px;
            max-width: 600px;
            margin-left: auto;
            margin-right: auto;
            background-color: rgba(50, 50, 50, 0.8);
            padding: 20px;
            border-radius: 8px;
          }
          label {
            display: block;
            margin-bottom: 10px;
          }
          input[type="text"],
          select,
          input[type="number"],
          input[type="password"] {
            width: calc(100% - 22px);
            padding: 10px;
            margin-bottom: 10px;
            border: 1px solid #ccc;
            border-radius: 4px;
            box-sizing: border-box;
            background-color: #444;
            color: #fff;
          }
          input[type="submit"] {
            background-color: #007bff; /* Blue */
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            display: block;
            margin-left: 0;
            margin-right: auto;
            width: 100%;
          }
          input[type="submit"]:hover {
            background-color: #0056b3; /* Darker Blue */
          }
          .section {
            margin-bottom: 20px;
            padding: 10px;
            border: 1px solid #555;
            border-radius: 8px;
            background-color: #444;
          }
          .section h2 {
            margin-top: 0;
            font-size: 1.2em;
            border-bottom: 1px solid #555;
            padding-bottom: 10px;
          }
          .checkbox-container {
            display: flex;
            align-items: center;
            margin-bottom: 10px;
          }
          .checkbox-container label {
            margin-bottom: 0;
            margin-right: 10px;
          }
          .checkbox-container label:first-child {
            margin-right: 0;
          }
          @media (max-width: 600px) {
            form {
              max-width: 100%;
            }
          }
        </style>
      </head>
      <body>
        <h1><strong>ESP32 WeatherStation</strong> Settings</h1>
        <form action="/" method="get">
          <input type="submit" value="Home">
        </form>
        <form action="/toggleScreen" method="post">
          <input type="submit" value=")" +
          String(screen_off ? "Turn On Screen" : "Turn Off Screen") + R"(" style="width: 100%;">
        </form>

        <!-- Network Settings Form -->
        <form action="/submitNetwork" method="post">
          <div class="section">
            <h2>Network Settings</h2>
            <label for="ssid">SSID:</label>
            <input type="text" id="ssid" name="ssid" value=")" +
              String(conf.wifi.SSID) + R"("><br>
            <label for="password">Password:</label>
            <input type="password" id="password" name="password" value=""><br>
            <input type="submit" value="Save Network Settings">
          </div>
        </form>

        <!-- NTP Server Form -->
        <form action="/submitNTP" method="post">
          <div class="section">
            <h2>NTP Server Settings</h2>
            <label for="ntpServer">NTP Server:</label>
            <input type="text" id="ntpServer" name="ntpServer" value=")" +
              String(conf.ntpServer) + R"("><br>
            <input type="submit" value="Save NTP Server">
          </div>
        </form>

        <form action="/updateTime" method="post">
          <input type="submit" value="Update Time">
        </form>

        <!-- Language Form -->
        <form action="/submitLanguage" method="post">
          <div class="section">
            <h2>Language Settings</h2>
            <label for="language">Language:</label>
            <select id="language" name="language">
              <option value="en")" +
              String(!strcmp(conf.language, "en") ? " selected" : "") + R"(>English</option>
              <option value="it")" +
              String(!strcmp(conf.language, "it") ? " selected" : "") + R"(>Italian</option>
              <option value="es")" +
              String(!strcmp(conf.language, "es") ? " selected" : "") + R"(>Spanish</option>
              <option value="de")" +
              String(!strcmp(conf.language, "de") ? " selected" : "") + R"(>German</option>
              <option value="fr")" +
              String(!strcmp(conf.language, "fr") ? " selected" : "") + R"(>French</option>
            </select><br>
            <input type="submit" value="Save Language Settings">
          </div>
        </form>

        <!-- Timezone Settings Form -->
        <form action="/submitTimezone" method="post">
          <div class="section">
            <h2>Timezone Settings</h2>
            <h3>Standard Time</h3>
            <label for="stdAbbrev">Abbreviation:</label>
            <input type="text" id="stdAbbrev" name="stdAbbrev" value=")" +
              String(conf.std.abbrev) + R"("><br>
            <label for="stdWeek">Week:</label>
            <select id="stdWeek" name="stdWeek">
              <option value="1")" +
              String(conf.std.week == 1 ? " selected" : "") + R"(>First</option>
              <option value="2")" +
              String(conf.std.week == 2 ? " selected" : "") + R"(>Second</option>
              <option value="3")" +
              String(conf.std.week == 3 ? " selected" : "") + R"(>Third</option>
              <option value="4")" +
              String(conf.std.week == 4 ? " selected" : "") + R"(>Fourth</option>
              <option value="5")" +
              String(conf.std.week == 5 ? " selected" : "") + R"(>Last</option>
            </select><br>
            <label for="stdDOW">Day of Week:</label>
            <select id="stdDOW" name="stdDOW">
              <option value="1")" +
              String(conf.std.dow == 1 ? " selected" : "") + R"(>Sunday</option>
              <option value="2")" +
              String(conf.std.dow == 2 ? " selected" : "") + R"(>Monday</option>
              <option value="3")" +
              String(conf.std.dow == 3 ? " selected" : "") + R"(>Tuesday</option>
              <option value="4")" +
              String(conf.std.dow == 4 ? " selected" : "") + R"(>Wednesday</option>
              <option value="5")" +
              String(conf.std.dow == 5 ? " selected" : "") + R"(>Thursday</option>
              <option value="6")" +
              String(conf.std.dow == 6 ? " selected" : "") + R"(>Friday</option>
              <option value="7")" +
              String(conf.std.dow == 7 ? " selected" : "") + R"(>Saturday</option>
            </select><br>
            <label for="stdMonth">Month:</label>
            <select id="stdMonth" name="stdMonth">
              <option value="1")" +
              String(conf.std.month == 1 ? " selected" : "") + R"(>January</option>
              <option value="2")" +
              String(conf.std.month == 2 ? " selected" : "") + R"(>February</option>
              <option value="3")" +
              String(conf.std.month == 3 ? " selected" : "") + R"(>March</option>
              <option value="4")" +
              String(conf.std.month == 4 ? " selected" : "") + R"(>April</option>
              <option value="5")" +
              String(conf.std.month == 5 ? " selected" : "") + R"(>May</option>
              <option value="6")" +
              String(conf.std.month == 6 ? " selected" : "") + R"(>June</option>
              <option value="7")" +
              String(conf.std.month == 7 ? " selected" : "") + R"(>July</option>
              <option value="8")" +
              String(conf.std.month == 8 ? " selected" : "") + R"(>August</option>
              <option value="9")" +
              String(conf.std.month == 9 ? " selected" : "") + R"(>September</option>
              <option value="10")" +
              String(conf.std.month == 10 ? " selected" : "") + R"(>October</option>
              <option value="11")" +
              String(conf.std.month == 11 ? " selected" : "") + R"(>November</option>
              <option value="12")" +
              String(conf.std.month == 12 ? " selected" : "") + R"(>December</option>
            </select><br>
            <label for="stdHour">Hour:</label>
            <input type="number" id="stdHour" name="stdHour" min="0" max="23" value=")" +
              String(conf.std.hour) + R"("><br>
            <label for="stdOffset">Offset:</label>
            <input type="number" id="stdOffset" name="stdOffset" value=")" +
              String(conf.std.offset) + R"("><br>
            <h3>Daylight Saving Time</h3>
            <label for="dltAbbrev">Abbreviation:</label>
            <input type="text" id="dltAbbrev" name="dltAbbrev" value=")" +
              String(conf.dlt.abbrev) + R"("><br>
            <label for="dltWeek">Week:</label>
            <select id="dltWeek" name="dltWeek">
              <option value="1")" +
              String(conf.dlt.week == 1 ? " selected" : "") + R"(>First</option>
              <option value="2")" +
              String(conf.dlt.week == 2 ? " selected" : "") + R"(>Second</option>
              <option value="3")" +
              String(conf.dlt.week == 3 ? " selected" : "") + R"(>Third</option>
              <option value="4")" +
              String(conf.dlt.week == 4 ? " selected" : "") + R"(>Fourth</option>
              <option value="5")" +
              String(conf.dlt.week == 5 ? " selected" : "") + R"(>Last</option>
            </select><br>
            <label for="dltDOW">Day of Week:</label>
            <select id="dltDOW" name="dltDOW">
              <option value="1")" +
              String(conf.dlt.dow == 1 ? " selected" : "") + R"(>Sunday</option>
              <option value="2")" +
              String(conf.dlt.dow == 2 ? " selected" : "") + R"(>Monday</option>
              <option value="3")" +
              String(conf.dlt.dow == 3 ? " selected" : "") + R"(>Tuesday</option>
              <option value="4")" +
              String(conf.dlt.dow == 4 ? " selected" : "") + R"(>Wednesday</option>
              <option value="5")" +
              String(conf.dlt.dow == 5 ? " selected" : "") + R"(>Thursday</option>
              <option value="6")" +
              String(conf.dlt.dow == 6 ? " selected" : "") + R"(>Friday</option>
              <option value="7")" +
              String(conf.dlt.dow == 7 ? " selected" : "") + R"(>Saturday</option>
            </select><br>
            <label for="dltMonth">Month:</label>
            <select id="dltMonth" name="dltMonth">
              <option value="1")" +
              String(conf.dlt.month == 1 ? " selected" : "") + R"(>January</option>
              <option value="2")" +
              String(conf.dlt.month == 2 ? " selected" : "") + R"(>February</option>
              <option value="3")" +
              String(conf.dlt.month == 3 ? " selected" : "") + R"(>March</option>
              <option value="4")" +
              String(conf.dlt.month == 4 ? " selected" : "") + R"(>April</option>
              <option value="5")" +
              String(conf.dlt.month == 5 ? " selected" : "") + R"(>May</option>
              <option value="6")" +
              String(conf.dlt.month == 6 ? " selected" : "") + R"(>June</option>
              <option value="7")" +
              String(conf.dlt.month == 7 ? " selected" : "") + R"(>July</option>
              <option value="8")" +
              String(conf.dlt.month == 8 ? " selected" : "") + R"(>August</option>
              <option value="9")" +
              String(conf.dlt.month == 9 ? " selected" : "") + R"(>September</option>
              <option value="10")" +
              String(conf.dlt.month == 10 ? " selected" : "") + R"(>October</option>
              <option value="11")" +
              String(conf.dlt.month == 11 ? " selected" : "") + R"(>November</option>
              <option value="12")" +
              String(conf.dlt.month == 12 ? " selected" : "") + R"(>December</option>
            </select><br>
            <label for="dltHour">Hour:</label>
            <input type="number" id="dltHour" name="dltHour" min="0" max="23" value=")" +
              String(conf.dlt.hour) + R"("><br>
            <label for="dltOffset">Offset:</label>
            <input type="number" id="dltOffset" name="dltOffset" value=")" +
              String(conf.dlt.offset) + R"("><br>
            <input type="submit" value="Save Timezone Settings">
          </div>
        </form>

        <!-- Additional Settings Form -->
        <form action="/submitAdditional" method="post">
          <div class="section">
            <h2>Additional Settings</h2>
            <div class="checkbox-container">
              <label for="buzzSound">Buzzer Sound</label>
              <input type="checkbox" id="buzzSound" name="buzzSound")" + String(conf.buzzSound ? " checked " : "") + R"()>
            </div>
            <div class="checkbox-container">
              <label for="fahrenheit">Temperature in Fahrenheit</label>
              <input type="checkbox" id="fahrenheit" name="fahrenheit")" + String(conf.fahrenheit ? " checked " : "") + R"()>
            </div>
            <input type="submit" value="Save Additional Settings">
          </div>
        </form>
      </body>
    </html>
    )";

    server.send(200, "text/html", html);
}

void handleNetworkSubmit() {
  if (server.method() == HTTP_POST) {
    strncpy(conf.wifi.SSID, server.arg("ssid").c_str(), sizeof(conf.wifi.SSID) - 1);
    strncpy(conf.wifi.PASSWORD, server.arg("password").c_str(), sizeof(conf.wifi.PASSWORD) - 1);
    storeConfiguration(conf);
    server.sendHeader("Location", "/settings", true);
    server.send(302, "text/plain", "Redirecting to /");
  } else {
    server.send(405, "text/html", "<html><body><h1>Method Not Allowed</h1></body></html>");
  }
}

void handleNTPSubmit() {
  if (server.method() == HTTP_POST) {
    strncpy(conf.ntpServer, server.arg("ntpServer").c_str(), sizeof(conf.ntpServer) - 1);
    storeConfiguration(conf);
    server.sendHeader("Location", "/settings", true);
    server.send(302, "text/plain", "Redirecting to /");
  } else {
    server.send(405, "text/html", "<html><body><h1>Method Not Allowed</h1></body></html>");
  }
}

void handleLanguageSubmit() {
  if (server.method() == HTTP_POST) {
    strncpy(conf.language, server.arg("language").c_str(), sizeof(conf.language) - 1);
    storeConfiguration(conf);
    server.sendHeader("Location", "/settings", true);
    server.send(302, "text/plain", "Redirecting to /");
  } else {
    server.send(405, "text/html", "<html><body><h1>Method Not Allowed</h1></body></html>");
  }
}

void handleTimezoneSubmit() {
  if (server.method() == HTTP_POST) {
    // Update timezone configuration from POST data
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
    server.send(302, "text/plain", "Redirecting to /");
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
    server.send(302, "text/plain", "Redirecting to /");
  } else {
    server.send(405, "text/html", "<html><body><h1>Method Not Allowed</h1></body></html>");
  }
}

void handleToggleScreen() {
  screen_off = !screen_off;

  if (screen_off)
    matrix->displayShutdown(true);
  else
    matrix->displayShutdown(false);

  server.sendHeader("Location", "/settings", true);
  server.send(302, "text/plain", "Redirecting to /");
}

void handleUpdateTime() {
  if (server.method() == HTTP_POST) {
    server.sendHeader("Location", "/settings", true);
    server.send(302, "text/plain", "Redirecting to /");
  }
  else {
    server.send(405, "text/html", "<html><body><h1>Method Not Allowed</h1></body></html>");
    return;
  }
  set_NTP_time();
}

void handleHome() {
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0;
  String temperatureUnit = conf.fahrenheit ? "Fahrenheit" : "Celsius";
  String temperatureValue = conf.fahrenheit ? String(temperature * 1.8 + 32) : String(temperature);

  int year = current_time.year();
  int month = current_time.month();
  int day = current_time.day();
  int hour = current_time.hour();
  int minute = current_time.minute();
  int second = current_time.second();

  String html = R"HTML(
    <!DOCTYPE html>
    <html lang="en">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Home</title>
      <style>
        body {
          font-family: Arial, sans-serif;
          background-color: #222;
          color: #fff;
          margin: 0;
          padding: 20px;
        }
        h1 {
          text-align: center;
          font-size: 2em;
          color: #007bff;
          margin-bottom: 20px;
        }
        .container {
          max-width: 600px;
          margin: 0 auto;
          background-color: rgba(50, 50, 50, 0.8);
          padding: 20px;
          border-radius: 8px;
          box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);
          display: flex;
          flex-direction: column;
          align-items: center; /* Center align items horizontally */
          text-align: center; /* Center align text */
        }
        p {
          font-size: 18px;
          line-height: 1.6;
          margin: 10px 0;
        }
        .data {
          font-weight: bold;
          color: #03dac6;
        }
        .button {
          display: inline-block;
          padding: 10px 20px;
          font-size: 18px;
          color: white;
          background-color: #007bff;
          border: none;
          border-radius: 5px;
          text-decoration: none;
          margin-top: 20px;
          text-align: center;
        }
        .button:hover {
          background-color: #0056b3;
        }
        @media (max-width: 600px) {
          body {
            padding: 10px;
          }
          .container {
            width: 100%;
            padding: 15px;
            box-shadow: none;
          }
          h1 {
            font-size: 1.5em;
          }
          p {
            font-size: 16px;
          }
          .button {
            width: 100%;
            padding: 12px;
            font-size: 16px;
          }
        }
      </style>
    </head>
    <body>
      <div class="container">
        <h1>Sensor Data</h1>
        <p>Temperature: <span class="data">)HTML" + temperatureValue + " " + temperatureUnit + R"HTML(</span></p>
        <p>Humidity: <span class="data">)HTML" + String(humidity) + R"HTML( %</span></p>
        <p>Pressure: <span class="data">)HTML" + String(pressure) + R"HTML( hPa</span></p>
        <h1>Date and Time</h1>
        <p>Date: <span class="data">)HTML" + String(day) + "/" + String(month) + "/" + String(year) + R"HTML(</span></p>
        <p>Time: <span class="data">)HTML" + String(hour) + ":" + String(minute) + ":" + String(second) + R"HTML(</span></p>
        <a href='/settings' class="button">Go to Settings</a>
      </div>
    </body>
    </html>
    )HTML";

  // Send HTML page as response
  server.send(200, "text/html", html);
}
