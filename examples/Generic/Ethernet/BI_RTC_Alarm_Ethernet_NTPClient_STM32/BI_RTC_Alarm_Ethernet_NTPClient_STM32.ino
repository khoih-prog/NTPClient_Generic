/****************************************************************************************************************************
  BI_RTC_Alarm_Ethernet_NTPClient_STM32.ino

  Self-adjusting clock for one time zone using Built-in STM32 RTC

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
/****************************************************************************************************************************
  STM32 has five clock sources: HSI, HSE, LSI, LSE, PLL.
  
  (1) HSI is a high-speed internal clock, RC oscillator, with a frequency of 8MHz and low accuracy.
  (2) HSE is a high-speed external clock, which can be connected with quartz/ceramic resonator or external clock source. 
      Its frequency range is from 4MHz to 16MHz.
  (3) LSI is a low-speed internal clock, RC oscillator, with a frequency of 40 kHz, providing a low-power clock. 　
  (4) LSE is a low-speed external clock connected to 32.768 kHz quartz crystal.
  (5) PLL is the frequency doubling output of PLL, and its clock input source can be HSI/2, HSE or HSE/2. 
      Frequency doubling can be chosen as 2 to 16 times, but the maximum output frequency should not exceed 72MHz.
      
  The system clock SYSCLK can be derived from three clock sources:
  (1) HSI oscillator clock
  (2) HSE oscillator clock
  (3) PLL Clock
  STM32 can choose a clock signal to output to MCO foot (PA8), and can choose 2-frequency, HSI, HSE, or system clock for PLL output.
  Before any peripheral can be used, its corresponding clock must be enabled first.
 *****************************************************************************************************************************/
 
#include "defines.h"

#include <Timezone_Generic.h>             // https://github.com/khoih-prog/Timezone_Generic

#include <STM32RTC.h>                     // https://github.com/stm32duino/STM32RTC

/* Get the rtc object */
STM32RTC& rtc = STM32RTC::getInstance();


//////////////////////////////////////////

// US Eastern Time Zone (New York, Detroit)
TimeChangeRule myDST = {"EDT", Second, Sun, Mar, 2, -240};    //Daylight time = UTC - 4 hours
TimeChangeRule mySTD = {"EST", First, Sun, Nov, 2, -300};     //Standard time = UTC - 5 hours
Timezone myTZ(myDST, mySTD);

// If TimeChangeRules are already stored in EEPROM, comment out the three
// lines above and uncomment the line below.
//Timezone myTZ(100);       //assumes rules stored at EEPROM address 100

TimeChangeRule *tcr;        //pointer to the time change rule, use to get TZ abbrev

//////////////////////////////////////////

#include <NTPClient_Generic.h>

// A UDP instance to let us send and receive packets over UDP
EthernetUDP ntpUDP;

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

static bool gotCurrentTime = false;

// format and print a time_t value, with a time zone appended.
void printDateTime(time_t t, const char *tz)
{
  char buf[32];
  char m[4];    // temporary storage for month string (DateStrings.cpp uses shared buffer)
  strcpy(m, monthShortStr(month(t)));
  sprintf(buf, "%.2d:%.2d:%.2d %s %.2d %s %d %s",
          hour(t), minute(t), second(t), dayShortStr(weekday(t)), day(t), m, year(t), tz);
  Serial.println(buf);
}

void update_RTC(void)
{
  // Just get the correct time once
  if (timeClient.updated())
  {
    // Update RTC
    Serial.println("\nUpdating Time for STM32 RTC");
    Serial.println("********UPDATED********");
  
    // STM32 RTC clock starts from 01/01/2000 if not set. No battery-backed RTC.
    // STM32 RTC specific code
    unsigned long epoch = timeClient.getUTCEpochTime();
    
    rtc.setEpoch(epoch);

    // Set test alarm after 30s
    setRTC_Alarm(epoch + 30L);
    
    gotCurrentTime = true;
  }
}

void alarmMatch(void *data)
{
  UNUSED(data);
  Serial.println("*****RTC ALARM ACTIVATED*****");
  Serial.println("*****RTC ALARM ACTIVATED*****");
}

