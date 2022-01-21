/****************************************************************************************************************************
  NTPClient_Generic.h
 
  For AVR, ESP8266/ESP32, SAMD21/SAMD51, nRF52, STM32, SAM DUE, WT32_ETH01, RTL8720DN boards using 
  a) Ethernet W5x00, ENC28J60, LAN8742A
  b) WiFiNINA
  c) ESP8266/ESP32 WiFi
  d) ESP8266/ESP32-AT-command WiFi
  e) WT32_ETH01 (ESP32 + LAN8720)
  f) RTL8720DN
  g) Portenta_H7

  Based on and modified from Arduino NTPClient Library (https://github.com/arduino-libraries/NTPClient)
  to support other boards such as ESP8266/ESP32, SAMD21, SAMD51, Adafruit's nRF52 boards, SAM DUE, RTL8720DN, etc.
  and Ethernet/WiFi/WiFiNINA shields
  
  Copyright (C) 2015 by Fabrice Weinberg and licensed under MIT License (MIT)

  Built by Khoi Hoang https://github.com/khoih-prog/NTPClient_Generic
  Licensed under MIT license
  Version: 3.7.0

  Version Modified By  Date      Comments
  ------- -----------  ---------- -----------
  3.2.1   K Hoang      27/10/2020 Initial porting to support SAM DUE, SAMD21, SAMD51, nRF52, ESP32/ESP8266, STM32, etc. boards 
                                  using Ethernet/WiFi/WiFiNINA shields. Add more features and functions.
  3.2.2   K Hoang      28/10/2020 Add examples to use STM32 Built-In RTC.
  3.3.0   K Hoang      04/06/2021 Add support to RP2040-based boards. Add packet validity checks, version string and debug
  3.4.0   K Hoang      16/07/2021 Add support to WT32_ETH01 (ESP32 + LAN8720)
  3.5.0   K Hoang      10/08/2021 Add support to Ameba Realtek RTL8720DN, RTL8722DM and RTL8722CSM
  3.5.1   K Hoang      12/10/2021 Update `platform.ini` and `library.json`
  3.5.2   K Hoang      01/12/2021 Auto detect ESP32 core version. Fix bug in examples for WT32_ETH01
  3.6.0   K Hoang      08/01/2022 Fix `multiple-definitions` linker error. Add support to Portenta_H7
  3.7.0   K Hoang      20/01/2022 Make compatible to old code
 *****************************************************************************************************************************/
 
#pragma once

// Reintroduce to prevent duplication compile error, pragma once can't prevent
#ifndef NTPCLIENT_GENERIC_H
#define NTPCLIENT_GENERIC_H

#include "NTPClient_Generic.hpp"
#include "NTPClient_Generic_Impl.h"

#endif    // NTPCLIENT_GENERIC_H
