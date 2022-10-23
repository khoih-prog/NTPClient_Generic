/****************************************************************************************************************************
  NTPClient_Generic.h
 
  For AVR, ESP8266/ESP32, SAMD21/SAMD51, nRF52, STM32, SAM DUE, WT32_ETH01, RTL8720DN, RP2040 boards using 
  1) Ethernet W5x00, ENC28J60, LAN8742A
  2) WiFiNINA
  3) ESP8266/ESP32 WiFi
  4) ESP8266/ESP32-AT-command WiFi
  5) WT32_ETH01 (ESP32 + LAN8720)
  6) RTL8720DN
  7) Portenta_H7
  8) RP2040W WiFi

  Based on and modified from Arduino NTPClient Library (https://github.com/arduino-libraries/NTPClient)
  to support other boards such as ESP8266/ESP32, SAMD21, SAMD51, Adafruit's nRF52 boards, SAM DUE, RTL8720DN, etc.
  and Ethernet/WiFi/WiFiNINA shields
  
  Copyright (C) 2015 by Fabrice Weinberg and licensed under MIT License (MIT)

  Built by Khoi Hoang https://github.com/khoih-prog/NTPClient_Generic
  Licensed under MIT license
  
  Version: 3.7.5

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
  3.7.1   K Hoang      20/01/2022 Fix getUTCEpochMillis() bug
  3.7.2   K Hoang      23/02/2022 Add setUDP() function to enable auto-switching between WiFi and Ethernet UDP
  3.7.3   K Hoang      05/04/2022 Use Ethernet_Generic library as default. Support SPI1/SPI2 for RP2040/ESP32
  3.7.4   K Hoang      27/04/2022 Sync with NTPClient releases v3.2.1
  3.7.5   K Hoang      22/10/2022 Fix bug causing time jumping back or forth when network has problem
 *****************************************************************************************************************************/
 
#pragma once

// Reintroduce to prevent duplication compile error, pragma once can't prevent
#ifndef NTPCLIENT_GENERIC_H
#define NTPCLIENT_GENERIC_H

#include "NTPClient_Generic.hpp"
#include "NTPClient_Generic_Impl.h"

#endif    // NTPCLIENT_GENERIC_H
