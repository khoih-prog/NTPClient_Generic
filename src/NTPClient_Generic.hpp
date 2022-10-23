/****************************************************************************************************************************
  NTPClient_Generic.hpp
 
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

// Reintroduce to prevent duplication compile error, pragma once can't prevent
#ifndef NTPCLIENT_GENERIC_HPP
#define NTPCLIENT_GENERIC_HPP

////////////////////////////////////////

#define NTPCLIENT_GENERIC_VERSION             "NTPClient_Generic v3.7.5"

#define NTPCLIENT_GENERIC_VERSION_MAJOR       3
#define NTPCLIENT_GENERIC_VERSION_MINOR       7
#define NTPCLIENT_GENERIC_VERSION_PATCH       5

#define NTPCLIENT_GENERIC_VERSION_INT        3007005

////////////////////////////////////////

#include "Arduino.h"

#include <TimeLib.h>    // https://github.com/PaulStoffregen/Time

////////////////////////////////////////

#if ( defined(CONFIG_PLATFORM_8721D) || defined(BOARD_RTL8722D) || defined(BOARD_RTL8722DM_MINI) || defined(BOARD_RTL8720DN_BW16) ) 
  #include <wifi_Udp.h>
#else
  #include <Udp.h>
#endif

////////////////////////////////////////

#include "NTPClient_Generic_Debug.h"

////////////////////////////////////////

#define SECS_IN_DAY               (86400L)
#define SECS_IN_HR                (3600L)
#define SECS_IN_MIN               (60L)

#define SEVENTYYEARS              (2208988800UL)
#define FRACTIONSPERMILLI         (4294967UL)
#define NTP_PACKET_SIZE           48

////////////////////////////////////////

#define NTP_DEFAULT_LOCAL_PORT    1337
#define NTP_SEVER_PORT            123

////////////////////////////////////////

//Timeout (ms) from sendNTPPacket() to checkResponse(). Use larger if slower network
#if !defined(TIMEOUT_WAITING_PACKET)
  #define TIMEOUT_WAITING_NTP_PACKET  1000
#endif  

////////////////////////////////////////


class NTPClient;

typedef void (*NTPUpdateCallbackFunction)(NTPClient* c);

class NTPClient 
{
  private:
    UDP*          _udp;
    bool          _udpSetup       = false;

    const char*   _poolServerName = "pool.ntp.org";                 // Default time server
    IPAddress     _poolServerIP   = IPAddress(162,159,200,123);     // Default time server IP of "pool.ntp.org"
    int           _port           = NTP_DEFAULT_LOCAL_PORT;
    
    // Time ofset in seconds
    long          _timeOffset     = 0;

    unsigned int  _retryInterval  = 1000;   // In ms
    unsigned long _updateInterval = 60000;  // In ms

    unsigned long _currentEpoc    = 0;      // In s
    unsigned long _currentFraction = 0;     // In 1/(2^32) s
    unsigned long _lastUpdate     = 0;      // In ms
    unsigned long _lastRequest    = 0;      // IN ms

    byte          _packetBuffer[NTP_PACKET_SIZE];

    NTPUpdateCallbackFunction _updateCallback = NULL;

    void          sendNTPPacket();
    bool          checkResponse();

  public:
    NTPClient(const long& timeOffset = 0);
    
    NTPClient(UDP& udp, const long& timeOffset = 0);
    NTPClient(UDP& udp, const char* poolServerName, const long& timeOffset = 0, const unsigned long& updateInterval = 60000);
    NTPClient(UDP& udp, const IPAddress& poolServerIP, const long& timeOffset = 0, const unsigned long& updateInterval = 60000);

    ////////////////////////////////////////

    /**
      Set UDP socket. Used to switch between WiFi and Ethernet UDP in runtime
      
      @param UDPsocket
    */
    inline void setUDP(UDP& udp)
    {
      this->_udp = &udp;
    }

    ////////////////////////////////////////
    
    /**
       Set time server name

       @param poolServerName
    */
    inline void setPoolServerName(const char* poolServerName) 
    {
      this->_poolServerName = poolServerName;
    }

    ////////////////////////////////////////
   
    /**
       Get time server name

       @param poolServerName
    */
    String getPoolServerName()
    {
      return String(this->_poolServerName);
    }
    
    ///////////////////////////////
    
    /**
       Set time server IP

       @param poolServerIP
    */
    inline void setPoolServerIP(const IPAddress& poolServerIP)
    {
      this->_poolServerIP = poolServerIP;
    }

    ////////////////////////////////////////
    
    /**
       Get time server IP. Use only after setPoolServerIP()

       @param poolServerIP
    */
    inline IPAddress getPoolServerIP()
    {
      return (this->_poolServerIP);
    }

    ////////////////////////////////////////
    
    /**
     * Set random local port
     */
    void setRandomPort(uint16_t minValue = 49152, uint16_t maxValue = 65535)
    {
      randomSeed(millis());
      this->_port = random(minValue, maxValue);
    }

    ////////////////////////////////////////

    /**
       Starts the underlying UDP client with the specified local port
    */
    void begin(int port = NTP_DEFAULT_LOCAL_PORT);

    ////////////////////////////////////////

    /**
       This should be called in the main loop of your application. By default an update from the NTP Server is only
       made every 60 seconds. This can be configured in the NTPClient constructor.

       @return true on success, false on failure
    */
    bool update();

    ////////////////////////////////////////

    /**
       Has the time ever been sucessfully updated

    */
    bool updated() 
    {
      return (this->_currentEpoc != 0);
    }

    ////////////////////////////////////////
    
    inline bool isTimeSet() const 
    {
      return (this->_lastUpdate != 0); // returns true if the time has been set, else false
    }

    ////////////////////////////////////////

    /**
       Register a callback function for when the time gets updated

    */
    inline void setUpdateCallback(NTPUpdateCallbackFunction f) 
    {
      _updateCallback = f;
    }

    ////////////////////////////////////////

    /**
       This will force the update from the NTP Server.
       This can block for a full second
       @return true on success, false on failure
    */
    bool forceUpdate();

    ////////////////////////////////////////
    
    int getUTCYear() const 
    {
      return ( year(this->getUTCEpochTime()) );      // Year, 20xy
    }

    ////////////////////////////////////////

    String getUTCMonthStr() const 
    {
      return ( monthShortStr(month(this->getUTCEpochTime())) );      // Month, 1-12
    }

    ////////////////////////////////////////

    int getUTCMonth() const 
    {
      return ( month(this->getUTCEpochTime()) );      // Month, 1-12
    }

    ////////////////////////////////////////

    String getUTCDoW() const 
    {
      return ( dayShortStr(weekday(this->getUTCEpochTime())) );        // Day of Week, Sun-Mon-..-Sat
    }

    ////////////////////////////////////////

    int getUTCDay() const 
    {
      return ( day(this->getUTCEpochTime()) );        // Day of Month, 1-31
    }

    ////////////////////////////////////////

    int getUTCHours() const 
    {
      return ( hour(this->getUTCEpochTime()) );       // Hour, 0-23
    }

    ////////////////////////////////////////

    int getUTCMinutes() const 
    {
      return ( minute(this->getUTCEpochTime()) );     // Min, 0-59
    }

    ////////////////////////////////////////

    int getUTCSeconds() const 
    {
      return ( second(this->getUTCEpochTime()) );     // Sec, 0-59
    }

    ////////////////////////////////////////

    // With leading 0
    String getUTCStrHours() const 
    {
      unsigned long tempo = this->getUTCHours();

      return ( tempo < 10 ? "0" + String(tempo) : String(tempo) );       // Hour, 00-23
    }

    ////////////////////////////////////////

    // With leading 0
    String getUTCStrMinutes() const 
    {
      unsigned long tempo = this->getUTCMinutes();
      
      return ( tempo < 10 ? "0" + String(tempo) : String(tempo) );      // Min, 00-59
    }

    ////////////////////////////////////////

    // With leading 0
    String getUTCStrSeconds() const 
    {
      unsigned long tempo = this->getUTCSeconds();
      
      return ( tempo < 10 ? "0" + String(tempo) : String(tempo) );      // Sec, 0-59
    }

    ////////////////////////////////////////

    int getYear() const 
    {
      return ( year(this->getEpochTime()) );      // Year, 20xy
    }

    ////////////////////////////////////////

    String getMonthStr() const 
    {
      return ( monthShortStr(month(this->getEpochTime())) );      // Month, 1-12
    }

    ////////////////////////////////////////

    int getMonth() const 
    {
      return ( month(this->getEpochTime()) );      // Month, 1-12
    }

    ////////////////////////////////////////

    String getDoW() const 
    {
      return ( dayShortStr(weekday(this->getEpochTime())) );        // Day of Week, Sun-Mon-..-Sat
    }

    ////////////////////////////////////////

    int getDay() const 
    {
      return ( day(this->getEpochTime()) );        // Day of Month, 1-31
    }

    ////////////////////////////////////////

    int getHours() const 
    {
      return ( hour(this->getEpochTime()) );       // Hour, 0-23
    }

    ////////////////////////////////////////

    int getMinutes() const 
    {
      return ( minute(this->getEpochTime()) );     // Min, 0-59
    }

    ////////////////////////////////////////

    int getSeconds() const 
    {
      return ( second(this->getEpochTime()) );     // Sec, 0-59
    }

    ////////////////////////////////////////

    // With leading 0
    String getStrHours() const 
    {
      unsigned long tempo = this->getHours();

      return ( tempo < 10 ? "0" + String(tempo) : String(tempo) );       // Hour, 00-23
    }

    ////////////////////////////////////////

    // With leading 0
    String getStrMinutes() const 
    {
      unsigned long tempo = this->getMinutes();
      
      return ( tempo < 10 ? "0" + String(tempo) : String(tempo) );      // Min, 00-59
    }

    ////////////////////////////////////////

    // With leading 0
    String getStrSeconds() const 
    {
      unsigned long tempo = this->getSeconds();
      
      return ( tempo < 10 ? "0" + String(tempo) : String(tempo) );      // Sec, 0-59
    }

    ////////////////////////////////////////
    
    /**
       Changes the time offset. Useful for changing timezones dynamically
    */
    inline void setTimeOffset(int timeOffset) 
    {
      this->_timeOffset     = timeOffset;
    }

    ////////////////////////////////////////

    /**
       Set the update interval to another frequency. E.g. useful when the
       timeOffset should not be set in the constructor
    */
    inline void setUpdateInterval(const unsigned long& updateInterval) 
    {
      this->_updateInterval = updateInterval;
    }

    ////////////////////////////////////////

    /**
       Set the retry interval to another frequency in ms
    */
    inline void setRetryInterval(const int& retryInterval) 
    {
      _retryInterval = retryInterval;
    }

    ////////////////////////////////////////
    
    /**
       @return time formatted like `hh:mm:ss` from rawTime input
    */
    String createFormattedTime(const unsigned long& rawTime) const;

    /**
       @return time formatted like `hh:mm:ss`
    */
    String getFormattedTime() const;
    
    /**
       @return UTC time formatted like `hh:mm:ss`
    */
    String getFormattedUTCTime() const;
    
    /**
       @return date-time formatted like `10:38:21 Sun 18 Oct 2020`
    */
    String getFormattedDateTime() const;
    
    /**
       @return UTC date-time formatted like `10:38:21 Sun 18 Oct 2020`
    */
    String getFormattedUTCDateTime() const;

    ////////////////////////////////////////

    /**
       @return UTC time in seconds since Jan. 1, 1970
    */   
    inline unsigned long getUTCEpochTime() const 
    {
      return this->_currentEpoc +     // Epoc returned by the NTP server
             ((millis() - this->_lastUpdate + (_currentFraction / FRACTIONSPERMILLI)) / 1000); // Time since last update
    }

    ////////////////////////////////////////
   
    /**
       @return time in seconds since Jan. 1, 1970
    */
    unsigned long getEpochTime() const 
    {
      return (this->_timeOffset + this->getUTCEpochTime());
    }

    ////////////////////////////////////////
    
    /**
       @return UTC time in milliseconds since Jan. 1, 1970
    */
    unsigned long long getUTCEpochMillis();

    /**
       @return time in milliseconds since Jan. 1, 1970
    */
    unsigned long long getEpochMillis();

    ////////////////////////////////////////

    /**
       Stops the underlying UDP client
    */
    void end() 
    {
      this->_udp->stop();

      this->_udpSetup = false;
    }
};

#endif    // NTPCLIENT_GENERIC_HPP
