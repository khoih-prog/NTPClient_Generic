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
  * [Releases v3.7.5](#releases-v375)
  * [Releases v3.7.4](#releases-v374)
  * [Releases v3.7.3](#releases-v373)
  * [Releases v3.7.2](#releases-v372)
  * [Releases v3.7.1](#releases-v371)
  * [Releases v3.7.0](#releases-v370)
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

### Releases v3.7.5

1. Fix bug causing time jumping back or forth when network has problem. Check [Time jumping back when connection is lost and forward when up #9](https://github.com/khoih-prog/NTPClient_Generic/issues/9) and [Time jumping back 9 minutes #1](https://github.com/khoih-prog/NTPClient_Generic/issues/1)
2. Modify example [ESP_NTPClient_Advanced](https://github.com/khoih-prog/NTPClient_Generic/tree/main/examples/ESP/ESP_NTPClient_Advanced) to demo the better way to use the library, without using long `delay()`
3. Add support to `RP2040W` boards using CYW43439 WiFi
4. Optimize and clean up
5. Modify `platformio.ini` and `library.json` to reduce error with PIO
6. Update `Packages' Patches`

### Releases v3.7.4

1. Sync with [NTPClient releases v3.2.1](https://github.com/arduino-libraries/NTPClient/releases/tag/3.2.1)


### Releases v3.7.3

1. Use new [Ethernet_Generic library](https://github.com/khoih-prog/Ethernet_Generic) as default for W5x00.
2. Rewrite to avoid `multiple-definitions` linker error for multiple-file project
3. Add example [multiFileProject](examples/multiFileProject) to demo how to avoid `multiple-definitions` linker error for multiple-file project
4. Add support to SPI1 for RP2040 using [arduino-pico core](https://github.com/earlephilhower/arduino-pico)
5. Add support SPI2 for ESP32
6. Rewrite all the examples to support new features
7. Update `Packages' Patches`

### Releases v3.7.2

1. Add setUDP() function to enable auto-switching between `WiFi` and `Ethernet` UDP instances. Check [added setUDP function #8](https://github.com/khoih-prog/NTPClient_Generic/pull/8)
2. Add new examples [ESP_WiFi_ETH_NTPClient_Advanced](https://github.com/khoih-prog/NTPClient_Generic/tree/main/examples/ESP/ESP_WiFi_ETH_NTPClient_Advanced) and [WT32_WiFi_ETH01_NTPClient_Advanced](https://github.com/khoih-prog/NTPClient_Generic/tree/main/examples/WT32_ETH01/WT32_WiFi_ETH01_NTPClient_Advanced) to use the new setUDP() function for auto-switching between `WiFi` and `Ethernet` UDP to update NTP time.
3. Update `Packages_Patches`

### Releases v3.7.1

1. Fix getUTCEpochMillis() bug. Check [getUTCEpochMillis() not returning correct value #7](https://github.com/khoih-prog/NTPClient_Generic/issues/7)
2. Update Adafruit SAMD `Packages_Patches`

### Releases v3.7.0

1. Make compatible with old code
2. Update all examples
3. Update `Packages_Patches`

### Releases v3.6.0

1. Add support to Portenta_H7 using Murata WiFi of Vision-Shield Ethernet
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


