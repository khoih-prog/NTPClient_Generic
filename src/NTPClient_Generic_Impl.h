/****************************************************************************************************************************
  NTPClient_Generic_Impl.h
 
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

NTPClient::NTPClient(UDP& udp, long timeOffset)
{
  this->_udp            = &udp;
  this->_timeOffset     = timeOffset;
}

NTPClient::NTPClient(UDP& udp, const char* poolServerName, long timeOffset, unsigned long updateInterval)
{
  this->_udp            = &udp;
  this->_timeOffset     = timeOffset;
  this->_poolServerName = poolServerName;
  this->_updateInterval = updateInterval;
}

NTPClient::NTPClient(UDP& udp, IPAddress poolServerIP, long timeOffset, unsigned long updateInterval)
{
  this->_udp            = &udp;
  this->_timeOffset     = timeOffset;
  this->_poolServerIP   = poolServerIP;
  this->_poolServerName = NULL;
  this->_updateInterval = updateInterval;
}

void NTPClient::begin(int port)
{
  this->_port = port;

  this->_udp->begin(this->_port);

  this->_udpSetup = true;
}

bool NTPClient::checkResponse()
{

  if (this->_udp->parsePacket())
  {
    this->_lastUpdate = millis();
    this->_lastRequest = 0; // no outstanding request
    this->_udp->read(this->_packetBuffer, NTP_PACKET_SIZE);

    unsigned long highWord = word(this->_packetBuffer[40], this->_packetBuffer[41]);
    unsigned long lowWord = word(this->_packetBuffer[42], this->_packetBuffer[43]);
    
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;

    this->_currentEpoc = secsSince1900 - SEVENTYYEARS;

    highWord = word(this->_packetBuffer[44], this->_packetBuffer[45]);
    lowWord = word(this->_packetBuffer[46], this->_packetBuffer[47]);
    this->_currentFraction = highWord << 16 | lowWord;

    // if the user has set a callback function for when the time is updated, call it
    if (_updateCallback)
    {
      _updateCallback(this);
    }

    return true;
  }
  else
  {
    return false;
  }
}

bool NTPClient::forceUpdate()
{
  NTP_LOGDEBUG("Update from NTP Server");

  // flush any existing packets
  while (this->_udp->parsePacket() != 0)
    this->_udp->flush();

  this->sendNTPPacket();

  // Wait till data is there or timeout...
  byte timeout  = 0;
  bool cb       = 0;

  do
  {
    delay ( 10 );
    cb = this->checkResponse();

    if (timeout > 100)
      return false; // timeout after 1000 ms

    timeout++;
  } while (cb == false);

  return true;
}

bool NTPClient::update()
{
  bool updated = false;
  unsigned long now = millis();

  if ( ((_lastRequest == 0) && (_lastUpdate == 0))                              // Never requested or updated
       || ((_lastRequest == 0) && ((now - _lastUpdate) >= _updateInterval))     // Update after _updateInterval
       || ((_lastRequest != 0) && ((now - _lastRequest) > _retryInterval)) )    // Update if there was no response to the request
  {
    // setup the UDP client if needed
    if (!this->_udpSetup) 
    {
      this->begin();
    }

    this->sendNTPPacket();
  }

  if (_lastRequest) 
  {
    updated = checkResponse();
  }

  return updated;
}

/////////////////////////////

unsigned long long NTPClient::getUTCEpochMillis() 
{
  unsigned long long epoch;

  epoch  = this->_currentEpoc * 1000;                   // last time returned via server in millis
  epoch += this->_currentFraction / FRACTIONSPERMILLI;  // add the fraction from the server
  epoch += millis() - this->_lastUpdate;          // add the millis that have passed since the last update

  return epoch;
}

unsigned long long NTPClient::getEpochMillis() 
{
  unsigned long long epoch;
  
  epoch = (this->_timeOffset * 1000) + getUTCEpochMillis();

  return epoch;
}

/////////////////////////////

String NTPClient::createFormattedTime(unsigned long rawTime) const 
{
  unsigned long tempo   = hour(rawTime);
  String hoursStr       = tempo < 10 ? "0" + String(tempo) : String(tempo);

  tempo   = minute(rawTime);
  String minuteStr      = tempo < 10 ? "0" + String(tempo) : String(tempo);

  tempo   = second(rawTime);
  String secondStr      = tempo < 10 ? "0" + String(tempo) : String(tempo);

  return hoursStr + ":" + minuteStr + ":" + secondStr;
}

String NTPClient::getFormattedTime() const 
{
  return createFormattedTime(this->getEpochTime());
}

String NTPClient::getFormattedUTCTime() const 
{
  return createFormattedTime(this->getUTCEpochTime());
}

String NTPClient::getFormattedDateTime() const 
{
  char buf[26];
  char m[4];    // temporary storage for month string (DateStrings.cpp uses shared buffer)
   
  time_t t = this->getEpochTime();
  
  strcpy(m, monthShortStr(month(t)));
  sprintf(buf, "%.2d:%.2d:%.2d %s %.2d %s %d", hour(t), minute(t), second(t), 
                                    dayShortStr(weekday(t)), day(t), m, year(t));
  
  return String(buf);
}

String NTPClient::getFormattedUTCDateTime() const 
{
  char buf[26];
  char m[4];    // temporary storage for month string (DateStrings.cpp uses shared buffer)
    
  time_t t = this->getEpochTime() - _timeOffset;
  
  strcpy(m, monthShortStr(month(t)));
  sprintf(buf, "%.2d:%.2d:%.2d %s %.2d %s %d", hour(t), minute(t), second(t), 
                                    dayShortStr(weekday(t)), day(t), m, year(t));
  
  return String(buf);
}

/////////////////////////////

void NTPClient::sendNTPPacket() 
{
  // set all bytes in the buffer to 0
  memset(this->_packetBuffer, 0, NTP_PACKET_SIZE);
  
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  this->_packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  this->_packetBuffer[1] = 0;     // Stratum, or type of clock
  this->_packetBuffer[2] = 6;     // Polling Interval
  this->_packetBuffer[3] = 0xEC;  // Peer Clock Precision
  
  // 8 bytes of zero for Root Delay & Root Dispersion
  this->_packetBuffer[12]  = 49;
  this->_packetBuffer[13]  = 0x4E;
  this->_packetBuffer[14]  = 49;
  this->_packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  if  (this->_poolServerName) 
  {
    this->_udp->beginPacket(this->_poolServerName, NTP_SEVER_PORT);
  } 
  else 
  {
    this->_udp->beginPacket(this->_poolServerIP, NTP_SEVER_PORT);
  }
  
  this->_udp->write(this->_packetBuffer, NTP_PACKET_SIZE);
  this->_udp->endPacket();

  this->_lastRequest = millis();
}
