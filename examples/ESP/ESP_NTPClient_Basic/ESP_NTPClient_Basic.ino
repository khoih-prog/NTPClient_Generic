/****************************************************************************************************************************
  ESP_NTPClient_Bas.ino

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

#define TIME_ZONE_OFFSET_HRS            (-4)

NTPClient timeClient(ntpUDP);

void setup() 
{
  Serial.begin(115200);
  while (!Serial && millis() < 5000);
  
  Serial.println("\nStarting ESP_NTPClient_Basic on " + String(ARDUINO_BOARD));
  Serial.println(NTPCLIENT_GENERIC_VERSION);

  Serial.println("Connecting to: " + String(ssid));

  WiFi.begin(ssid, pass);

  while ( WiFi.status() != WL_CONNECTED ) 
  {
    delay ( 500 );
    Serial.print ( "." );
  }

  Serial.print(F("\nESP_NTPClient_Basic started @ IP address: "));
  Serial.println(WiFi.localIP());
  
  timeClient.begin();
  timeClient.setTimeOffset(3600 * TIME_ZONE_OFFSET_HRS);
  // default 60000 => 60s. Set to once per hour
  timeClient.setUpdateInterval(SECS_IN_HR);
  
  Serial.println("Using NTP Server " + timeClient.getPoolServerName());
}

void loop()
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

  delay(10000);
}
