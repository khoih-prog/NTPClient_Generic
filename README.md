## NTPClient_Generic Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/NTPClient_Generic.svg?)](https://www.ardu-badge.com/NTPClient_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/NTPClient_Generic.svg)](https://github.com/khoih-prog/NTPClient_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/NTPClient_Generic/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/NTPClient_Generic.svg)](http://github.com/khoih-prog/NTPClient_Generic/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>

---
---

## Table of Contents

* [Important Change from v3.7.0](#Important-Change-from-v370)
* [Why do we need this NTPClient_Generic library](#why-do-we-need-this-ntpclient_generic-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
  * [Currently supported WiFi shields/modules](#currently-supported-wifi-shieldsmodules)
  * [Currently supported Ethernet shields/modules](#currently-supported-ethernet-shieldsmodules)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Teensy boards](#2-for-teensy-boards)
  * [3. For Arduino SAM DUE boards](#3-for-arduino-sam-due-boards)
  * [4. For Arduino SAMD boards](#4-for-arduino-samd-boards)
      * [For core version v1.8.10+](#for-core-version-v1810)
      * [For core version v1.8.9-](#for-core-version-v189-)
  * [5. For Adafruit SAMD boards](#5-for-adafruit-samd-boards)
  * [6. For Seeeduino SAMD boards](#6-for-seeeduino-samd-boards)
  * [7. For STM32 boards](#7-for-stm32-boards) 
    * [7.1. For STM32 boards to use LAN8720](#71-for-stm32-boards-to-use-lan8720)
    * [7.2. For STM32 boards to use Serial1](#72-for-stm32-boards-to-use-serial1)
  * [8. For RP2040-based boards using Earle Philhower arduino-pico core](#8-for-rp2040-based-boards-using-earle-philhower-arduino-pico-core)
    * [8.1. To use BOARD_NAME](#81-to-use-board_name)
    * [8.2. To avoid compile error relating to microsecondsToClockCycles](#82-to-avoid-compile-error-relating-to-microsecondstoclockcycles)
  * [9. For Portenta_H7 boards using Arduino IDE in Linux](#9-for-portenta_h7-boards-using-arduino-ide-in-linux)
  * [10. For RTL8720DN boards using AmebaD core](#10-for-rtl8720dn-boards-using-amebad-core)
  * [11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core](#11-For-SAMD21-and-SAMD51-boards-using-ArduinoCore-fab-sam-core)
  * [12. For Seeeduino RP2040 boards](#12-For-Seeeduino-RP2040-boards)
* [Libraries' Patches](#libraries-patches)
  * [1. For application requiring 2K+ HTML page](#1-for-application-requiring-2k-html-page)
  * [2. For Ethernet library](#2-for-ethernet-library)
  * [3. For EthernetLarge library](#3-for-ethernetlarge-library)
  * [4. For Etherne2 library](#4-for-ethernet2-library)
  * [5. For Ethernet3 library](#5-for-ethernet3-library)
  * [6. For UIPEthernet library](#6-for-uipethernet-library)
  * [7. For fixing ESP32 compile error](#7-for-fixing-esp32-compile-error)
  * [8. For fixing ESP8266 compile error](#8-for-fixing-esp8266-compile-error)
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)
* [HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)](#howto-use-analogread-with-esp32-running-wifi-andor-bluetooth-btble)
  * [1. ESP32 has 2 ADCs, named ADC1 and ADC2](#1--esp32-has-2-adcs-named-adc1-and-adc2)
  * [2. ESP32 ADCs functions](#2-esp32-adcs-functions)
  * [3. ESP32 WiFi uses ADC2 for WiFi functions](#3-esp32-wifi-uses-adc2-for-wifi-functions)
* [Important Notes](#important-notes)
* [Examples](#examples)
  * [ESP32/ESP8266 Boards](#esp32esp8266-boards)
  * [Generic Boards with Ethernet](#generic-boards-with-ethernet)
  * [STM32F/L/H/G/WB/MP1 Boards with Ethernet](#stm32flhgwbmp1-boards-with-ethernet)
  * [Generic Boards with WiFiNINA](#generic-boards-with-wifinina)
  * [WT32_ETH01 Boards](#wt32_eth01-boards)
  * [RTL8720DN Boards](#rtl8720dn-boards)
  * [Portenta_H7 Boards with WiFi](#Portenta_H7-Boards-with-WiFi)
  * [Portenta_H7 Boards with Ethernet](#Portenta_H7-Boards-with-Ethernet)
  * [General](#General)
* [Example RTC_Ethernet_NTPClient](#example-rtc_ethernet_ntpclient)
  * [ 1. File RTC_Ethernet_NTPClient.ino](#1-file-rtc_ethernet_ntpclientino)
  * [ 2. File defines.h](#2-file-definesh)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [ 1. Ethernet_NTPClient_Advanced on Adafruit NRF52840_FEATHER_EXPRESS with ENC28J60 using EthernetENC Library](#1-ethernet_ntpclient_advanced-on-adafruit-nrf52840_feather_express-with-enc28J60-using-ethernetenc-library)
  * [ 2. NINA_NTPClient_Advanced on Arduino SAMD21 SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library](#2-nina_ntpclient_advanced-on-arduino-samd21-samd_nano_33_iot-with-wifinina-using-wifinina_generic-library)
  * [ 3. TZ_NTP_WorldClock_Ethernet on Adafruit NRF52840_FEATHER_EXPRESS with W5500 using Ethernet_Generic Library](#3-tz_ntp_worldclock_ethernet-on-adafruit-nrf52840_feather_express-with-w5500-using-Ethernet_Generic-library)
  * [ 4. TZ_NTP_WorldClock_STM32_Ethernet on STM32F7 Nucleo-144 NUCLEO_F767ZI with LAN8742A using STM32Ethernet Library](#4-tz_ntp_worldclock_stm32_ethernet-on-stm32f7-nucleo-144-nucleo_f767zi-with-lan8742a-using-stm32ethernet-library)
  * [ 5. RTC_Ethernet_NTPClient on Adafruit NRF52840_FEATHER_EXPRESS with ENC28J60 using EthernetENC Library](#5-rtc_ethernet_ntpclient-on-adafruit-nrf52840_feather_express-with-enc28J60-using-ethernetenc-library)
  * [ 6. RTC_Ethernet_NTPClient_STM32 on STM32F7 Nucleo-144 NUCLEO_F767ZI with LAN8742A using STM32Ethernet Library](#6-rtc_ethernet_ntpclient_stm32-on-stm32f7-nucleo-144-nucleo_f767zi-with-lan8742a-using-stm32ethernet-library)
  * [ 7. ESP_NTPClient_Advanced on ESP8266_NODEMCU_ESP12E](#7-esp_ntpclient_advanced-on-esp8266_nodemcu_esp12e)
  * [ 8. ESP_NTPClient_Advanced on ESP32_DEV](#8-esp_ntpclient_advanced-on-esp32_dev)
  * [ 9. Ethernet_NTPClient_Advanced on SAM DUE with W5100 using Ethernet_Generic Library](#9-ethernet_ntpclient_advanced-on-sam-due-with-w5100-using-Ethernet_Generic-library)
  * [10. BI_RTC_Ethernet_NTPClient_STM32 on STM32F7 Nucleo-144 NUCLEO_F767ZI with LAN8742A using STM32Ethernet Library](#10-bi_rtc_ethernet_ntpclient_stm32-on-stm32f7-nucleo-144-nucleo_f767zi-with-lan8742a-using-stm32ethernet-library)
  * [11. BI_RTC_Ethernet_NTPClient_STM32 on STM32F7 Nucleo-144 NUCLEO_F767ZI with ENC28J60 using EthernetENC Library](#11-bi_rtc_ethernet_ntpclient_stm32-on-stm32f7-nucleo-144-nucleo_f767zi-with-enc28J60-using-ethernetenc-library)
  * [12. BI_RTC_Alarm_Ethernet_NTPClient_STM32 on STM32F7 Nucleo-144 NUCLEO_F767ZI with LAN8742A using STM32Ethernet Library](#12-bi_rtc_alarm_ethernet_ntpclient_stm32-on-stm32f7-nucleo-144-nucleo_f767zi-with-lan8742a-using-stm32ethernet-library)
  * [13. NINA_NTPClient_Basic on MBED NANO_RP2040_CONNECT with WiFiNINA using WiFiNINA_Generic Library](#13-nina_ntpclient_basic-on-mbed-nano_rp2040_connect-with-wifinina-using-wifinina_generic-library)
  * [14. Ethernet_NTPClient_Advanced on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library](#14-ethernet_ntpclient_advanced-on-raspberry_pi_pico-with-w5x00-using-Ethernet_Generic-library)
  * [15. Ethernet_NTPClient_Advanced on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library](#15-ethernet_ntpclient_advanced-on-mbed-raspberry_pi_pico-with-w5x00-using-Ethernet_Generic-library)
  * [16. NINA_TZ_NTP_WorldClock on MBED NANO_RP2040_CONNECT with WiFiNINA using WiFiNINA_Generic Library](#16-nina_tz_ntp_worldclock-on-mbed-nano_rp2040_connect-with-wifinina-using-wifinina_generic-library)
  * [17. WT32_ETH01_TZ_NTP_WorldClock on ESP32_DEV with ETH_PHY_LAN8720](#17-wt32_eth01_tz_ntp_worldclock-on-esp32_dev-with-eth_phy_lan8720)
  * [18. WT32_ETH01_NTPClient_Advanced on ESP32_DEV with ETH_PHY_LAN8720](#18-wt32_eth01_ntpclient_advanced-on-esp32_dev-with-eth_phy_lan8720)
  * [19. RTL8720DN_TZ_NTP_WorldClock on Rtlduino RTL8720DN](#19-rtl8720dn_tz_ntp_worldclock-on-rtlduino-rtl8720dn)
  * [20. Portenta_H7_NTPClient_Advanced on PORTENTA_H7_M7 with WiFi](#20-Portenta_H7_NTPClient_Advanced-on-PORTENTA_H7_M7-with-WiFi)
  * [21. Portenta_H7_NTPClient_Advanced on PORTENTA_H7_M7 with Ethernet](#21-Portenta_H7_NTPClient_Advanced-on-PORTENTA_H7_M7-with-Ethernet)
  * [22. ESP_WiFi_ETH_NTPClient_Advanced on ESP32_DEV with W5x00 using Ethernet_Generic Library](#22-ESP_WiFi_ETH_NTPClient_Advanced-on-ESP32_DEV-with-W5x00-using-Ethernet_Generic-Library)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Important Change from v3.7.0

Please have a look at [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)

From v3.7.2, you can use the new `setUDP()` function for auto-switching between `WiFi` and `Ethernet` UDP to update NTP time.

Check examples [ESP_WiFi_ETH_NTPClient_Advanced](https://github.com/khoih-prog/NTPClient_Generic/tree/main/examples/ESP/ESP_WiFi_ETH_NTPClient_Advanced) and [WT32_WiFi_ETH01_NTPClient_Advanced](https://github.com/khoih-prog/NTPClient_Generic/tree/main/examples/WT32_ETH01/WT32_WiFi_ETH01_NTPClient_Advanced) for a demo.

---
---

### Why do we need this [NTPClient_Generic library](https://github.com/khoih-prog/NTPClient_Generic)

#### Features

The [**NTPClient_Generic library**](https://github.com/khoih-prog/NTPClient_Generic) is designed to work in conjunction with the [**Arduino Time library**](https://github.com/PaulStoffregen/Time), which must also be installed on your system. This documentation assumes some familiarity with the Time library.

The primary goal of the [**NTPClient_Generic library**](https://github.com/khoih-prog/NTPClient_Generic) is to enable the creation of an NTPClient to connect to NTP time-servers to get time and keep local time in sync. For **ESP8266/ESP32, WT32_ETH01 (ESP32 + LAN8720), nRF52, SAMD21/SAMD51, STM32F/L/H/G/WB/MP1, Teensy, RP2040-based boards (Nano_RP2040_Connect, RASPBERRY_PI_PICO), etc. besides AVR, using ESP WiFi, WiFiNINA, Ethernet W5x00, ENC28J60, LAN8742A, ESP8266/ESP32 AT-command WiFi**. But whether hardware RTC or another time-keeping source is present is not mandatory, since the [**Time library**](https://github.com/PaulStoffregen/Time) library can function as a software RTC without additional hardware (although its accuracy is dependent on the accuracy of the microcontroller's system clock.)

The examples will demonstrate how to get the UTC time from NTP server, then update the DS3231 RTC or local clock to make sure the time is perfectly correct.

In the examples, the interval to get perfect time from the NTP server to update RTC and/or local clock is configurable to ensure the RTC and/or local clock accuracy.

This [**NTPClient_Generic library**](https://github.com/khoih-prog/NTPClient_Generic) is based on and modified from [**Fabrice Weinberg's NTPClient Library**](https://github.com/arduino-libraries/NTPClient) to add functions, features and as well as support to many boards and shields.

---

#### Currently supported Boards

This [**NTPClient_Generic** library](https://github.com/khoih-prog/NTPClient_Generic) currently supports these following boards:

 1. **nRF52 boards**, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**
 
 2. **SAMD21**
  - Arduino SAMD21: ZERO, MKRs, NANO_33_IOT, etc.
  - Adafruit SAMD21 (M0): ItsyBitsy M0, Feather M0, Feather M0 Express, Metro M0 Express, Circuit Playground Express, Trinket M0, PIRkey, Hallowing M0, Crickit M0, etc.
  - Seeeduino:  LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, etc.
  
 3. **SAMD51**
  - Adafruit SAMD51 (M4): Metro M4, Grand Central M4, ItsyBitsy M4, Feather M4 Express, Trellis M4, Metro M4 AirLift Lite, MONSTER M4SK Express, Hallowing M4, etc.
  - Seeeduino: Wio Terminal, Grove UI Wireless
  
 4. **SAM DUE** 
 5. **Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0)**
 6. **STM32F/L/H/G/WB/MP1 boards (with 32+K Flash)**
  - Nucleo-144
  - Nucleo-64
  - Discovery
  - Generic STM32F0, STM32F1, STM32F2, STM32F3, STM32F4, STM32F7 (with 64+K Flash): x8 and up
  - STM32L0, STM32L1, STM32L4
  - STM32G0, STM32G4
  - STM32H7
  - STM32WB
  - STM32MP1
  - LoRa boards
  - 3-D printer boards
  - Generic Flight Controllers
  - Midatronics boards

 7. **ESP32**
 8. **ESP8266**
 9. **AVR Mega1280, 2560, ADK.**
  
10. RP2040-based boards, such as **Nano_RP2040_Connect**, using [**Arduino mbed OS for Nano boards**](https://github.com/arduino/ArduinoCore-mbed).

11. RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).

12. **WT32_ETH01 boards** using ESP32-based boards and LAN8720 Ethernet

13. **RTL8720DN, RTL8722DM, RTL8722CSM, etc. boards**

14. **Portenta_H7** using Murata WiFi or Vision-shield Ethernet

15. RP2040W boards using CYW43439 WiFi, such as **RASPBERRY_PI_PICO_W**, using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).

---

#### Currently supported WiFi shields/modules

1. WiFiNINA using [`WiFiNINA_Generic library`](https://github.com/khoih-prog/WiFiNINA_Generic)
2. WiFi101 using [`WiFi101 library v0.16.1+`](https://github.com/arduino-libraries/WiFi101)
3. U-Blox W101, W102 using [`WiFiNINA_Generic library`](https://github.com/khoih-prog/WiFiNINA_Generic)
4. ESP826-AT command using [`WiFiEspAT library`](https://github.com/jandrassy/WiFiEspAT)
5. ESP8266/ESP32-AT command using [`ESP_AT_Lib library`](https://github.com/khoih-prog/ESP_AT_Lib) and [`ESP8266_AT_WebServer`](ESP8266_AT_WebServer)
6. ESP32 and ESP8266 WiFi
7. **RTL8720DN, RTL8722DM, RTL8722CSM**
8. **Portenta_H7 Murata WiFi**
9. **RASPBERRY_PI_PICO_W CYW43439 WiFi**

#### Currently supported Ethernet shields/modules

1. W5x00 using [`Ethernet_Generic`](https://github.com/khoih-prog/Ethernet_Generic) library
2. W5x00 using [`Ethernet`](https://www.arduino.cc/en/Reference/Ethernet), [`EthernetLarge`](https://github.com/OPEnSLab-OSU/EthernetLarge), [`Ethernet2`](https://github.com/adafruit/Ethernet2) or [`Ethernet3`](https://github.com/sstaub/Ethernet3) library
3. ENC28J60 using [`EthernetENC`](https://github.com/jandrassy/EthernetENC) or [`UIPEthernet`](https://github.com/UIPEthernet/UIPEthernet) library
4. Teensy 4.1 built-in Ethernet using [`NativeEthernet`](https://github.com/vjmuzik/NativeEthernet) library
5. Teensy 4.1 built-in Ethernet using [`QNEthernet`](https://github.com/ssilverman/QNEthernet) library
6. LAN8742A using [`STM32Ethernet`](https://github.com/stm32duino/STM32Ethernet) / [STM32 LwIP](https://github.com/stm32duino/LwIP) libraries.
7. LAN8720A in WT32-ETH01 using [`WebServer_WT32_ETH01`](https://github.com/khoih-prog/WebServer_WT32_ETH01)
8. Portenta_H7 Ethernet using [`Portenta_Ethernet`](https://github.com/arduino/ArduinoCore-mbed/tree/master/libraries/Ethernet) library


---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`ESP32 Core 2.0.5+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. [![Latest release](https://img.shields.io/github/release/espressif/arduino-esp32.svg)](https://github.com/espressif/arduino-esp32/releases/latest/)
 3. [`ESP8266 Core 3.0.2+`](https://github.com/esp8266/Arduino) for ESP8266-based boards. [![Latest release](https://img.shields.io/github/release/esp8266/Arduino.svg)](https://github.com/esp8266/Arduino/releases/latest/). To use ESP8266 core 2.7.1+ for LittleFS. 
 4. [`Arduino AVR core 1.8.5+`](https://github.com/arduino/ArduinoCore-avr) for Arduino (Use Arduino Board Manager) for AVR boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-avr.svg)](https://github.com/arduino/ArduinoCore-avr/releases/latest)
 5. [`Teensy core v1.57+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0) boards.
 6. [`Arduino SAM DUE core v1.6.12+`](https://github.com/arduino/ArduinoCore-sam) for SAM DUE ARM Cortex-M3 boards.
 7. [`Arduino SAMD core 1.8.13+`](https://github.com/arduino/ArduinoCore-samd) for SAMD ARM Cortex-M0+ boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-samd.svg)](https://github.com/arduino/ArduinoCore-samd/releases/latest)
 8. [`Adafruit SAMD core 1.7.10+`](https://github.com/adafruit/ArduinoCore-samd) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.). [![GitHub release](https://img.shields.io/github/release/adafruit/ArduinoCore-samd.svg)](https://github.com/adafruit/ArduinoCore-samd/releases/latest)
 9. [`Seeeduino SAMD core 1.8.3+`](https://github.com/Seeed-Studio/ArduinoCore-samd) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.). [![Latest release](https://img.shields.io/github/release/Seeed-Studio/ArduinoCore-samd.svg)](https://github.com/Seeed-Studio/ArduinoCore-samd/releases/latest/)
10. [`Adafruit nRF52 v1.3.0+`](https://github.com/adafruit/Adafruit_nRF52_Arduino) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc. [![GitHub release](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/latest) 
11. [`Arduino Core for STM32 v2.3.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32F/L/H/G/WB/MP1 boards. [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
12. [`ArduinoCore-mbed mbed_rp2040, mbed_nano, mbed_portenta core 3.4.1+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino (Use Arduino Board Manager) **Portenta_H7, RP2040-based boards, such as Nano_RP2040_Connect, RASPBERRY_PI_PICO**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
13. [`Earle Philhower's arduino-pico core v2.6.1+`](https://github.com/earlephilhower/arduino-pico) for RP2040-based boards such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. [![GitHub release](https://img.shields.io/github/release/earlephilhower/arduino-pico.svg)](https://github.com/earlephilhower/arduino-pico/releases/latest)
14. [`Arduino AmebaD core 3.1.4+`](https://github.com/ambiot/ambd_arduino) for Realtek RTL8720DN, RTL8722DM and RTL8722CSM. [![GitHub release](https://img.shields.io/github/release/ambiot/ambd_arduino.svg)](https://github.com/ambiot/ambd_arduino/releases/latest)

15. [`Time v1.6.1+`](https://github.com/PaulStoffregen/Time). [![GitHub release](https://img.shields.io/github/release/PaulStoffregen/Time.svg)](https://github.com/PaulStoffregen/Time/releases/latest)
16. For built-in LAN8742A Ethernet:
   - [`STM32Ethernet library v1.3.0+`](https://github.com/stm32duino/STM32Ethernet) for built-in LAN8742A Ethernet on (Nucleo-144, Discovery). [![GitHub release](https://img.shields.io/github/release/stm32duino/STM32Ethernet.svg)](https://github.com/stm32duino/STM32Ethernet/releases/latest)
   - [`LwIP library v2.1.2+`](https://github.com/stm32duino/LwIP) for built-in LAN8742A Ethernet on (Nucleo-144, Discovery). [![GitHub release](https://img.shields.io/github/release/stm32duino/LwIP.svg)](https://github.com/stm32duino/LwIP/releases/latest)
17. For W5x00 Ethernet:
   - [`Ethernet_Generic library v2.6.1+`](https://github.com/khoih-prog/Ethernet_Generic) for W5100, W5200 and W5500/WIZ550io/WIZ850io/USR-ES1 with Wiznet W5500 chip.  [![GitHub release](https://img.shields.io/github/release/khoih-prog/Ethernet_Generic.svg)](https://github.com/khoih-prog/Ethernet_Generic/releases/latest)
18. For ENC28J60 Ethernet:
   - [`EthernetENC library v2.0.3+`](https://github.com/jandrassy/EthernetENC) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/jandrassy/EthernetENC.svg)](https://github.com/jandrassy/EthernetENC/releases/latest). **New and Better**
   - [`UIPEthernet library v2.0.12+`](https://github.com/UIPEthernet/UIPEthernet) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/UIPEthernet/UIPEthernet.svg)](https://github.com/UIPEthernet/UIPEthernet/releases/latest)
19. [`WiFiNINA_Generic library v1.8.14-6+`](https://github.com/khoih-prog/WiFiNINA_Generic) to use WiFiNINA modules/shields. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic) if using WiFiNINA for boards such as Nano 33 IoT, nRF52, Teensy, etc.
20. [`WiFiWebServer library v1.9.5+`](https://github.com/khoih-prog/WiFiWebServer) to use WiFi/WiFiNINA modules/shields. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiWebServer.svg?)](https://www.ardu-badge.com/WiFiWebServer)
21. [`EthernetWebServer library v2.2.3+`](https://github.com/khoih-prog/EthernetWebServer) to use Ethernet modules/shields on boards other than STM32F/L/H/G/WB/MP1. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer.svg?)](https://www.ardu-badge.com/EthernetWebServer).
22. [`EthernetWebServer_STM32 library v1.5.0+`](https://github.com/khoih-prog/EthernetWebServer_STM32) to use Ethernet modules/shields on STM32F/L/H/G/WB/MP1 boards. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer_STM32.svg?)](https://www.ardu-badge.com/EthernetWebServer_STM32).
23. [`ESP8266_AT_WebServer library v1.5.4+`](https://github.com/khoih-prog/ESP8266_AT_WebServer) to use ESP8266-AT/ESP32-AT WiFi modules/shields. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP8266_AT_WebServer.svg?)](https://www.ardu-badge.com/ESP8266_AT_WebServer)
24. [`DS323x_Generic library v1.3.1+`](https://github.com/khoih-prog/DS323x_Generic) to use examples using DS323x RTC modules/shields. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/DS323x_Generic.svg?)](https://www.ardu-badge.com/DS323x_Generic)
25. [`Timezone_Generic library v1.10.1+`](https://github.com/khoih-prog/Timezone_Generic) to use examples using Timezone. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/Timezone_Generic.svg?)](https://www.ardu-badge.com/Timezone_Generic)
26. [`STM32RTC library v1.3.2+`](https://github.com/stm32duino/STM32RTC) to use STM32 examples using built-in STM32 RTC. [![GitHub release](https://img.shields.io/github/release/stm32duino/STM32RTC.svg)](https://github.com/stm32duino/STM32RTC/releases/latest).
27. [`WebServer_WT32_ETH01 library v1.5.1+`](https://github.com/khoih-prog/WebServer_WT32_ETH01) to use WT32_ETH01 (ESP32 + LAN8720). To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WebServer_WT32_ETH01.svg?)](https://www.ardu-badge.com/WebServer_WT32_ETH01).
28. [`WiFiWebServer_RTL8720 library v1.1.2+`](https://github.com/khoih-prog/WiFiWebServer_RTL8720) to use Realtek RTL8720DN, etc. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiWebServer_RTL8720.svg?)](https://www.ardu-badge.com/WiFiWebServer_RTL8720).

29. [`Modified WiFi101 Library v0.16.1+`](https://github.com/khoih-prog/WiFi101) to use SAMD MKR1000, etc. boards with WiFi101.
30. [`WiFiEspAT library v1.4.1+`](https://github.com/jandrassy/WiFiEspAT) if using ESP8288/ESP32-AT shields. [![GitHub release](https://img.shields.io/github/release/jandrassy/WiFiEspAT.svg)](https://github.com/jandrassy/WiFiEspAT/releases/latest)
31. [`FlashStorage_SAMD library v1.3.2+`](https://github.com/khoih-prog/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.). [![GitHub release](https://img.shields.io/github/release/khoih-prog/FlashStorage_SAMD.svg)](https://github.com/khoih-prog/FlashStorage_SAMD/releases/latest)
32. [`FlashStorage_STM32F1 library v1.1.0+`](https://github.com/khoih-prog/FlashStorage_STM32F1) for STM32F1/F3 boards. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/FlashStorage_STM32F1.svg?)](https://www.ardu-badge.com/FlashStorage_STM32F1)
33. [`FlashStorage_STM32 library v1.2.0+`](https://github.com/khoih-prog/FlashStorage_STM32) for STM32F/L/H/G/WB/MP1 boards. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/FlashStorage_STM32.svg?)](https://www.ardu-badge.com/FlashStorage_STM32)

---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**NTPClient_Generic**](https://github.com/khoih-prog/NTPClient_Generic), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/NTPClient_Generic.svg?)](https://www.ardu-badge.com/NTPClient_Generic) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**NTPClient_Generic**](https://github.com/khoih-prog/NTPClient_Generic) page.
2. Download the latest release `NTPClient_Generic-main.zip`.
3. Extract the zip file to `NTPClient_Generic-main` directory 
4. Copy whole `NTPClient_Generic-main/src` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**NTPClient_Generic** library](https://registry.platformio.org/libraries/khoih-prog/NTPClient_Generic) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/NTPClient_Generic/installation). Search for **NTPClient_Generic** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 Packages_Patches](Packages_Patches/adafruit/hardware/nrf52/1.3.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0). 

Supposing the Adafruit nRF52 version is 1.3.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.19/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.19. These files must be copied into the directory:

- `./arduino-1.8.19/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

#### 3. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

#### 4. For Arduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD Packages_Patches](Packages_Patches/arduino/hardware/samd/1.8.13) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.13).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.13. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.13/platform.txt`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`
 
#### For core version v1.8.9-

Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

#### 5. For Adafruit SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the whole [Adafruit SAMD Packages_Patches](Packages_Patches/adafruit/hardware/samd/1.7.10) directory into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.7.10). 

Supposing the Adafruit SAMD core version is 1.7.10. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.7.10/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.10/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.10/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the whole [Seeeduino SAMD Packages_Patches](Packages_Patches/Seeeduino/hardware/samd/1.8.3) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3). 

Supposing the Seeeduino SAMD core version is 1.8.3. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 7. For STM32 boards

#### 7.1 For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.3.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.3.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.3.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 7.2 For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/2.3.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.3.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 2.3.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h`

#### 8. For RP2040-based boards using [Earle Philhower arduino-pico core](https://github.com/earlephilhower/arduino-pico)

#### 8.1 To use BOARD_NAME

 **To be able to automatically detect and display BOARD_NAME on RP2040-based boards (RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, etc) boards**, you have to copy the file [RP2040 platform.txt](Packages_Patches/rp2040/hardware/rp2040/1.4.0) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0). 

Supposing the rp2040 core version is 1.4.0. This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/platform.txt`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add -DBOARD_NAME="{build.board}" #136](https://github.com/earlephilhower/arduino-pico/pull/136).

#### 8.2 To avoid compile error relating to microsecondsToClockCycles

Some libraries, such as [Adafruit DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library), require the definition of microsecondsToClockCycles(). **To be able to compile and run on RP2040-based boards**, you have to copy the files in [**RP2040 Arduino.h**](Packages_Patches/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0).

Supposing the rp2040 core version is 1.4.0. This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/cores/rp2040/Arduino.h`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add defs for compatibility #142](https://github.com/earlephilhower/arduino-pico/pull/142).


#### 9. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 3.4.1. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`


#### 10. For RTL8720DN boards using AmebaD core
 
 To avoid compile error relating to PROGMEM, you have to copy the file [Realtek AmebaD core pgmspace.h](Packages_Patches/realtek/hardware/AmebaD/3.1.4/cores/ambd/avr/pgmspace.h) into Realtek AmebaD directory (~/.arduino15/packages/realtek/hardware/AmebaD/3.1.4/cores/arduino/avr/pgmspace.h). 

Supposing the Realtek AmebaD core version is 3.1.4. This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/3.1.4/cores/arduino/avr/pgmspace.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/x.yy.zz/cores/arduino/avr/pgmspace.h`


#### 11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core
 
 To avoid compile error relating to SAMD21/SAMD51, you have to copy the file [ArduinoCore-fab-sam core pgmspace.h](Packages_Patches/Fab_SAM_Arduino/hardware/samd/1.7.0/boards.txt) into `ArduinoCore-fab-sam` samd directory (~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.7.0/boards.txt). 

Supposing the `ArduinoCore-fab-sam` samd core version is 1.7.0. This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.7.0/boards.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/x.yy.zz/boards.txt`


#### 12. For Seeeduino RP2040 boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino RP2040 (XIAO RP2040, Wio RP2040 Mini) boards***, you have to copy the whole [Seeeduino RP2040 Packages_Patches](Packages_Patches/Seeeduino/hardware/rp2040/2.7.2) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2). 

Supposing the Seeeduino SAMD core version is 2.7.2. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/variants/Seeed_XIAO_RP2040/pins_arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/variants/Seeed_XIAO_RP2040/pins_arduino.h`

---
---

### Libraries' Patches

#### 1. For application requiring 2K+ HTML page

If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

#### 2. For Ethernet library

To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

#### 3. For EthernetLarge library

To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)


#### 4. For Ethernet2 library

To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for the [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

#### 5. For Ethernet3 library

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

#### 6. For UIPEthernet library

***To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library***, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
- [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
- [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
- [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

#### 7. For fixing ESP32 compile error

To fix [`ESP32 compile error`](https://github.com/espressif/arduino-esp32), just copy the following file into the [`ESP32`](https://github.com/espressif/arduino-esp32) cores/esp32 directory (e.g. ./arduino-1.8.13/hardware/espressif/cores/esp32) to overwrite the old file:
- [Server.h](LibraryPatches/esp32/cores/esp32/Server.h)

#### 8. For fixing ESP8266 compile error

To fix `ESP8266 compile error` such as

```cpp
error: 'class EthernetClass' has no member named 'init'
Ethernet.init (USE_THIS_SS_PIN);
```

just rename the following file in ./arduino-1.8.13/hardware/esp8266com/esp8266/libraries/Ethernet directory

- From `Ethernet.h` to `Ethernet_ESP8266.h`

---
---


### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can use

```cpp
#include <NTPClient_Generic.hpp>               //https://github.com/khoih-prog/NTPClient_Generic
```

in many files. But be sure to use the following `#include <NTPClient_Generic.h>` **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```cpp
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <NTPClient_Generic.h>                //https://github.com/khoih-prog/NTPClient_Generic
```

Check [multiFileProject](examples/multiFileProject) for a demo how to avoid `multiple-definitions` linker error for multiple-file project

---
---

### HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)

Please have a look at [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to have more detailed description and solution of the issue.

#### 1.  ESP32 has 2 ADCs, named ADC1 and ADC2

#### 2. ESP32 ADCs functions

- ADC1 controls ADC function for pins **GPIO32-GPIO39**
- ADC2 controls ADC function for pins **GPIO0, 2, 4, 12-15, 25-27**

#### 3.. ESP32 WiFi uses ADC2 for WiFi functions

Look in file [**adc_common.c**](https://github.com/espressif/esp-idf/blob/master/components/driver/adc_common.c#L61)

> In ADC2, there're two locks used for different cases:
> 1. lock shared with app and Wi-Fi:
>    ESP32:
>         When Wi-Fi using the ADC2, we assume it will never stop, so app checks the lock and returns immediately if failed.
>    ESP32S2:
>         The controller's control over the ADC is determined by the arbiter. There is no need to control by lock.
> 
> 2. lock shared between tasks:
>    when several tasks sharing the ADC2, we want to guarantee
>    all the requests will be handled.
>    Since conversions are short (about 31us), app returns the lock very soon,
>    we use a spinlock to stand there waiting to do conversions one by one.
> 
> adc2_spinlock should be acquired first, then adc2_wifi_lock or rtc_spinlock.


- In order to use ADC2 for other functions, we have to **acquire complicated firmware locks and very difficult to do**
- So, it's not advisable to use ADC2 with WiFi/BlueTooth (BT/BLE).
- Use ADC1, and pins GPIO32-GPIO39
- If somehow it's a must to use those pins serviced by ADC2 (**GPIO0, 2, 4, 12, 13, 14, 15, 25, 26 and 27**), use the **fix mentioned at the end** of [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to work with ESP32 WiFi/BlueTooth (BT/BLE).

---
---

### Important Notes

1. Code is restructured to provide flexibility to make it easy to support many more **WiFi/Ethernet** modules/shields in the future. Please delete the *.cpp files, replaced by *.hpp files, in the src directory, if *.cpp files still exist after installing new version.

2. For **Adafruit nRF52**, use the SPI's  pin as follows:

  - SS/CS     = 10
  - SPI_MOSI  = MO(SI)
  - SPI_MISO  = MI(SO)
  - SPI_SCK   = SCK

3. For **Adafruit SAMD21/SAMD51**, use the SPI's CS/SS pin as follows:

  - Itsy-Bitsy M0/M4, Feather M0 (Express), Hallowing M0 Express, Zero, Metro M0 => use CS = 16 = pin A2
  - Feather M4 (SAMD51)   => use SS/CS = 9
  - Grand Central M4      => use SS/CS = 53
  - Hallowing M4          => use SS/CS = 10
  - Metro M4 AirLift      => use SS/CS = 36

To know the default CS/SS pins of not listed boards, check the related `variant.h` files in 

`~/.arduino15/packages/adafruit/hardware/samd/x.y.zz/variants/board_name/variant.h`

4. For **Arduino SAM DUE**, use the SPI's  pin as follows:

  - SS/CS     = 10
  - SPI_MOSI  = 75 ( pin 4 @ [ICSP connector](pics/ICSP_connector.jpg) )
  - SPI_MISO  = 74 ( pin 1 @ [ICSP connector](pics/ICSP_connector.jpg) )
  - SPI_SCK   = 76 ( pin 3 @ [ICSP connector](pics/ICSP_connector.jpg) )
  
<p align="center">
    <img src="https://github.com/khoih-prog/NTPClient_Generic/blob/main/pics/ICSP_connector.jpg">
</p>
  
  
---
---

## Examples

### ESP32/ESP8266 Boards

 1. [ESP_NTPClient_Advanced](examples/ESP/ESP_NTPClient_Advanced)
 2. [ESP_NTPClient_Basic](examples/ESP/ESP_NTPClient_Basic)
 3. [ESP_WiFi_ETH_NTPClient_Advanced](examples/ESP/ESP_WiFi_ETH_NTPClient_Advanced) **New**
 
### Generic Boards with Ethernet

 1. [Ethernet_NTPClient_Advanced](examples/Generic/Ethernet/Ethernet_NTPClient_Advanced)
 2. [Ethernet_NTPClient_Basic](examples/Generic/Ethernet/Ethernet_NTPClient_Basic)
 3. [RTC_Ethernet_NTPClient](examples/Generic/Ethernet/RTC_Ethernet_NTPClient)
 4. [TZ_NTP_Clock_Ethernet](examples/Generic/Ethernet/TZ_NTP_Clock_Ethernet) 
 5. [TZ_NTP_WorldClock_Ethernet](examples/Generic/Ethernet/TZ_NTP_WorldClock_Ethernet)

### STM32F/L/H/G/WB/MP1 Boards with Ethernet

 1. [BI_RTC_Alarm_Ethernet_NTPClient_STM32](examples/Generic/Ethernet/BI_RTC_Alarm_Ethernet_NTPClient_STM32) 
 2. [BI_RTC_Ethernet_NTPClient_STM32](examples/Generic/Ethernet/BI_RTC_Ethernet_NTPClient_STM32) 
 3. [Ethernet_NTPClient_Advanced_STM32](examples/Generic/Ethernet/Ethernet_NTPClient_Advanced_STM32) 
 4. [Ethernet_NTPClient_Basic_STM32](examples/Generic/Ethernet/Ethernet_NTPClient_Basic_STM32)
 5. [RTC_Ethernet_NTPClient_STM32](examples/Generic/Ethernet/RTC_Ethernet_NTPClient_STM32)
 6. [TZ_NTP_Clock_STM32_Ethernet](examples/Generic/Ethernet/TZ_NTP_Clock_STM32_Ethernet) 
 7. [TZ_NTP_WorldClock_STM32_Ethernet](examples/Generic/Ethernet/TZ_NTP_WorldClock_STM32_Ethernet)
 
### Generic Boards with WiFiNINA 
 
 1. [NINA_NTPClient_Advanced](examples/Generic/WiFiNINA/NINA_NTPClient_Advanced) 
 2. [NINA_NTPClient_Basic](examples/Generic/WiFiNINA/NINA_NTPClient_Basic)
 3. [NINA_TZ_NTP_Clock](examples/Generic/WiFiNINA/NINA_TZ_NTP_Clock)
 4. [NINA_TZ_NTP_WorldClock](examples/Generic/WiFiNINA/NINA_TZ_NTP_WorldClock)
 
### WT32_ETH01 Boards

 1. [WT32_ETH01_NTPClient_Advanced](examples/WT32_ETH01/WT32_ETH01_NTPClient_Advanced)
 2. [WT32_ETH01_NTPClient_Basic](examples/WT32_ETH01/WT32_ETH01_NTPClient_Basic)
 3. [WT32_ETH01_TZ_NTP_Clock](examples/WT32_ETH01/WT32_ETH01_TZ_NTP_Clock)
 4. [WT32_ETH01_TZ_NTP_WorldClock](examples/WT32_ETH01/WT32_ETH01_TZ_NTP_WorldClock)
 5. [WT32_WiFi_ETH01_NTPClient_Advanced](examples/WT32_ETH01/WT32_WiFi_ETH01_NTPClient_Advanced) **New** 

### RTL8720DN Boards
 
 1. [RTL8720DN_NTPClient_Advanced](examples/RTL8720DN/RTL8720DN_NTPClient_Advanced) 
 2. [RTL8720DN_NTPClient_Basic](examples/RTL8720DN/RTL8720DN_NTPClient_Basic)
 3. [RTL8720DN_TZ_NTP_Clock](examples/RTL8720DN/RTL8720DN_TZ_NTP_Clock)
 4. [RTL8720DN_TZ_NTP_WorldClock](examples/RTL8720DN/RTL8720DN_TZ_NTP_WorldClock)
 
### Portenta_H7 Boards with WiFi

 1. [Portenta_H7_NTPClient_Advanced](examples/Portenta_H7/WiFi/Portenta_H7_NTPClient_Advanced)
 2. [Portenta_H7_NTPClient_Basic](examples/Portenta_H7/WiFi/Portenta_H7_NTPClient_Basic)
 
### Portenta_H7 Boards with Ethernet

 1. [Portenta_H7_NTPClient_Advanced](examples/Portenta_H7/Ethernet/Portenta_H7_NTPClient_Advanced)
 2. [Portenta_H7_NTPClient_Basic](examples/Portenta_H7/Ethernet/Portenta_H7_NTPClient_Basic)

### General

 1. [multiFileProject](examples/multiFileProject) **New**
  
---
---

### Example [RTC_Ethernet_NTPClient](examples/Generic/Ethernet/RTC_Ethernet_NTPClient)

#### 1. File [RTC_Ethernet_NTPClient.ino](examples/Generic/Ethernet/RTC_Ethernet_NTPClient/RTC_Ethernet_NTPClient.ino)

https://github.com/khoih-prog/NTPClient_Generic/blob/bf50ed80564ea39a2475eb2053e48734777d7131/examples/Generic/Ethernet/RTC_Ethernet_NTPClient/RTC_Ethernet_NTPClient.ino#L24-L394


---

#### 2. File [defines.h](examples/Generic/Ethernet/RTC_Ethernet_NTPClient/defines.h)

https://github.com/khoih-prog/NTPClient_Generic/blob/bf50ed80564ea39a2475eb2053e48734777d7131/examples/Generic/Ethernet/RTC_Ethernet_NTPClient/defines.h#L20-L494


---
---

### Debug Terminal Output Samples

#### 1. [**Ethernet_NTPClient_Advanced**](examples/Generic/Ethernet/Ethernet_NTPClient_Advanced) on Adafruit NRF52840_FEATHER_EXPRESS with ENC28J60 using EthernetENC Library

Following is the debug terminal output when running example [**Ethernet_NTPClient_Advanced**](examples/Generic/Ethernet/Ethernet_NTPClient_Advanced) on Adafruit NRF52840_FEATHER_EXPRESS with ENC28J60 using EthernetENC Library

```
Starting Ethernet_NTPClient_Advanced on NRF52840_FEATHER with ENC28J60 using EthernetENC Library
NTPClient_Generic v3.7.5
[EWS] =========================
[EWS] Default SPI pinout:
[EWS] MOSI: 25
[EWS] MISO: 24
[EWS] SCK: 26
[EWS] SS: 5
[EWS] =========================
[EWS] Board : NRF52840_FEATHER , setCsPin: 10
=========================
Currently Used SPI pinout:
MOSI:25
MISO:24
SCK:26
SS:5
=========================
Using mac index = 3
You're connected to the network, IP = 192.168.2.79
Using NTP Server 0.ca.pool.ntp.org
******NOT UPDATED******
UTC : 00:00:01
UTC :  0: 0: 1 Thu  1 Jan 1970
LOC : 02:28:17
LOC :  2:28:17 Sun  7 Feb 2106
UTC EPOCH : 1
LOC EPOCH : 4294952897
UTC : 0:0:1 Thu 1/1/1970 or 1 Jan 1970
UTC : 00:00:01 Thu 1/1/1970 or 1 Jan 1970
LOC : 2:28:17 Sun 7/2/2106 or 7 Feb 2106
LOC : 02:28:17 Sun 7/2/2106 or 7 Feb 2106
********UPDATED********
UTC : 17:51:56
UTC : 17:51:56 Sat  9 Apr 2022
LOC : 13:51:56
LOC : 13:51:56 Sat  9 Apr 2022
UTC EPOCH : 1649526716
LOC EPOCH : 1649512316
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
```

---

#### 2. [**NINA_NTPClient_Advanced**](examples/Generic/WiFiNINA/NINA_NTPClient_Advanced) on Arduino SAMD21 SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library

Following is the debug terminal output when running example [**NINA_NTPClient_Advanced**](examples/Generic/WiFiNINA/NINA_NTPClient_Advanced) on Arduino SAMD21 SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library

```
Starting NINA_NTPClient_Advanced on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library
NTPClient_Generic v3.7.5
Connecting to: HueNet1

NTPClient_Advanced started @ IP address: 192.168.2.98
Using NTP Server 0.ca.pool.ntp.org
******NOT UPDATED******
UTC : 00:00:01
UTC :  0: 0: 1 Thu  1 Jan 1970
LOC : 02:28:17
LOC :  2:28:17 Sun  7 Feb 2106
UTC EPOCH : 1
LOC EPOCH : 4294952897
UTC : 0:0:1 Thu 1/1/1970 or 1 Jan 1970
UTC : 00:00:01 Thu 1/1/1970 or 1 Jan 1970
LOC : 2:28:17 Sun 7/2/2106 or 7 Feb 2106
LOC : 02:28:17 Sun 7/2/2106 or 7 Feb 2106
********UPDATED********
UTC : 17:51:56
UTC : 17:51:56 Sat  9 Apr 2022
LOC : 13:51:56
LOC : 13:51:56 Sat  9 Apr 2022
UTC EPOCH : 1649526716
LOC EPOCH : 1649512316
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
```

---

#### 3. [**TZ_NTP_WorldClock_Ethernet**](examples/Generic/Ethernet/TZ_NTP_WorldClock_Ethernet) on Adafruit NRF52840_FEATHER_EXPRESS with W5500 using Ethernet_Generic Library

Following is the debug terminal output when running example [**TZ_NTP_WorldClock_Ethernet**](examples/Generic/Ethernet/TZ_NTP_WorldClock_Ethernet) on Adafruit NRF52840_FEATHER_EXPRESS with W5500 using Ethernet_Generic Library

```
Start TZ_NTP_WorldClock_Ethernet on NRF52840_FEATHER with W5x00 using Ethernet_Generic Library
NTPClient_Generic v3.7.5
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 25
[EWS] MISO: 24
[EWS] SCK: 26
[EWS] SS: 5
[EWS] =========================
[EWS] Board : NRF52840_FEATHER , setCsPin: 10
=========================
Currently Used SPI pinout:
MOSI:25
MISO:24
SCK:26
SS:5
=========================
Using mac index = 17
You're connected to the network, IP = 192.168.2.80
********UPDATED********
Time updated. Next update in seconds : 3600

04:05:18 Sun 10 Apr 2022 AEST Sydney
21:05:18 Sat 09 Apr 2022 MSK  Moscow
20:05:18 Sat 09 Apr 2022 CEST Paris
19:05:18 Sat 09 Apr 2022 BST  London
18:05:18 Sat 09 Apr 2022 UTC  Universal Coordinated Time
14:05:18 Sat 09 Apr 2022 EDT  New York
13:05:18 Sat 09 Apr 2022 CDT  Chicago
12:05:18 Sat 09 Apr 2022 MDT  Denver
11:05:18 Sat 09 Apr 2022 MST  Phoenix
11:05:18 Sat 09 Apr 2022 PDT  Los Angeles
```

---

#### 4. [**TZ_NTP_WorldClock_STM32_Ethernet**](examples/Generic/Ethernet/TZ_NTP_WorldClock_STM32_Ethernet) on STM32F7 Nucleo-144 NUCLEO_F767ZI with LAN8742A using STM32Ethernet Library

Following is the debug terminal output when running example [**TZ_NTP_WorldClock_STM32_Ethernet**](examples/Generic/Ethernet/TZ_NTP_WorldClock_STM32_Ethernet) on STM32F7 Nucleo-144 NUCLEO_F767ZI with LAN8742A using STM32Ethernet Library

```
Start TZ_NTP_WorldClock_STM32_Ethernet on NUCLEO_F767ZI, using LAN8742A Ethernet & STM32Ethernet Library
EthernetWebServer_STM32 v1.5.0
NTPClient_Generic v3.7.5
You're connected to the network, IP = 192.168.2.96
Retry Time update in seconds : 3
********UPDATED********
Time updated. Next update in seconds : 3600

04:05:18 Sun 10 Apr 2022 AEST Sydney
21:05:18 Sat 09 Apr 2022 MSK  Moscow
20:05:18 Sat 09 Apr 2022 CEST Paris
19:05:18 Sat 09 Apr 2022 BST  London
18:05:18 Sat 09 Apr 2022 UTC  Universal Coordinated Time
14:05:18 Sat 09 Apr 2022 EDT  New York
13:05:18 Sat 09 Apr 2022 CDT  Chicago
12:05:18 Sat 09 Apr 2022 MDT  Denver
11:05:18 Sat 09 Apr 2022 MST  Phoenix
11:05:18 Sat 09 Apr 2022 PDT  Los Angeles
```


---

#### 5. [**RTC_Ethernet_NTPClient**](examples/Generic/Ethernet/RTC_Ethernet_NTPClient) on Adafruit NRF52840_FEATHER_EXPRESS with ENC28J60 using EthernetENC Library

Following is the debug terminal output when running example [**RTC_Ethernet_NTPClient**](examples/Generic/Ethernet/RTC_Ethernet_NTPClient) on Adafruit NRF52840_FEATHER_EXPRESS with ENC28J60 using EthernetENC Library

```
Start RTC_Ethernet_NTPClient on NRF52840_FEATHER with ENC28J60 using EthernetENC Library
NTPClient_Generic v3.7.5
[EWS] =========================
[EWS] Default SPI pinout:
[EWS] MOSI: 25
[EWS] MISO: 24
[EWS] SCK: 26
[EWS] SS: 5
[EWS] =========================
[EWS] Board : NRF52840_FEATHER , setCsPin: 10
=========================
Currently Used SPI pinout:
MOSI:25
MISO:24
SCK:26
SS:5
=========================
Using mac index = 0
You're connected to the network, IP = 192.168.2.94
============================
18:15:32 Sat 09 Apr 2022 UTC
14:15:32 Sat 09 Apr 2022 EDT
********UPDATED********
RTC updated. Next update in seconds : 3600
============================
18:15:41 Sat 09 Apr 2022 UTC
14:15:41 Sat 09 Apr 2022 EDT
============================
18:15:50 Sat 09 Apr 2022 UTC
14:15:50 Sat 09 Apr 2022 EDT
============================
```

---

#### 6. [**RTC_Ethernet_NTPClient_STM32**](examples/Generic/Ethernet/RTC_Ethernet_NTPClient_STM32) on STM32F7 Nucleo-144 NUCLEO_F767ZI with LAN8742A using STM32Ethernet Library

Following is the debug terminal output when running example [**RTC_Ethernet_NTPClient_STM32**](examples/Generic/Ethernet/RTC_Ethernet_NTPClient_STM32) on STM32F7 Nucleo-144 NUCLEO_F767ZI with LAN8742A using STM32Ethernet Library

```
Start RTC_Ethernet_NTPClient_STM32 on NUCLEO_F767ZI, using LAN8742A Ethernet & STM32Ethernet Library
EthernetWebServer_STM32 v1.5.0
NTPClient_Generic v3.7.5
You're connected to the network, IP = 192.168.2.105
Retry RTC update in seconds : 3
********UPDATED********
RTC updated. Next update in seconds : 3600
============================
22:17:23 Wed 27 Apr 2022 UTC
18:17:23 Wed 27 Apr 2022 EDT
============================
22:17:33 Wed 27 Apr 2022 UTC
18:17:33 Wed 27 Apr 2022 EDT
```

---

#### 7. [**ESP_NTPClient_Advanced**](examples/ESP/ESP_NTPClient_Advanced) on ESP8266_NODEMCU_ESP12E

Following is the debug terminal output when running example [**ESP_NTPClient_Advanced**](examples/ESP/ESP_NTPClient_Advanced) on ESP8266_NODEMCU_ESP12E.

```
Starting ESP_NTPClient_Advanced on ESP8266_NODEMCU_ESP12E
NTPClient_Generic v3.7.5
Connecting to: HueNet1
....
ESP_NTPClient_Advanced started @ IP address: 192.168.2.69
Using NTP Server 0.ca.pool.ntp.org
******NOT UPDATED******
UTC : 00:00:01
UTC :  0: 0: 1 Thu  1 Jan 1970
LOC : 02:28:17
LOC :  2:28:17 Sun  7 Feb 2106
UTC EPOCH : 1
LOC EPOCH : 4294952897
UTC : 0:0:1 Thu 1/1/1970 or 1 Jan 1970
UTC : 00:00:01 Thu 1/1/1970 or 1 Jan 1970
LOC : 2:28:17 Sun 7/2/2106 or 7 Feb 2106
LOC : 02:28:17 Sun 7/2/2106 or 7 Feb 2106
********UPDATED********
UTC : 17:51:56
UTC : 17:51:56 Sat  9 Apr 2022
LOC : 13:51:56
LOC : 13:51:56 Sat  9 Apr 2022
UTC EPOCH : 1649526716
LOC EPOCH : 1649512316
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
```

---

#### 8. [**ESP_NTPClient_Advanced**](examples/ESP/ESP_NTPClient_Advanced) on ESP32_DEV

Following is the debug terminal output when running example [**ESP_NTPClient_Advanced**](examples/ESP/ESP_NTPClient_Advanced) on ESP32_DEV.

```
Starting ESP_NTPClient_Advanced on ESP32_DEV
NTPClient_Generic v3.7.5
Connecting to: HueNet1
....
ESP_NTPClient_Advanced started @ IP address: 192.168.2.101
Using NTP Server 0.ca.pool.ntp.org
******NOT UPDATED******
UTC : 00:00:01
UTC :  0: 0: 1 Thu  1 Jan 1970
LOC : 02:28:17
LOC :  2:28:17 Sun  7 Feb 2106
UTC EPOCH : 1
LOC EPOCH : 4294952897
UTC : 0:0:1 Thu 1/1/1970 or 1 Jan 1970
UTC : 00:00:01 Thu 1/1/1970 or 1 Jan 1970
LOC : 2:28:17 Sun 7/2/2106 or 7 Feb 2106
LOC : 02:28:17 Sun 7/2/2106 or 7 Feb 2106
********UPDATED********
UTC : 17:51:56
UTC : 17:51:56 Sat  9 Apr 2022
LOC : 13:51:56
LOC : 13:51:56 Sat  9 Apr 2022
UTC EPOCH : 1649526716
LOC EPOCH : 1649512316
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
```

---

#### 9. [**Ethernet_NTPClient_Advanced**](examples/Generic/Ethernet/Ethernet_NTPClient_Advanced) on SAM DUE with W5100 using Ethernet_Generic Library

Following is the debug terminal output when running example [**Ethernet_NTPClient_Advanced**](examples/Generic/Ethernet/Ethernet_NTPClient_Advanced) on SAM DUE with W5100 using Ethernet_Generic Library

```
Starting Ethernet_NTPClient_Advanced on SAM DUE with W5x00 using Ethernet_Generic Library
NTPClient_Generic v3.7.5
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 75
[EWS] MISO: 74
[EWS] SCK: 76
[EWS] SS: 10
[EWS] =========================
[EWS] Board : SAM DUE , setCsPin: 10
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 10
W5100::init: W5100, SSIZE =4096
=========================
Currently Used SPI pinout:
MOSI:75
MISO:74
SCK:76
SS:10
=========================
Using mac index = 6
You're connected to the network, IP = 192.168.2.71
Using NTP Server 0.ca.pool.ntp.org
******NOT UPDATED******
UTC : 00:00:01
UTC :  0: 0: 1 Thu  1 Jan 1970
LOC : 02:28:17
LOC :  2:28:17 Sun  7 Feb 2106
UTC EPOCH : 1
LOC EPOCH : 4294952897
UTC : 0:0:1 Thu 1/1/1970 or 1 Jan 1970
UTC : 00:00:01 Thu 1/1/1970 or 1 Jan 1970
LOC : 2:28:17 Sun 7/2/2106 or 7 Feb 2106
LOC : 02:28:17 Sun 7/2/2106 or 7 Feb 2106
********UPDATED********
UTC : 17:51:56
UTC : 17:51:56 Sat  9 Apr 2022
LOC : 13:51:56
LOC : 13:51:56 Sat  9 Apr 2022
UTC EPOCH : 1649526716
LOC EPOCH : 1649512316
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
```

---

#### 10. [**BI_RTC_Ethernet_NTPClient_STM32**](examples/Generic/Ethernet/BI_RTC_Ethernet_NTPClient_STM32) on STM32F7 Nucleo-144 NUCLEO_F767ZI with LAN8742A using STM32Ethernet Library

Following is the debug terminal output when running example [**BI_RTC_Ethernet_NTPClient_STM32**](examples/Generic/Ethernet/BI_RTC_Ethernet_NTPClient_STM32) on STM32F7 Nucleo-144 NUCLEO_F767ZI with LAN8742A using STM32Ethernet Library to demonstrate the usage of STM32 built-in RTC

```
Start BI_RTC_Ethernet_NTPClient_STM32 on NUCLEO_F767ZI, using LAN8742A Ethernet & STM32Ethernet Library
EthernetWebServer_STM32 v1.5.0
NTPClient_Generic v3.7.5
You're connected to the network, IP = 192.168.2.96
Retry RTC update in seconds : 3

Updating Time for STM32 RTC
********UPDATED********
RTC updated. Next update in seconds : 3600
============================
18:15:41 Sat 09 Apr 2022 UTC
14:15:41 Sat 09 Apr 2022 EDT
============================
18:15:50 Sat 09 Apr 2022 UTC
14:15:50 Sat 09 Apr 2022 EDT
```

---

#### 11. [**BI_RTC_Ethernet_NTPClient_STM32**](examples/Generic/Ethernet/BI_RTC_Ethernet_NTPClient_STM32) on STM32F7 Nucleo-144 NUCLEO_F767ZI with ENC28J60 using EthernetENC Library

Following is the debug terminal output when running example [**BI_RTC_Ethernet_NTPClient_STM32**](examples/Generic/Ethernet/BI_RTC_Ethernet_NTPClient_STM32) on STM32F7 Nucleo-144 NUCLEO_F767ZI with ENC28J60 using EthernetENC Library to demonstrate the usage of STM32 built-in RTC

```
Start BI_RTC_Ethernet_NTPClient_STM32 on NUCLEO_F767ZI, using ENC28J60 & EthernetENC Library
NTPClient_Generic v3.7.5
[EWS] Board : NUCLEO_F767ZI , setCsPin: 10
[EWS] Default SPI pinout:
[EWS] MOSI: 11
[EWS] MISO: 12
[EWS] SCK: 13
[EWS] SS: 10
[EWS] =========================
BYou're connected to the network, IP = 192.168.2.97

Updating Time for STM32 RTC
********UPDATED********
RTC updated. Next update in seconds : 3600
============================
22:18:43 Wed 27 Apr 2022 UTC
18:18:43 Wed 27 Apr 2022 EDT
============================
22:18:53 Wed 27 Apr 2022 UTC
18:18:53 Wed 27 Apr 2022 EDT
```

---

#### 12. [**BI_RTC_Alarm_Ethernet_NTPClient_STM32**](examples/Generic/Ethernet/BI_RTC_Alarm_Ethernet_NTPClient_STM32) on STM32F7 Nucleo-144 NUCLEO_F767ZI with LAN8742A using STM32Ethernet Library

Following is the debug terminal output when running example [**BI_RTC_Alarm_Ethernet_NTPClient_STM32**](examples/Generic/Ethernet/BI_RTC_Alarm_Ethernet_NTPClient_STM32) on STM32F7 Nucleo-144 NUCLEO_F767ZI with LAN8742A using STM32Ethernet Library to demonstrate the usage of STM32 built-in RTC Alarm function

```
Start BI_RTC_Alarm_Ethernet_NTPClient_STM32 on NUCLEO_F767ZI with LAN8742A Ethernet & STM32Ethernet Library
EthernetWebServer_STM32 v1.5.0
NTPClient_Generic v3.7.5
You're connected to the network, IP = 192.168.2.88
Retry RTC update in seconds : 3

Updating Time for STM32 RTC
********UPDATED********
=======RTC ALARM SET========
18:13:52 Sat 09 Apr 2022 UTC
14:13:52 Sat 09 Apr 2022 EDT
============================
RTC updated. Next update in seconds : 3600
============================
18:13:28 Sat 09 Apr 2022 UTC
14:13:28 Sat 09 Apr 2022 EDT
============================
18:13:37 Sat 09 Apr 2022 UTC
14:13:37 Sat 09 Apr 2022 EDT
============================
18:13:47 Sat 09 Apr 2022 UTC
14:13:47 Sat 09 Apr 2022 EDT
*****RTC ALARM ACTIVATED*****
*****RTC ALARM ACTIVATED*****
============================
18:13:56 Sat 09 Apr 2022 UTC
14:13:56 Sat 09 Apr 2022 EDT
============================
18:14:05 Sat 09 Apr 2022 UTC
14:14:05 Sat 09 Apr 2022 EDT
```

---

#### 13. [**NINA_NTPClient_Basic**](examples/Generic/WiFiNINA/NINA_NTPClient_Basic) on MBED NANO_RP2040_CONNECT with WiFiNINA using WiFiNINA_Generic Library

Following is the debug terminal output when running example [**NINA_NTPClient_Basic**](examples/Generic/WiFiNINA/NINA_NTPClient_Basic) on MBED NANO_RP2040_CONNECT with WiFiNINA using WiFiNINA_Generic Library

```
Starting NINA_NTPClient_Basic on MBED NANO_RP2040_CONNECT with WiFiNINA using WiFiNINA_Generic Library
NTPClient_Generic v3.7.5
Connecting to: HueNet1

NINA_NTPClient_Basic started @ IP address: 192.168.2.153
Using NTP Server 0.ca.pool.ntp.org
******NOT UPDATED******
UTC : 00:00:01
UTC :  0: 0: 1 Thu  1 Jan 1970
LOC : 02:28:17
LOC :  2:28:17 Sun  7 Feb 2106
UTC EPOCH : 1
LOC EPOCH : 4294952897
UTC : 0:0:1 Thu 1/1/1970 or 1 Jan 1970
UTC : 00:00:01 Thu 1/1/1970 or 1 Jan 1970
LOC : 2:28:17 Sun 7/2/2106 or 7 Feb 2106
LOC : 02:28:17 Sun 7/2/2106 or 7 Feb 2106
********UPDATED********
UTC : 17:51:56
UTC : 17:51:56 Sat  9 Apr 2022
LOC : 13:51:56
LOC : 13:51:56 Sat  9 Apr 2022
UTC EPOCH : 1649526716
LOC EPOCH : 1649512316
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
```

---

#### 14. [**Ethernet_NTPClient_Advanced**](examples/Generic/Ethernet/Ethernet_NTPClient_Advanced) on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

Following is the debug terminal output when running example [**Ethernet_NTPClient_Advanced**](examples/Generic/Ethernet/Ethernet_NTPClient_Advanced) on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

```
Starting Ethernet_NTPClient_Advanced on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
NTPClient_Generic v3.7.5
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 19
[EWS] MISO: 16
[EWS] SCK: 18
[EWS] SS: 17
[EWS] =========================
[EWS] RPIPICO setCsPin: 17
=========================
Currently Used SPI pinout:
MOSI:19
MISO:16
SCK:18
SS:17
========
=========================
Using mac index = 10
You're connected to the network, IP = 192.168.2.94
Using NTP Server 0.ca.pool.ntp.org
******NOT UPDATED******
UTC : 00:00:01
UTC :  0: 0: 1 Thu  1 Jan 1970
LOC : 02:28:17
LOC :  2:28:17 Sun  7 Feb 2106
UTC EPOCH : 1
LOC EPOCH : 4294952897
UTC : 0:0:1 Thu 1/1/1970 or 1 Jan 1970
UTC : 00:00:01 Thu 1/1/1970 or 1 Jan 1970
LOC : 2:28:17 Sun 7/2/2106 or 7 Feb 2106
LOC : 02:28:17 Sun 7/2/2106 or 7 Feb 2106
********UPDATED********
UTC : 17:51:56
UTC : 17:51:56 Sat  9 Apr 2022
LOC : 13:51:56
LOC : 13:51:56 Sat  9 Apr 2022
UTC EPOCH : 1649526716
LOC EPOCH : 1649512316
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
```

---

#### 15. [**Ethernet_NTPClient_Advanced**](examples/Generic/Ethernet/Ethernet_NTPClient_Advanced) on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

Following is the debug terminal output when running example [**Ethernet_NTPClient_Advanced**](examples/Generic/Ethernet/Ethernet_NTPClient_Advanced) on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

```
Starting Ethernet_NTPClient_Advanced on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
NTPClient_Generic v3.7.5
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 19
[EWS] MISO: 16
[EWS] SCK: 18
[EWS] SS: 17
[EWS] =========================
[EWS] RPIPICO setCsPin: 17
=========================
Currently Used SPI pinout:
MOSI:19
MISO:16
SCK:18
SS:17
=========================
Using mac index = 5
You're connected to the network, IP = 192.168.2.123
Using NTP Server 0.ca.pool.ntp.org
******NOT UPDATED******
UTC : 00:00:01
UTC :  0: 0: 1 Thu  1 Jan 1970
LOC : 02:28:17
LOC :  2:28:17 Sun  7 Feb 2106
UTC EPOCH : 1
LOC EPOCH : 4294952897
UTC : 0:0:1 Thu 1/1/1970 or 1 Jan 1970
UTC : 00:00:01 Thu 1/1/1970 or 1 Jan 1970
LOC : 2:28:17 Sun 7/2/2106 or 7 Feb 2106
LOC : 02:28:17 Sun 7/2/2106 or 7 Feb 2106
********UPDATED********
UTC : 17:51:56
UTC : 17:51:56 Sat  9 Apr 2022
LOC : 13:51:56
LOC : 13:51:56 Sat  9 Apr 2022
UTC EPOCH : 1649526716
LOC EPOCH : 1649512316
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
```

---

#### 16. [**NINA_TZ_NTP_WorldClock**](examples/Generic/WiFiNINA/NINA_TZ_NTP_WorldClock) on MBED NANO_RP2040_CONNECT with WiFiNINA using WiFiNINA_Generic Library

Following is the debug terminal output when running example [**NINA_TZ_NTP_WorldClock**](examples/Generic/WiFiNINA/NINA_TZ_NTP_WorldClock) on MBED NANO_RP2040_CONNECT with WiFiNINA using WiFiNINA_Generic Library

```
Starting NINA_TZ_NTP_WorldClock on MBED NANO_RP2040_CONNECT with WiFiNINA using WiFiNINA_Generic Library
NTPClient_Generic v3.7.5
Connecting to WPA SSID: HueNet1
You're connected to the network, IP = 192.168.2.153
********UPDATED********
Time updated. Next update in seconds : 3600

04:05:18 Sun 10 Apr 2022 AEST Sydney
21:05:18 Sat 09 Apr 2022 MSK  Moscow
20:05:18 Sat 09 Apr 2022 CEST Paris
19:05:18 Sat 09 Apr 2022 BST  London
18:05:18 Sat 09 Apr 2022 UTC  Universal Coordinated Time
14:05:18 Sat 09 Apr 2022 EDT  New York
13:05:18 Sat 09 Apr 2022 CDT  Chicago
12:05:18 Sat 09 Apr 2022 MDT  Denver
11:05:18 Sat 09 Apr 2022 MST  Phoenix
11:05:18 Sat 09 Apr 2022 PDT  Los Angeles
```

---

#### 17. [**WT32_ETH01_TZ_NTP_WorldClock**](examples/WT32_ETH01/WT32_ETH01_TZ_NTP_WorldClock) on ESP32_DEV with ETH_PHY_LAN8720

Following is the debug terminal output when running example [**WT32_ETH01_TZ_NTP_WorldClock**](examples/WT32_ETH01/WT32_ETH01_TZ_NTP_WorldClock) on ESP32_DEV with ETH_PHY_LAN8720

```
Starting WT32_ETH01_TZ_NTP_WorldClock on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.5.1
NTPClient_Generic v3.7.5
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232
FULL_DUPLEX, 100Mbps
WT32_ETH01_TZ_NTP_WorldClock started @ IP address: 192.168.2.232
********UPDATED********
Time updated. Next update in seconds : 3600

04:05:18 Sun 10 Apr 2022 AEST Sydney
21:05:18 Sat 09 Apr 2022 MSK  Moscow
20:05:18 Sat 09 Apr 2022 CEST Paris
19:05:18 Sat 09 Apr 2022 BST  London
18:05:18 Sat 09 Apr 2022 UTC  Universal Coordinated Time
14:05:18 Sat 09 Apr 2022 EDT  New York
13:05:18 Sat 09 Apr 2022 CDT  Chicago
12:05:18 Sat 09 Apr 2022 MDT  Denver
11:05:18 Sat 09 Apr 2022 MST  Phoenix
11:05:18 Sat 09 Apr 2022 PDT  Los Angeles
```

---

#### 18. [**WT32_ETH01_NTPClient_Advanced**](examples/WT32_ETH01/WT32_ETH01_NTPClient_Advanced) on ESP32_DEV with ETH_PHY_LAN8720

Following is the debug terminal output when running example [**WT32_ETH01_NTPClient_Advanced**](examples/WT32_ETH01/WT32_ETH01_NTPClient_Advanced) on ESP32_DEV with ETH_PHY_LAN8720

```
Starting WT32_ETH01_NTPClient_Advanced on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.5.1
NTPClient_Generic v3.7.5
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232
FULL_DUPLEX, 100Mbps
WT32_ETH01_NTPClient_Advanced started @ IP address: 192.168.2.232
Using NTP Server 0.ca.pool.ntp.org
******NOT UPDATED******
UTC : 00:00:01
UTC :  0: 0: 1 Thu  1 Jan 1970
LOC : 02:28:17
LOC :  2:28:17 Sun  7 Feb 2106
UTC EPOCH : 1
LOC EPOCH : 4294952897
UTC : 0:0:1 Thu 1/1/1970 or 1 Jan 1970
UTC : 00:00:01 Thu 1/1/1970 or 1 Jan 1970
LOC : 2:28:17 Sun 7/2/2106 or 7 Feb 2106
LOC : 02:28:17 Sun 7/2/2106 or 7 Feb 2106
********UPDATED********
UTC : 17:51:56
UTC : 17:51:56 Sat  9 Apr 2022
LOC : 13:51:56
LOC : 13:51:56 Sat  9 Apr 2022
UTC EPOCH : 1649526716
LOC EPOCH : 1649512316
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
```


---

#### 19. [**RTL8720DN_TZ_NTP_WorldClock**](examples/RTL8720DN/RTL8720DN_TZ_NTP_WorldClock) on Rtlduino RTL8720DN

Following is the debug terminal output when running example [**RTL8720DN_TZ_NTP_WorldClock**](examples/RTL8720DN/RTL8720DN_TZ_NTP_WorldClock) on Rtlduino RTL8720DN

```
Starting RTL8720DN_TZ_NTP_WorldClock on Rtlduino RTL8720DN
WiFiWebServer_RTL8720 v1.1.1
NTPClient_Generic v3.7.5
Current Firmware Version = 1.0.0
Attempting to connect to SSID: HueNet_5G
TZ_NTP_Clock_RTL8720DN started @ IP address: 192.168.2.111
Retry Time update in seconds : 3
********UPDATED********
Time updated. Next update in seconds : 3600

04:05:18 Sun 10 Apr 2022 AEST Sydney
21:05:18 Sat 09 Apr 2022 MSK  Moscow
20:05:18 Sat 09 Apr 2022 CEST Paris
19:05:18 Sat 09 Apr 2022 BST  London
18:05:18 Sat 09 Apr 2022 UTC  Universal Coordinated Time
14:05:18 Sat 09 Apr 2022 EDT  New York
13:05:18 Sat 09 Apr 2022 CDT  Chicago
12:05:18 Sat 09 Apr 2022 MDT  Denver
11:05:18 Sat 09 Apr 2022 MST  Phoenix
11:05:18 Sat 09 Apr 2022 PDT  Los Angeles
```

---

#### 20. [**Portenta_H7_NTPClient_Advanced**](examples/Portenta_H7/WiFi/Portenta_H7_NTPClient_Advanced) on PORTENTA_H7_M7 with WiFi

Following is the debug terminal output when running example [**Portenta_H7_NTPClient_Advanced**](examples/Portenta_H7/WiFi/Portenta_H7_NTPClient_Advanced) on on PORTENTA_H7_M7 with Murata WiFi

```
Starting Portenta_H7_NTPClient_Advanced on PORTENTA_H7_M7
NTPClient_Generic v3.7.5
Connecting to: HueNet1
Portenta_H7_NTPClient_Advanced started @ IP address: 192.168.2.104
Using NTP Server 0.ca.pool.ntp.org
******NOT UPDATED******
UTC : 00:00:01
UTC :  0: 0: 1 Thu  1 Jan 1970
LOC : 02:28:17
LOC :  2:28:17 Sun  7 Feb 2106
UTC EPOCH : 1
LOC EPOCH : 4294952897
UTC : 0:0:1 Thu 1/1/1970 or 1 Jan 1970
UTC : 00:00:01 Thu 1/1/1970 or 1 Jan 1970
LOC : 2:28:17 Sun 7/2/2106 or 7 Feb 2106
LOC : 02:28:17 Sun 7/2/2106 or 7 Feb 2106
********UPDATED********
UTC : 17:51:56
UTC : 17:51:56 Sat  9 Apr 2022
LOC : 13:51:56
LOC : 13:51:56 Sat  9 Apr 2022
UTC EPOCH : 1649526716
LOC EPOCH : 1649512316
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
```

---

#### 21. [**Portenta_H7_NTPClient_Advanced**](examples/Portenta_H7/Ethernet/Portenta_H7_NTPClient_Advanced) on PORTENTA_H7_M7 with Ethernet

Following is the debug terminal output when running example [**Portenta_H7_NTPClient_Advanced**](examples/Portenta_H7/Ethernet/Portenta_H7_NTPClient_Advanced) on on PORTENTA_H7_M7 with Vision-shield Ethernet

```
Starting Portenta_H7_NTPClient_Advanced using Ethernet on PORTENTA_H7_M7
NTPClient_Generic v3.7.5
Portenta_H7_NTPClient_Basic started @ IP address: 192.168.2.111
Using NTP Server 0.ca.pool.ntp.org
******NOT UPDATED******
UTC : 00:00:01
UTC :  0: 0: 1 Thu  1 Jan 1970
LOC : 02:28:17
LOC :  2:28:17 Sun  7 Feb 2106
UTC EPOCH : 1
LOC EPOCH : 4294952897
UTC : 0:0:1 Thu 1/1/1970 or 1 Jan 1970
UTC : 00:00:01 Thu 1/1/1970 or 1 Jan 1970
LOC : 2:28:17 Sun 7/2/2106 or 7 Feb 2106
LOC : 02:28:17 Sun 7/2/2106 or 7 Feb 2106
********UPDATED********
UTC : 17:51:56
UTC : 17:51:56 Sat  9 Apr 2022
LOC : 13:51:56
LOC : 13:51:56 Sat  9 Apr 2022
UTC EPOCH : 1649526716
LOC EPOCH : 1649512316
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
UTC : 17:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
LOC : 13:51:56 Sat 9/4/2022 or 9 Apr 2022
```

---

#### 22. [**ESP_WiFi_ETH_NTPClient_Advanced**](examples/ESP/ESP_WiFi_ETH_NTPClient_Advanced) on ESP32_DEV with W5x00 using Ethernet_Generic Library

Following is the debug terminal output when running example [**ESP_WiFi_ETH_NTPClient_Advanced**](examples/ESP/ESP_WiFi_ETH_NTPClient_Advanced) on ESP32_DEV with W5x00 using Ethernet_Generic Library to demonstrate how to to use the new `setUDP()` function for auto-switching between `WiFi` and `Ethernet` UDP to update NTP time.


```
Starting ESP_WiFi_ETH_NTPClient_Advanced on ESP32_DEV with W5x00 using Ethernet_Generic Library
EthernetWebServer v2.2.3
NTPClient_Generic v3.7.5
Connecting to: HueNet1
...................
WiFi failed to connect      <=====  Start without WiFi to use Ethernet UDP
.[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 23
[EWS] MISO: 19
[EWS] SCK: 18
[EWS] SS: 5
[EWS] =========================
[EWS] ESP32 setCsPin: 22
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 22, new ss_pin = 10, W5100Class::ss_pin = 22
W5100::init: W5500, SSIZE =8192
=========================
Currently Used SPI pinout:
MOSI:23
MISO:19
SCK:18
CS/SS:22
=========================
Using mac index = 11
Connected! IP address: 192.168.2.125
Using NTP Server 0.ca.pool.ntp.org
****WIFI Status****
WiFi Failed
******NOT UPDATED******
UTC : 00:00:13
UTC :  0: 0:13 Thu  1 Jan 1970
LOC : 02:28:29
LOC :  2:28:29 Sun  7 Feb 2106
UTC EPOCH : 13
LOC EPOCH : 4294952909
UTC : 0:0:13 Thu 1/1/1970 or 1 Jan 1970
UTC : 00:00:13 Thu 1/1/1970 or 1 Jan 1970
LOC : 2:28:29 Sun 7/2/2106 or 7 Feb 2106
LOC : 02:28:29 Sun 7/2/2106 or 7 Feb 2106
****WIFI Status****
WiFi Failed
********UPDATED********       <=====  Updated using Ethernet UDP
UTC : 04:14:00
UTC :  4:14: 0 Thu 24 Feb 2022
LOC : 00:14:00
LOC :  0:14: 0 Thu 24 Feb 2022
UTC EPOCH : 1645676040
LOC EPOCH : 1645661640
UTC : 4:14:0 Thu 24/2/2022 or 24 Feb 2022
UTC : 04:14:00 Thu 24/2/2022 or 24 Feb 2022
LOC : 0:14:0 Thu 24/2/2022 or 24 Feb 2022
LOC : 00:14:00 Thu 24/2/2022 or 24 Feb 2022
****WIFI Status****
WiFi Failed
****WIFI Status****
WiFi Failed
****WIFI Status****
WiFi Failed
****WIFI Status****
WiFi Failed
****WIFI Status****
WiFi Failed
********UPDATED********
UTC : 04:15:00
UTC :  4:15: 0 Thu 24 Feb 2022
LOC : 00:15:00
LOC :  0:15: 0 Thu 24 Feb 2022
UTC EPOCH : 1645676100
LOC EPOCH : 1645661700
UTC : 4:15:0 Thu 24/2/2022 or 24 Feb 2022
UTC : 04:15:00 Thu 24/2/2022 or 24 Feb 2022
LOC : 0:15:0 Thu 24/2/2022 or 24 Feb 2022
LOC : 00:15:00 Thu 24/2/2022 or 24 Feb 2022
****WIFI Status****
WiFi OK
NTP => WiFi          <=====  Switch back to use WiFi UDP as WiFi is OK
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
********UPDATED********    <=====  Updated using WiFi UDP
UTC : 04:16:00
UTC :  4:16: 0 Thu 24 Feb 2022
LOC : 00:16:00
LOC :  0:16: 0 Thu 24 Feb 2022
UTC EPOCH : 1645676160
LOC EPOCH : 1645661760
UTC : 4:16:0 Thu 24/2/2022 or 24 Feb 2022
UTC : 04:16:00 Thu 24/2/2022 or 24 Feb 2022
LOC : 0:16:0 Thu 24/2/2022 or 24 Feb 2022
LOC : 00:16:00 Thu 24/2/2022 or 24 Feb 2022
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
********UPDATED********
UTC : 04:16:10
UTC :  4:16:10 Thu 24 Feb 2022
LOC : 00:16:10
LOC :  0:16:10 Thu 24 Feb 2022
UTC EPOCH : 1645676170
LOC EPOCH : 1645661770
UTC : 4:16:10 Thu 24/2/2022 or 24 Feb 2022
UTC : 04:16:10 Thu 24/2/2022 or 24 Feb 2022
LOC : 0:16:10 Thu 24/2/2022 or 24 Feb 2022
LOC : 00:16:10 Thu 24/2/2022 or 24 Feb 2022
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
********UPDATED********
UTC : 04:17:10
UTC :  4:17:10 Thu 24 Feb 2022
LOC : 00:17:10
LOC :  0:17:10 Thu 24 Feb 2022
UTC EPOCH : 1645676230
LOC EPOCH : 1645661830
UTC : 4:17:10 Thu 24/2/2022 or 24 Feb 2022
UTC : 04:17:10 Thu 24/2/2022 or 24 Feb 2022
LOC : 0:17:10 Thu 24/2/2022 or 24 Feb 2022
LOC : 00:17:10 Thu 24/2/2022 or 24 Feb 2022
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
********UPDATED********
UTC : 04:18:10
UTC :  4:18:10 Thu 24 Feb 2022
LOC : 00:18:10
LOC :  0:18:10 Thu 24 Feb 2022
UTC EPOCH : 1645676290
LOC EPOCH : 1645661890
UTC : 4:18:10 Thu 24/2/2022 or 24 Feb 2022
UTC : 04:18:10 Thu 24/2/2022 or 24 Feb 2022
LOC : 0:18:10 Thu 24/2/2022 or 24 Feb 2022
LOC : 00:18:10 Thu 24/2/2022 or 24 Feb 2022
****WIFI Status****
WiFi OK
****WIFI Status****
WiFi OK
```


---
---

### Debug

Debug is enabled by default on Serial. To disable, add at the beginning of sketch

```cpp
/* Comment this out to disable prints and save space */
#define NTP_DBG_PORT                Serial

// Debug Level from 0 to 4
#define _NTP_LOGLEVEL_              0
```

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, dependent libraries or this library version.

Sometimes, the library will only work if you update the core to the newer or older version because some function compatibility.

---
---


### Issues

Submit issues to: [NTPClient_Generic issues](https://github.com/khoih-prog/NTPClient_Generic/issues)

---
---

### TO DO

1. Bug Searching and Killing
2. Add more examples

---

### DONE

 1. Add support to **Arduino SAMD21 (ZERO, MKR, NANO_33_IOT, etc.) and FlashStorage**
 2. Add support to **Adafruit SAMD21 (Itsy-Bitsy M0, Metro M0, Feather M0 Express, etc.) and FlashStorage**.
 3. Add support to **Adafruit SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.) and FlashStorage**.
 4. Add support to **Adafruit nRF52 ( Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc. annd LittleFS**.
 5. Add support to **SAM DUE**.
 6. Add support to Ethernet W5x00, using either [`Ethernet`](https://www.arduino.cc/en/Reference/Ethernet), [`Ethernet2`](https://github.com/adafruit/Ethernet2), or [`EthernetLarge`](https://github.com/OPEnSLab-OSU/EthernetLarge) library
 7. Add support to Ethernet ENC28J60, using [`UIPEthernet`](https://github.com/UIPEthernet/UIPEthernet) library
 8. Add support to Seeeduino SAMD21/SAMD51: LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, Wio Terminal, Grove UI Wireless and FlashStorage.
 9. Add support to [`EthernetENC`](https://github.com/jandrassy/EthernetENC)
10. Add support to **AVR Mega, UNO, Nano**.
11. Add support to **Arduino Nano_RP2040_Connect** using [**Arduino mbed OS for Nano boards**](https://github.com/arduino/ArduinoCore-mbed).
12. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).
13. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed)
14. Add Version String and Table-of-Contents 
15. Add support to **WT32_ETH01 boards** using ESP32-based boards and LAN8720 Ethernet
16. Add support to **RTL8720DN, RTL8722DM, RTL8722CSM, etc. boards**
17. Add support to **Add support to Potenta_H7 using Murata WiFi of Vision-Shield Ethernet**
18. Fix `multiple-definitions` linker error.
19. Fix getUTCEpochMillis() bug
20. Add setUDP() function to enable auto-switching between `WiFi` and `Ethernet` UDP instances.
21. Add new examples [ESP_WiFi_ETH_NTPClient_Advanced](https://github.com/khoih-prog/NTPClient_Generic/tree/main/examples/ESP/ESP_WiFi_ETH_NTPClient_Advanced) and [WT32_WiFi_ETH01_NTPClient_Advanced](https://github.com/khoih-prog/NTPClient_Generic/tree/main/examples/WT32_ETH01/WT32_WiFi_ETH01_NTPClient_Advanced) to use the new setUDP() function for auto-switching between `WiFi` and `Ethernet` UDP to update NTP time.
22. Use [Ethernet_Generic](https://github.com/khoih-prog/Ethernet_Generic) library as default for W5x00 Ethernet.
23. Support **SPI2 for ESP32**
24. Add support to **SPI1 for RP2040** using [arduino-pico core](https://github.com/earlephilhower/arduino-pico)
25. Add example [multiFileProject](examples/multiFileProject) to demo how to avoid `multiple-definitions` linker error for multiple-file project
26. Sync with [NTPClient releases v3.2.1](https://github.com/arduino-libraries/NTPClient/releases/tag/3.2.1)
27. Fix bug causing time jumping back or forth when network has problem


---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

1. Based on and modified from the [**Fabrice Weinberg's NTPClient Library**](https://github.com/arduino-libraries/NTPClient).
2. Thanks to good work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing.
3. Thanks to [bmcdonnell](https://github.com/bmcdonnell) to make PR in [Add packet validity checks #4](https://github.com/khoih-prog/NTPClient_Generic/pull/4) leading to v3.3.0
4. Thanks to [DavidSteinmann](https://github.com/DavidSteinmann) to report the `getUTCEpochMillis()` bug and propose the bug fix in [getUTCEpochMillis() not returning correct value #7](https://github.com/khoih-prog/NTPClient_Generic/issues/7) leading to v3.7.1
5. Thanks to [argo9](https://github.com/argo9) to make PR in [added setUDP function #8](https://github.com/khoih-prog/NTPClient_Generic/pull/8) leading to v3.7.2
6. Thanks to [iBuilderBY](https://github.com/iBuilderBY) to report the bug with steps to duplicate in [Time jumping back when connection is lost and forward when up #9](https://github.com/khoih-prog/NTPClient_Generic/issues/9) leading to v3.7.5


<table>
  <tr>
    <td align="center"><a href="https://github.com/FWeinb"><img src="https://github.com/FWeinb.png" width="100px;" alt="FWeinb"/><br /><sub><b>⭐️ Fabrice Weinberg</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>Miguel Wisintainer</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/bmcdonnell"><img src="https://github.com/bmcdonnell.png" width="100px;" alt="bmcdonnell"/><br /><sub><b>bmcdonnell</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/DavidSteinmann"><img src="https://github.com/DavidSteinmann.png" width="100px;" alt="DavidSteinmann"/><br /><sub><b>DavidSteinmann</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/argo9"><img src="https://github.com/argo9.png" width="100px;" alt="argo9"/><br /><sub><b>argo9</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/iBuilderBY"><img src="https://github.com/iBuilderBY.png" width="100px;" alt="iBuilderBY"/><br /><sub><b>iBuilderBY</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/NTPClient_Generic/blob/main/LICENSE)

---

## Copyright

- Copyright 2015- Fabrice Weinberg

- Copyright 2020- Khoi Hoang


