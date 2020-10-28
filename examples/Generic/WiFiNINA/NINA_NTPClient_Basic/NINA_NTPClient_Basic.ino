/****************************************************************************************************************************
  NINA_NTPClient_Basic.ino

  For AVR, ESP8266/ESP32, SAMD21/SAMD51, nRF52, STM32, SAM DUE boards using 
  a) Ethernet W5x00, ENC28J60, LAN8742A
  b) WiFiNINA
  c) ESP8266/ESP32 WiFi
  d) ESP8266/ESP32-AT-command WiFi

  Based on and modified from Arduino NTPClient Library (https://github.com/arduino-libraries/NTPClient)
  to support other boards such as ESP8266/ESP32, SAMD21, SAMD51, Adafruit's nRF52 boards, SAM DUE, etc.
  and Ethernet/WiFi/WiFiNINA shields
  
  Copyright (C) 2015 by Fabrice Weinberg and licensed under MIT License (MIT)

  Built by Khoi Hoang https://github.com/khoih-prog/NTPClient_Generic
  Licensed under MIT license
  Version: 3.2.2

  Version Modified By  Date      Comments
  ------- -----------  ---------- -----------
  3.2.1   K Hoang      27/10/2020 Initial porting to support SAM DUE, SAMD21, SAMD51, nRF52, ESP32/ESP8266, STM32, etc. boards 
                                  using Ethernet/WiFi/WiFiNINA shields. Add more features and functions.
  3.2.2   K Hoang      28/10/2020 Add examples to use STM32 Built-In RTC.
 *****************************************************************************************************************************/
 
#include "defines.h"

#include <NTPClient_Generic.h>

// A UDP instance to let us send and receive packets over UDP
WiFiUDP ntpUDP;

#define TIME_ZONE_OFFSET_HRS            (-4)

NTPClient timeClient(ntpUDP);

void setup() 
{
  Serial.begin(115200);
  while (!Serial);
  
  Serial.print("\nStarting NINA_NTPClient_Basic on " + String(BOARD_NAME));
  Serial.println(" with " + String(SHIELD_TYPE));

  Serial.println("Connecting to: " + String(ssid));

  WiFi.begin(ssid, pass);

  while ( WiFi.status() != WL_CONNECTED ) 
  {
    delay ( 500 );
    Serial.print ( "." );
  }

  Serial.print(F("\nNINA_NTPClient_Basic started @ IP address: "));
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
