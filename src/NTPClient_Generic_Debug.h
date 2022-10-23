/****************************************************************************************************************************
  NTPClient_Generic_Debug.h
 
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

#ifndef NTPCLIENT_GENERIC_DEBUG_H
#define NTPCLIENT_GENERIC_DEBUG_H

#ifdef NTP_DEBUG_PORT
  #define NTP_DBG_PORT      NTP_DEBUG_PORT
#else
  #define NTP_DBG_PORT      Serial
#endif

// Change _NTP_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _NTP_LOGLEVEL_
  #define _NTP_LOGLEVEL_       0
#endif

///////////////////////////////////////

const char NTP_MARK[]  = "[NTP] ";
const char NTP_SPACE[] = " ";

#define NTP_PRINT        NTP_DBG_PORT.print
#define NTP_PRINTLN      NTP_DBG_PORT.println

#define NTP_PRINT_MARK   NTP_PRINT(NTP_MARK)
#define NTP_PRINT_SP     NTP_PRINT(NTP_SPACE)
#define NTP_PRINT_LINE   NTP_PRINT(NTP_LINE)

///////////////////////////////////////

#define NTP_LOGERROR(x)         if(_NTP_LOGLEVEL_>0) { NTP_PRINT_MARK; NTP_PRINTLN(x); }
#define NTP_LOGERROR0(x)        if(_NTP_LOGLEVEL_>0) { NTP_PRINT(x); }
#define NTP_LOGERROR1(x,y)      if(_NTP_LOGLEVEL_>0) { NTP_PRINT_MARK; NTP_PRINT(x); NTP_PRINT_SP; NTP_PRINTLN(y); }
#define NTP_LOGERROR2(x,y,z)    if(_NTP_LOGLEVEL_>0) { NTP_PRINT_MARK; NTP_PRINT(x); NTP_PRINT_SP; NTP_PRINT(y); NTP_PRINT_SP; NTP_PRINTLN(z); }
#define NTP_LOGERROR3(x,y,z,w)  if(_NTP_LOGLEVEL_>0) { NTP_PRINT_MARK; NTP_PRINT(x); NTP_PRINT_SP; NTP_PRINT(y); NTP_PRINT_SP; NTP_PRINT(z); NTP_PRINT_SP; NTP_PRINTLN(w); }

///////////////////////////////////////

#define NTP_LOGWARN(x)          if(_NTP_LOGLEVEL_>1) { NTP_PRINT_MARK; NTP_PRINTLN(x); }
#define NTP_LOGWARN0(x)         if(_NTP_LOGLEVEL_>1) { NTP_PRINT(x); }
#define NTP_LOGWARN1(x,y)       if(_NTP_LOGLEVEL_>1) { NTP_PRINT_MARK; NTP_PRINT(x); NTP_PRINT_SP; NTP_PRINTLN(y); }
#define NTP_LOGWARN2(x,y,z)     if(_NTP_LOGLEVEL_>1) { NTP_PRINT_MARK; NTP_PRINT(x); NTP_PRINT_SP; NTP_PRINT(y); NTP_PRINT_SP; NTP_PRINTLN(z); }
#define NTP_LOGWARN3(x,y,z,w)   if(_NTP_LOGLEVEL_>1) { NTP_PRINT_MARK; NTP_PRINT(x); NTP_PRINT_SP; NTP_PRINT(y); NTP_PRINT_SP; NTP_PRINT(z); NTP_PRINT_SP; NTP_PRINTLN(w); }

///////////////////////////////////////

#define NTP_LOGINFO(x)          if(_NTP_LOGLEVEL_>2) { NTP_PRINT_MARK; NTP_PRINTLN(x); }
#define NTP_LOGINFO0(x)         if(_NTP_LOGLEVEL_>2) { NTP_PRINT(x); }
#define NTP_LOGINFO1(x,y)       if(_NTP_LOGLEVEL_>2) { NTP_PRINT_MARK; NTP_PRINT(x); NTP_PRINT_SP; NTP_PRINTLN(y); }
#define NTP_LOGINFO2(x,y,z)     if(_NTP_LOGLEVEL_>2) { NTP_PRINT_MARK; NTP_PRINT(x); NTP_PRINT_SP; NTP_PRINT(y); NTP_PRINT_SP; NTP_PRINTLN(z); }
#define NTP_LOGINFO3(x,y,z,w)   if(_NTP_LOGLEVEL_>2) { NTP_PRINT_MARK; NTP_PRINT(x); NTP_PRINT_SP; NTP_PRINT(y); NTP_PRINT_SP; NTP_PRINT(z); NTP_PRINT_SP; NTP_PRINTLN(w); }

///////////////////////////////////////

#define NTP_LOGDEBUG(x)         if(_NTP_LOGLEVEL_>3) { NTP_PRINT_MARK; NTP_PRINTLN(x); }
#define NTP_LOGDEBUG0(x)        if(_NTP_LOGLEVEL_>3) { NTP_PRINT(x); }
#define NTP_LOGDEBUG1(x,y)      if(_NTP_LOGLEVEL_>3) { NTP_PRINT_MARK; NTP_PRINT(x); NTP_PRINT_SP; NTP_PRINTLN(y); }
#define NTP_LOGDEBUG2(x,y,z)    if(_NTP_LOGLEVEL_>3) { NTP_PRINT_MARK; NTP_PRINT(x); NTP_PRINT_SP; NTP_PRINT(y); NTP_PRINT_SP; NTP_PRINTLN(z); }
#define NTP_LOGDEBUG3(x,y,z,w)  if(_NTP_LOGLEVEL_>3) { NTP_PRINT_MARK; NTP_PRINT(x); NTP_PRINT_SP; NTP_PRINT(y); NTP_PRINT_SP; NTP_PRINT(z); NTP_PRINT_SP; NTP_PRINTLN(w); }

///////////////////////////////////////

#endif    // NTPCLIENT_GENERIC_DEBUG_H
