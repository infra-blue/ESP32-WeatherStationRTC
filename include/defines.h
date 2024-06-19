#pragma once

/**
 * @brief 
 * 
 * WiFi settings
 * 
 */
#define YOUR_SSID "clock"
#define YOUR_PASSWORD "coglione1"

/**
 * @brief 
 * 
 * NTP Servers
 * 
 */

#define MCNTP "time.windows.com"
#define POOLNTP "pool.ntp.org"
#define POOLNTP1 "0.it.pool.ntp.org"
#define INRIM "time.inrim.it"
#define INRIM1 "ntp1.inrim.it"
#define INRIM2 "ntp2.inrim.it"

/**
 * @brief 
 * 
 * MAX7219 display settings
 * 
 */

#define CLK_PIN   12
#define DATA_PIN  11
#define CS_PIN    10

#define MAX_DEVICES 4
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW