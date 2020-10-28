/****************************************************************************************************************************
  NTPClient_Generic.h
 
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
 
#pragma once

#include "Arduino.h"

#include <TimeLib.h>    // https://github.com/PaulStoffregen/Time

#include <Udp.h>

#include "NTPClient_Generic_Debug.h"

#define SECS_IN_DAY               (86400L)
#define SECS_IN_HR                (3600L)
#define SECS_IN_MIN               (60L)


#define SEVENTYYEARS              (2208988800UL)
#define FRACTIONSPERMILLI         (4294967UL)
#define NTP_PACKET_SIZE           48
#define NTP_DEFAULT_LOCAL_PORT    1337

#define NTP_SEVER_PORT            123

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
    NTPClient(UDP& udp, long timeOffset = 0);
    NTPClient(UDP& udp, const char* poolServerName, long timeOffset = 0, unsigned long updateInterval = 60000);
    NTPClient(UDP& udp, IPAddress poolServerIP, long timeOffset = 0, unsigned long updateInterval = 60000);

    /**
       Set time server name

       @param poolServerName
    */
    void setPoolServerName(const char* poolServerName) 
    {
      this->_poolServerName = poolServerName;
    }
   
    /**
       Get time server name

       @param poolServerName
    */
    String getPoolServerName(void)
    {
      return String(this->_poolServerName);
    }
    
    ///////////////////////////////
    
    /**
       Set time server IP

       @param poolServerIP
    */
    void setPoolServerIP(const IPAddress poolServerIP)
    {
      this->_poolServerIP = poolServerIP;
    }
    
    /**
       Get time server IP. Use only after setPoolServerIP()

       @param poolServerIP
    */
    IPAddress getPoolServerIP(void)
    {
      return (this->_poolServerIP);
    }

    /**
       Starts the underlying UDP client with the specified local port
    */
    void begin(int port = NTP_DEFAULT_LOCAL_PORT);

    /**
       This should be called in the main loop of your application. By default an update from the NTP Server is only
       made every 60 seconds. This can be configured in the NTPClient constructor.

       @return true on success, false on failure
    */
    bool update();

    /**
       Has the time ever been sucessfully updated

    */
    bool updated() 
    {
      return (this->_currentEpoc != 0);
    }

    /**
       Register a callback function for when the time gets updated

    */
    void setUpdateCallback(NTPUpdateCallbackFunction f) 
    {
      _updateCallback = f;
    }

    /**
       This will force the update from the NTP Server.
       This can block for a full second
       @return true on success, false on failure
    */
    bool forceUpdate();
    
    int getUTCYear() const 
    {
      return ( year(this->getUTCEpochTime()) );      // Year, 20xy
    }

    String getUTCMonthStr() const 
    {
      return ( monthShortStr(month(this->getUTCEpochTime())) );      // Month, 1-12
    }

    int getUTCMonth() const 
    {
      return ( month(this->getUTCEpochTime()) );      // Month, 1-12
    }

    String getUTCDoW() const 
    {
      return ( dayShortStr(weekday(this->getUTCEpochTime())) );        // Day of Week, Sun-Mon-..-Sat
    }

    int getUTCDay() const 
    {
      return ( day(this->getUTCEpochTime()) );        // Day of Month, 1-31
    }

    int getUTCHours() const 
    {
      return ( hour(this->getUTCEpochTime()) );       // Hour, 0-23
    }

    int getUTCMinutes() const 
    {
      return ( minute(this->getUTCEpochTime()) );     // Min, 0-59
    }

    int getUTCSeconds() const 
    {
      return ( second(this->getUTCEpochTime()) );     // Sec, 0-59
    }

    // With leading 0
    String getUTCStrHours() const 
    {
      unsigned long tempo = this->getUTCHours();

      return ( tempo < 10 ? "0" + String(tempo) : String(tempo) );       // Hour, 00-23
    }

    // With leading 0
    String getUTCStrMinutes() const 
    {
      unsigned long tempo = this->getUTCMinutes();
      
      return ( tempo < 10 ? "0" + String(tempo) : String(tempo) );      // Min, 00-59
    }

    // With leading 0
    String getUTCStrSeconds() const 
    {
      unsigned long tempo = this->getUTCSeconds();
      
      return ( tempo < 10 ? "0" + String(tempo) : String(tempo) );      // Sec, 0-59
    }


//////////////////////////////////////////

    int getYear() const 
    {
      return ( year(this->getEpochTime()) );      // Year, 20xy
    }

    String getMonthStr() const 
    {
      return ( monthShortStr(month(this->getEpochTime())) );      // Month, 1-12
    }

    int getMonth() const 
    {
      return ( month(this->getEpochTime()) );      // Month, 1-12
    }

    String getDoW() const 
    {
      return ( dayShortStr(weekday(this->getEpochTime())) );        // Day of Week, Sun-Mon-..-Sat
    }

    int getDay() const 
    {
      return ( day(this->getEpochTime()) );        // Day of Month, 1-31
    }

    int getHours() const 
    {
      return ( hour(this->getEpochTime()) );       // Hour, 0-23
    }

    int getMinutes() const 
    {
      return ( minute(this->getEpochTime()) );     // Min, 0-59
    }

    int getSeconds() const 
    {
      return ( second(this->getEpochTime()) );     // Sec, 0-59
    }

    // With leading 0
    String getStrHours() const 
    {
      unsigned long tempo = this->getHours();

      return ( tempo < 10 ? "0" + String(tempo) : String(tempo) );       // Hour, 00-23
    }

    // With leading 0
    String getStrMinutes() const 
    {
      unsigned long tempo = this->getMinutes();
      
      return ( tempo < 10 ? "0" + String(tempo) : String(tempo) );      // Min, 00-59
    }

    // With leading 0
    String getStrSeconds() const 
    {
      unsigned long tempo = this->getSeconds();
      
      return ( tempo < 10 ? "0" + String(tempo) : String(tempo) );      // Sec, 0-59
    }
    
    /**
       Changes the time offset. Useful for changing timezones dynamically
    */
    void setTimeOffset(int timeOffset) 
    {
      this->_timeOffset     = timeOffset;
    }

    /**
       Set the update interval to another frequency. E.g. useful when the
       timeOffset should not be set in the constructor
    */
    void setUpdateInterval(unsigned long updateInterval) 
    {
      this->_updateInterval = updateInterval;
    }

    /**
       Set the retry interval to another frequency in ms
    */
    void setRetryInterval(int retryInterval) 
    {
      _retryInterval = retryInterval;
    }
    
    /**
       @return time formatted like `hh:mm:ss` from rawTime input
    */
    String createFormattedTime(unsigned long rawTime) const;

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

    /**
       @return UTC time in seconds since Jan. 1, 1970
    */   
    unsigned long getUTCEpochTime() const 
    {
      return this->_currentEpoc +     // Epoc returned by the NTP server
             ((millis() - this->_lastUpdate + (_currentFraction / FRACTIONSPERMILLI)) / 1000); // Time since last update
    }
   
    /**
       @return time in seconds since Jan. 1, 1970
    */
    unsigned long getEpochTime() const 
    {
      return (this->_timeOffset + this->getUTCEpochTime());
    }
    
    /**
       @return UTC time in milliseconds since Jan. 1, 1970
    */
    unsigned long long getUTCEpochMillis();

    /**
       @return time in milliseconds since Jan. 1, 1970
    */
    unsigned long long getEpochMillis();

    /**
       Stops the underlying UDP client
    */
    void end() 
    {
      this->_udp->stop();

      this->_udpSetup = false;
    }
};

#include "NTPClient_Generic_Impl.h"
