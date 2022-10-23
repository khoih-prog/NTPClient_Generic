/****************************************************************************************************************************
  ESP_NTPClient_Advanced.ino

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
 *****************************************************************************************************************************/

#if !( defined(ESP8266) ||  defined(ESP32) )
  #error This code is intended to run on the ESP8266 or ESP32 platform! Please check your Tools->Board setting.
#endif

#define NTP_DBG_PORT                Serial

// Debug Level from 0 to 4
#define _NTP_LOGLEVEL_              0

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <NTPClient_Generic.h>          // https://github.com/khoih-prog/NTPClient_Generic

#if (ESP32)
  #include <WiFi.h>
#elif (ESP8266)
  #include <ESP8266WiFi.h>
#endif

#include <WiFiUdp.h>

char ssid[] = "SSID";             // your network SSID (name)
char pass[] = "12345678";         // your network password

WiFiUDP ntpUDP;

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

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionaly you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, timeServer, (3600 * TIME_ZONE_OFFSET_HRS), NTP_UPDATE_INTERVAL_MS);

int WiFiStatus = WL_IDLE_STATUS;

void setup()
{
  Serial.begin(115200);
  while (!Serial && millis() < 5000);

  Serial.println("\nStarting ESP_NTPClient_Advanced on " + String(ARDUINO_BOARD));
  Serial.println(NTPCLIENT_GENERIC_VERSION);

  Serial.println("Connecting to: " + String(ssid));

  WiFi.begin(ssid, pass);

  while ( WiFi.status() != WL_CONNECTED )
  {
    delay ( 500 );
    Serial.print ( "." );
  }

  WiFiStatus = WL_CONNECTED;

  Serial.print(F("\nESP_NTPClient_Advanced started @ IP address: "));
  Serial.println(WiFi.localIP());

  timeClient.begin();

  Serial.println("Using NTP Server " + timeClient.getPoolServerName());
}

void updateStatus()
{
  static unsigned long wifiStatus_timeout   = 0;
  static unsigned long updateStatus_timeout = 0;

#define WIFI_CHECK_INTERVAL       1000L
#define UPDATE_INTERVAL           10000L

  if ((millis() > wifiStatus_timeout) || (wifiStatus_timeout == 0))
  {
    if (WiFi.status() != WiFiStatus)
    {
      WiFiStatus = WiFi.status();
  
      if (WiFiStatus == WL_CONNECTED)
        Serial.println("Changed, WiFiStatus = Connected");
      else if (WiFiStatus == WL_DISCONNECTED)
        Serial.println("Changed, WiFiStatus = Disconnected");
      else if (WiFiStatus == WL_IDLE_STATUS)
        Serial.println("Changed, WiFiStatus = Idle");
      else if (WiFiStatus == WL_NO_SSID_AVAIL)
        Serial.println("Changed, WiFiStatus = lost WiFi SSID");
      else if (WiFiStatus == WL_CONNECTION_LOST)
        Serial.println("Changed, WiFiStatus = lost WiFi connection");
      else
      {
        Serial.print("Changed, WiFiStatus = "); Serial.println(WiFiStatus);
      }
    }
   
    wifiStatus_timeout = millis() + WIFI_CHECK_INTERVAL;
  }
  
  // Send update request every UPDATE_INTERVAL (10) seconds: we don't need to send update request frequently
  if ((millis() > updateStatus_timeout) || (updateStatus_timeout == 0))
  {
    timeClient.update();
  
    if (timeClient.updated())
      Serial.println("********UPDATED********");
    else
      Serial.println("******NOT UPDATED******");
  
    Serial.println("UTC : " + timeClient.getFormattedUTCTime());
    Serial.println("UTC : " + timeClient.getFormattedUTCDateTime());
    Serial.println("LOC : " + timeClient.getFormattedTime());
    Serial.println("LOC : " + timeClient.getFormattedDateTime());
    Serial.println("UTC EPOCH : " + String(timeClient.getUTCEpochTime()));
    Serial.println("LOC EPOCH : " + String(timeClient.getEpochTime()));
  
    // Function test
    // Without leading 0
    Serial.println(String("UTC : ") + timeClient.getUTCHours() + ":" + timeClient.getUTCMinutes() + ":" + timeClient.getUTCSeconds() + " " +
                   timeClient.getUTCDoW() + " " + timeClient.getUTCDay() + "/" + timeClient.getUTCMonth() + "/" + timeClient.getUTCYear() + " or " +
                   timeClient.getUTCDay() + " " + timeClient.getUTCMonthStr() + " " + timeClient.getUTCYear());
    // With leading 0
    Serial.println(String("UTC : ") + timeClient.getUTCStrHours() + ":" + timeClient.getUTCStrMinutes() + ":" + timeClient.getUTCStrSeconds() + " " +
                   timeClient.getUTCDoW() + " " + timeClient.getUTCDay() + "/" + timeClient.getUTCMonth() + "/" + timeClient.getUTCYear() + " or " +
                   timeClient.getUTCDay() + " " + timeClient.getUTCMonthStr() + " " + timeClient.getUTCYear());
    // Without leading 0
    Serial.println(String("LOC : ") + timeClient.getHours() + ":" + timeClient.getMinutes() + ":" + timeClient.getSeconds() + " " +
                   timeClient.getDoW() + " " + timeClient.getDay() + "/" + timeClient.getMonth() + "/" + timeClient.getYear() + " or " +
                   timeClient.getDay() + " " + timeClient.getMonthStr() + " " + timeClient.getYear());
    // With leading 0
    Serial.println(String("LOC : ") + timeClient.getStrHours() + ":" + timeClient.getStrMinutes() + ":" + timeClient.getStrSeconds() + " " +
                   timeClient.getDoW() + " " + timeClient.getDay() + "/" + timeClient.getMonth() + "/" + timeClient.getYear() + " or " +
                   timeClient.getDay() + " " + timeClient.getMonthStr() + " " + timeClient.getYear());
    
    updateStatus_timeout = millis() + UPDATE_INTERVAL;
  }
}

void loop()
{
  updateStatus();
}
