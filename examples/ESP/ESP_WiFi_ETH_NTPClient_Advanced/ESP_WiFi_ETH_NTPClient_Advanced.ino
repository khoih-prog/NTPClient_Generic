/****************************************************************************************************************************
  ESP_WiFi_ETH_NTPClient_Advanced.ino

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

#if !( defined(ESP32) )
#error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
#endif

#include "defines.h"

#define DEBUG_ETHERNET_WEBSERVER_PORT     Serial
#define NTP_DBG_PORT                      Serial

// Debug Level from 0 to 4
//#define _ETHERNET_WEBSERVER_LOGLEVEL_     0
#define _NTP_LOGLEVEL_                    0

// For WiFi
#include <WiFi.h>

char ssid[] = "SSID";             // your network SSID (name)
char pass[] = "12345678";         // your network password

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <NTPClient_Generic.h>          // https://github.com/khoih-prog/NTPClient_Generic

// Select the IP address according to your local network
//IPAddress myIP(192, 168, 2, 232);
//IPAddress myGW(192, 168, 2, 1);
//IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
//IPAddress myDNS(8, 8, 8, 8);

// For default ESP32 WiFi
WiFiUDP ntpWiFiUDP;

// A UDP instance to let us send and receive packets over UDP
EthernetUDP ntpEthernetUDP;

// NTP server
//World
//char timeServer[] = "time.nist.gov";
// Canada
char timeServer[] = "0.ca.pool.ntp.org";
//char timeServer[] = "1.ca.pool.ntp.org";
//char timeServer[] = "2.ca.pool.ntp.org";
//char timeServer[] = "3.ca.pool.ntp.org";
// Europe
//char timeServer[] = ""europe.pool.ntp.org";

#define TIME_ZONE_OFFSET_HRS            (-4)
#define NTP_UPDATE_INTERVAL_MS          60000L

NTPClient *timeClient;

bool isWiFiUDP = true;

void statusPrint()
{ 
  Serial.println("****WIFI Status****");

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println(F("WiFi OK"));

    if (!isWiFiUDP)
    {
      // Switch back to WiFi UDP for NTP if WiFi is OK
      timeClient->setUDP(ntpWiFiUDP);

      isWiFiUDP = true;
      Serial.println(F("NTP => WiFi"));
    }
  }
  else
  {
    Serial.println(F("WiFi Failed"));

    if (isWiFiUDP)
    {
      // Switch to Ethernet UDP for NTP if WiFi lost
      timeClient->setUDP(ntpEthernetUDP);

      isWiFiUDP = false;
      Serial.println(F("NTP => Ethernet"));
    }
  }
}

#define NTP_UPDATE_SHORT_INTERVAL   10000L
#define NTP_UPDATE_LONG_INTERVAL    60000L

void ntpUpdate(uint32_t& delayTime)
{
  timeClient->update();

  if (timeClient->updated())
  {
    Serial.println("********UPDATED********");

    delayTime = NTP_UPDATE_LONG_INTERVAL;
  }
  else
  {
    Serial.println("******NOT UPDATED******");

    delayTime = NTP_UPDATE_SHORT_INTERVAL;
  }

  Serial.println("UTC : " + timeClient->getFormattedUTCTime());
  Serial.println("UTC : " + timeClient->getFormattedUTCDateTime());
  Serial.println("LOC : " + timeClient->getFormattedTime());
  Serial.println("LOC : " + timeClient->getFormattedDateTime());
  Serial.println("UTC EPOCH : " + String(timeClient->getUTCEpochTime()));
  Serial.println("LOC EPOCH : " + String(timeClient->getEpochTime()));

  // Function test
  // Without leading 0
  Serial.println(String("UTC : ") + timeClient->getUTCHours() + ":" + timeClient->getUTCMinutes() + ":" + timeClient->getUTCSeconds() + " " +
                 timeClient->getUTCDoW() + " " + timeClient->getUTCDay() + "/" + timeClient->getUTCMonth() + "/" + timeClient->getUTCYear() + " or " +
                 timeClient->getUTCDay() + " " + timeClient->getUTCMonthStr() + " " + timeClient->getUTCYear());
  // With leading 0
  Serial.println(String("UTC : ") + timeClient->getUTCStrHours() + ":" + timeClient->getUTCStrMinutes() + ":" + timeClient->getUTCStrSeconds() + " " +
                 timeClient->getUTCDoW() + " " + timeClient->getUTCDay() + "/" + timeClient->getUTCMonth() + "/" + timeClient->getUTCYear() + " or " +
                 timeClient->getUTCDay() + " " + timeClient->getUTCMonthStr() + " " + timeClient->getUTCYear());
  // Without leading 0
  Serial.println(String("LOC : ") + timeClient->getHours() + ":" + timeClient->getMinutes() + ":" + timeClient->getSeconds() + " " +
                 timeClient->getDoW() + " " + timeClient->getDay() + "/" + timeClient->getMonth() + "/" + timeClient->getYear() + " or " +
                 timeClient->getDay() + " " + timeClient->getMonthStr() + " " + timeClient->getYear());
  // With leading 0
  Serial.println(String("LOC : ") + timeClient->getStrHours() + ":" + timeClient->getStrMinutes() + ":" + timeClient->getStrSeconds() + " " +
                 timeClient->getDoW() + " " + timeClient->getDay() + "/" + timeClient->getMonth() + "/" + timeClient->getYear() + " or " +
                 timeClient->getDay() + " " + timeClient->getMonthStr() + " " + timeClient->getYear());
}

void check_status()
{
#define STATUS_CHECK_INTERVAL       10000L

  static uint32_t checkstatus_timeout = STATUS_CHECK_INTERVAL;
  static uint32_t ntpUpdate_timeout   = NTP_UPDATE_SHORT_INTERVAL;
  static uint32_t ntpUpdateDelayTime  = NTP_UPDATE_SHORT_INTERVAL;

  static uint32_t currentMillis;

  currentMillis = millis();

  // Send status report every STATUS_REPORT_INTERVAL (10) seconds: we don't need to send updates frequently if there is no status change.
  if ( currentMillis > checkstatus_timeout )
  {
    statusPrint();
    checkstatus_timeout = currentMillis + STATUS_CHECK_INTERVAL;
  }

  // Update NTP every NTP_UPDATE_SHORT_INTERVAL (10s) or NTP_UPDATE_LONG_INTERVAL (60) seconds
  // we don't need to send updates frequently
  if ( currentMillis > ntpUpdate_timeout )
  {
    // Lengthen time betwen updates if got time. Don't bombard NTP server
    ntpUpdate(ntpUpdateDelayTime);
    ntpUpdate_timeout = currentMillis + ntpUpdateDelayTime;
  }
}

void setup()
{
  Serial.begin(115200);
  while (!Serial && millis() < 5000);

  Serial.print("\nStarting ESP_WiFi_ETH_NTPClient_Advanced on "); Serial.print(ARDUINO_BOARD);
  Serial.print(" with "); Serial.println(SHIELD_TYPE);
  //Serial.println(WEBSERVER_WT32_ETH01_VERSION);
  Serial.println(ETHERNET_WEBSERVER_VERSION);
  Serial.println(NTPCLIENT_GENERIC_VERSION);

  /////////////////////////////////

  // Start WiFi

  Serial.println("Connecting to: " + String(ssid));

  WiFi.begin(ssid, pass);

  uint8_t connectTimes = 0;

  while ( connectTimes++ < 20 )
  {
    if ( WiFi.status() == WL_CONNECTED )
    {
      Serial.print(F("\nWiFi started @ IP address: "));
      Serial.println(WiFi.localIP());

      break;
    }
    else if (connectTimes >= 20)
    {
      Serial.println(F("\nWiFi failed to connect"));
    }

    delay ( 500 );
    Serial.print ( "." );
  }

  /////////////////////////////////

#if USE_ETHERNET
  ET_LOGWARN(F("=========== USE_ETHERNET ==========="));
#elif USE_ETHERNET2
  ET_LOGWARN(F("=========== USE_ETHERNET2 ==========="));
#elif USE_ETHERNET3
  ET_LOGWARN(F("=========== USE_ETHERNET3 ==========="));
#elif USE_ETHERNET_LARGE
  ET_LOGWARN(F("=========== USE_ETHERNET_LARGE ==========="));
#elif USE_ETHERNET_ESP8266
  ET_LOGWARN(F("=========== USE_ETHERNET_ESP8266 ==========="));
#elif USE_ETHERNET_ENC
  ET_LOGWARN(F("=========== USE_ETHERNET_ENC ==========="));
#else
  ET_LOGWARN(F("========================="));
#endif

  ET_LOGWARN(F("Default SPI pinout:"));
  ET_LOGWARN1(F("MOSI:"), MOSI);
  ET_LOGWARN1(F("MISO:"), MISO);
  ET_LOGWARN1(F("SCK:"),  SCK);
  ET_LOGWARN1(F("SS:"),   SS);
  ET_LOGWARN(F("========================="));

#define PIN_D18           18        // Pin D18 mapped to pin GPIO18/VSPI_SCK of ESP32
#define PIN_D19           19        // Pin D19 mapped to pin GPIO19/VSPI_MISO of ESP32
#define PIN_D23           23        // Pin D23 mapped to pin GPIO23/VSPI_MOSI of ESP32

  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // Connection for ESP32
  // MOSI: GPIO23, MISP: GPIO19, SCK: GPIO18, CS/SS: GPIO22

#ifndef USE_THIS_SS_PIN
#define USING_M5STACK_W5500     false
#if USING_M5STACK_W5500
#warning Using M5Stack_Core_ESP32 with W5500 mudule
#define USE_THIS_SS_PIN   26    // For M5Stack_Core_ESP32 with W5500 mudule
#else
#define USE_THIS_SS_PIN   22    // For ESP32
#endif
#endif

  ET_LOGWARN1(F("ESP32 setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
#if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC )
  // Must use library patch for Ethernet, EthernetLarge libraries
  // ESP32 => GPIO2,4,5,13,15,21,22 OK with Ethernet, Ethernet2, EthernetLarge
  // ESP32 => GPIO2,4,5,15,21,22 OK with Ethernet3

  //Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (USE_THIS_SS_PIN);

#elif USE_ETHERNET3
  // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
#ifndef ETHERNET3_MAX_SOCK_NUM
#define ETHERNET3_MAX_SOCK_NUM      4
#endif

  Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (ETHERNET3_MAX_SOCK_NUM);

#elif USE_CUSTOM_ETHERNET

  // You have to add initialization for your Custom Ethernet here
  // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
  Ethernet.init(USE_THIS_SS_PIN);

#endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  // Just info to know how to connect correctly
  Serial.println("=========================");
  Serial.println("Currently Used SPI pinout:");
  Serial.print("MOSI:");
  Serial.println(MOSI);
  Serial.print("MISO:");
  Serial.println(MISO);
  Serial.print("SCK:");
  Serial.println(SCK);
  Serial.print("CS/SS:");
  Serial.println(USE_THIS_SS_PIN);
#if USE_ETHERNET3
  Serial.print("SPI_CS:");
  Serial.println(SPI_CS);
#endif
  Serial.println(F("========================="));

  Serial.print(F("Using mac index = "));
  Serial.println(index);

  Serial.print(F("Connected! IP address: "));
  Serial.println(Ethernet.localIP());

  /////////////////////////////////

  // You can specify the time server pool and the offset (in seconds, can be
  // changed later with setTimeOffset() ). Additionaly you can specify the
  // update interval (in milliseconds, can be changed using setUpdateInterval() ).
  if (WiFi.status() == WL_CONNECTED)
  {
    timeClient = new NTPClient(ntpWiFiUDP, timeServer, (3600 * TIME_ZONE_OFFSET_HRS), NTP_UPDATE_INTERVAL_MS);
    isWiFiUDP = true;
  }
  else
  {
    timeClient = new NTPClient(ntpEthernetUDP, timeServer, (3600 * TIME_ZONE_OFFSET_HRS), NTP_UPDATE_INTERVAL_MS);
    isWiFiUDP = false;
  }

  timeClient->begin();

  Serial.println("Using NTP Server " + timeClient->getPoolServerName());
}

void loop()
{
  check_status();
}
