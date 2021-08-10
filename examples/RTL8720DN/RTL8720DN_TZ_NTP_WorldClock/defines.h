/****************************************************************************************************************************
  defines.h
  
  For AVR, ESP8266/ESP32, SAMD21/SAMD51, nRF52, STM32, SAM DUE, WT32_ETH01,  boards using 
  a) Ethernet W5x00, ENC28J60, LAN8742A
  b) WiFiNINA
  c) ESP8266/ESP32 WiFi
  d) ESP8266/ESP32-AT-command WiFi
  e) WT32_ETH01 (ESP32 + LAN8720)
  f) RTL8720DN

  Based on and modified from Arduino NTPClient Library (https://github.com/arduino-libraries/NTPClient)
  to support other boards such as ESP8266/ESP32, SAMD21, SAMD51, Adafruit's nRF52 boards, SAM DUE, RTL8720DN, etc.
  and Ethernet/WiFi/WiFiNINA shields
  
  Copyright (C) 2015 by Fabrice Weinberg and licensed under MIT License (MIT)

  Built by Khoi Hoang https://github.com/khoih-prog/NTPClient_Generic
  Licensed under MIT license
 *****************************************************************************************************************************/

#ifndef defines_h
#define defines_h

#if !( defined(CONFIG_PLATFORM_8721D) || defined(BOARD_RTL8722D) || defined(BOARD_RTL8722DM_MINI) || defined(BOARD_RTL8720DN_BW16) ) 
  #error This code is intended to run on the AmebaD RTL8720DN platform! Please check your Tools->Board setting.
#endif

#define DEBUG_WIFI_WEBSERVER_PORT   Serial
#define NTP_DBG_PORT                Serial

// Debug Level from 0 to 4
#define _WIFI_LOGLEVEL_             3
#define _NTP_LOGLEVEL_              0

#include <WiFiWebServer_RTL8720.h>

char ssid[] = "SSID_5GHz";        // your network SSID (name)
char pass[] = "12345678";        // your network password

#endif    //defines_h
