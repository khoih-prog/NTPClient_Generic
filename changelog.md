## NTPClient_Generic Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/NTPClient_Generic.svg?)](https://www.ardu-badge.com/NTPClient_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/NTPClient_Generic.svg)](https://github.com/khoih-prog/NTPClient_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/NTPClient_Generic/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/NTPClient_Generic.svg)](http://github.com/khoih-prog/NTPClient_Generic/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v3.6.0](#releases-v360)
  * [Releases v3.5.2](#releases-v352)
  * [Releases v3.5.1](#releases-v351)
  * [Releases v3.5.0](#releases-v350)
  * [Releases v3.4.1](#releases-v341)
  * [Releases v3.4.0](#releases-v340)
  * [Releases v3.3.0](#releases-v330)
  * [Releases v3.2.2](#releases-v322)
  * [Releases v3.2.1](#releases-v321)

---
---

## Changelog

### Releases v3.6.0

1. Add support to Potenta_H7 using Murata WiFi of Vision-Shield Ethernet
2. Fix `multiple-definitions` linker error. Check [Different behaviour using the src_cpp or src_h lib #80](https://github.com/khoih-prog/ESPAsync_WiFiManager/discussions/80)
3. Update all examples
4. Update `Packages_Patches`

### Releases v3.5.2

1. Auto detect ESP32 core version.
2. Fix bug in examples for WT32_ETH01
3. Update `Packages' Patches`

### Releases v3.5.1

1. Update `platform.ini` and `library.json` to use original `khoih-prog` instead of `khoih.prog` after PIO fix
2. Update `Packages' Patches`

### Releases v3.5.0

1. Add support to RTL8720DN, RTL8722DM, RTL8722CSM, etc. boards
2. Add examples with new features

### Releases v3.4.1

1. Fix typo in `library.json`

### Releases v3.4.0

1. Add support to WT32_ETH01 (ESP32 + LAN8720) boards
2. Add examples with new features

### Releases v3.3.0

1. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).
2. Add support to RP2040-based boards, such as **Nano_RP2040_Connect, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed).
3. Add packet validity checks
4. Add version string
5. Improve and add more debugging codes

### Releases v3.2.2

1. Add examples to use **STM32 Built-In RTC.**

### Releases v3.2.1

1. Initial porting to many Generic boards using WiFi/Ethernet modules/shields.
2. Add support to **SAMD21/SAMD51, nRF52, STM32F/L/H/G/WB/MP1 with WiFiNINA, W5x00, ENC28J60, LAN8742A Ethernet modules/shields.**
3. Add functions.
4. Completely new examples using NTP time to update DS3231 RTC and/or local clock.