void setRTC_Alarm(unsigned long epochAlarm)
{
  rtc.attachInterrupt(alarmMatch);

  // Alarm at epochAlarm
  rtc.setAlarmEpoch(epochAlarm, rtc.MATCH_DHHMMSS);

  // Display Alarm time from RTC
  Serial.println("=======RTC ALARM SET========");

  // STM32 RTC specific code
  time_t utcAlarm   = epochAlarm;
  time_t localAlarm = myTZ.toLocal(utcAlarm, &tcr);
  //////

  printDateTime(utcAlarm, "UTC");
  printDateTime(localAlarm, tcr -> abbrev);
  Serial.println("============================");
}

void displayRTC()
{
  // Display time from RTC
  Serial.println("============================");

  // STM32 RTC specific code
  time_t utc = rtc.getEpoch();
  time_t local = myTZ.toLocal(utc, &tcr);
  //////
  
  printDateTime(utc, "UTC");
  printDateTime(local, tcr -> abbrev);
}

void check_status(void)
{
  // Update first time after 5s
  static ulong checkstatus_timeout  = 5000L;
  static ulong RTCDisplay_timeout   = 0;

  static ulong current_millis;

// Display every 10s
#define RTC_DISPLAY_INTERVAL        (10000L)

// Update RTC every hour if got correct time from NTP
#define RTC_UPDATE_INTERVAL         (3600 * 1000L)

// Retry updating RTC every 5s if haven't got correct time from NTP
#define RTC_RETRY_INTERVAL          (3 * 1000L)

  current_millis = millis();

  if ((current_millis > RTCDisplay_timeout) || (RTCDisplay_timeout == 0))
  {
    if (gotCurrentTime)
      displayRTC();
      
    RTCDisplay_timeout = current_millis + RTC_DISPLAY_INTERVAL;
  }
  
  // Update RTC every RTC_UPDATE_INTERVAL (3600) seconds.
  if ((current_millis > checkstatus_timeout))
  {
    update_RTC();
    
    if (gotCurrentTime)
    {
      Serial.println("RTC updated. Next update in seconds : " + String(RTC_UPDATE_INTERVAL/1000, DEC));
      checkstatus_timeout = current_millis + RTC_UPDATE_INTERVAL;
    }
    else
    {
      Serial.println("Retry RTC update in seconds : " + String(RTC_RETRY_INTERVAL/1000, DEC));
      checkstatus_timeout = current_millis + RTC_RETRY_INTERVAL;
    }   
  }
}

//////////////////////////////////////////

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println("\nStart BI_RTC_Alarm_Ethernet_NTPClient_STM32 on " + String(BOARD_NAME) + ", using " + String(SHIELD_TYPE));

  ET_LOGWARN3(F("Board :"), BOARD_NAME, F(", setCsPin:"), USE_THIS_SS_PIN);

  ET_LOGWARN(F("Default SPI pinout:"));
  ET_LOGWARN1(F("MOSI:"), MOSI);
  ET_LOGWARN1(F("MISO:"), MISO);
  ET_LOGWARN1(F("SCK:"),  SCK);
  ET_LOGWARN1(F("SS:"),   SS);
  ET_LOGWARN(F("========================="));

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // For other boards, to change if necessary
  #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2  || USE_ETHERNET_ENC )
    // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries
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
    //Ethernet.init(USE_THIS_SS_PIN);
  
  #endif  //( ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2  || USE_ETHERNET_ENC )
#endif

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  // you're connected now, so print out the data
  Serial.print(F("You're connected to the network, IP = "));
  Serial.println(Ethernet.localIP());

  timeClient.begin();

  // STM32 RTC specific code
  // Select RTC clock source: LSI_CLOCK, LSE_CLOCK or HSE_CLOCK.
  // By default the LSI is selected as source.
  //rtc.setClockSource(STM32RTC::LSE_CLOCK);
  rtc.begin(); // initialize RTC 24H format
  //////
}

void loop()
{
  timeClient.update();
  
  check_status();
}
