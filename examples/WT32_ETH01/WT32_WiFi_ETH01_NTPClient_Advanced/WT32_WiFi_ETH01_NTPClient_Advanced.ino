/****************************************************************************************************************************
  WT32_WiFi_ETH01_NTPClient_Advanced.ino

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

#define DEBUG_ETHERNET_WEBSERVER_PORT     Serial
#define NTP_DBG_PORT                      Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_     0
#define _NTP_LOGLEVEL_                    0

// For WiFi
#include <WiFi.h>

char ssid[] = "SSID";             // your network SSID (name)
char pass[] = "12345678";         // your network password

// For Ethernet
#include <WebServer_WT32_ETH01.h>

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <NTPClient_Generic.h>          // https://github.com/khoih-prog/NTPClient_Generic

// Select the IP address according to your local network
IPAddress myIP(192, 168, 2, 232);
IPAddress myGW(192, 168, 2, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

// Shared between ETH and WiFi for WT32_ETH01
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

NTPClient *timeClient;

void statusPrint()
{
  static IPAddress localEthernetIP;

  Serial.println("****ETH WIFI Status****");

  if (WT32_ETH01_isConnected())
  {
    localEthernetIP = ETH.localIP();
   
    if ( ( (uint32_t) localEthernetIP != 0 ) )
    {
      Serial.print(F("ETH OK"));
    }
    else
      Serial.print(F("ETH Failed"));
  }
  else
    Serial.print(F("ETH Failed"));

  if (WiFi.status() == WL_CONNECTED)
    Serial.println(F(", WiFi OK"));
  else
      Serial.println(F(", WiFi Failed"));
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

  Serial.print("\nStarting WT32_WiFi_ETH01_NTPClient_Advanced on "); Serial.print(ARDUINO_BOARD);
  Serial.print(" with "); Serial.println(SHIELD_TYPE);
  Serial.println(WEBSERVER_WT32_ETH01_VERSION);
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

  // Start Ethernet

  // To be called before ETH.begin()
  WT32_ETH01_onEvent();

  //bool begin(uint8_t phy_addr=ETH_PHY_ADDR, int power=ETH_PHY_POWER, int mdc=ETH_PHY_MDC, int mdio=ETH_PHY_MDIO, 
  //           eth_phy_type_t type=ETH_PHY_TYPE, eth_clock_mode_t clk_mode=ETH_CLK_MODE);
  //ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER, ETH_PHY_MDC, ETH_PHY_MDIO, ETH_PHY_TYPE, ETH_CLK_MODE);
  ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER);

  // Static IP, leave without this line to get IP via DHCP
  //bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = 0, IPAddress dns2 = 0);
  ETH.config(myIP, myGW, mySN, myDNS);

  // Using this will wait forever if no ETH connection
  //WT32_ETH01_waitForConnect();

  connectTimes = 0;

  while ( connectTimes++ < 20 )
  {
    if ( WT32_ETH01_isConnected() )
    {
      Serial.print(F("\nEthernet started @ IP address: "));
      Serial.println(ETH.localIP());

      break;
    }
    else if (connectTimes >= 20)
    {
      Serial.println(F("\nEthernet failed to connect"));
    }
           
    delay ( 500 );
    Serial.print ( "." );
  }
  
  /////////////////////////////////

  // You can specify the time server pool and the offset (in seconds, can be
  // changed later with setTimeOffset() ). Additionaly you can specify the
  // update interval (in milliseconds, can be changed using setUpdateInterval() ).
  timeClient = new NTPClient(ntpUDP, timeServer, (3600 * TIME_ZONE_OFFSET_HRS), NTP_UPDATE_INTERVAL_MS);

  timeClient->begin();

  Serial.println("Using NTP Server " + timeClient->getPoolServerName());
}

void loop()
{
  check_status();
}
