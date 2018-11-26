/*
 * NTPtime.h
 *
 *  Created on: 4 ???. 2017 ?.
 *      Author: User
 */

#ifndef CLOCK_NTPTIME_H_
#define CLOCK_NTPTIME_H_
//#define DUBUG_CLOCK_NTPTIME

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "../acus/CFilter.h"
typedef void (*tNTPtimeSync)(time_t);

class NTPtime:public CSubjectPeriodic<time_t> {
private:
    const static uint32_t refreshPeriod = 24*60 * 60 * 1000;          // one hour
    const static uint32_t reRefreshPeriod = 5*60l * 1000l;     // 10 sec

    IPAddress timeServerIP; // time.nist.gov NTP server address
    const char *ntpServerName = "time.nist.gov";

    const static int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

  byte packetBuffer[NTP_PACKET_SIZE]; // buffer to hold incoming packets

  const static unsigned int localPort =
      2390; // local port to listen for UDP packets
  WiFiUDP udp;
  int32 parceAsEpoch();
  int sendNTPpacket();
  bool initServerIP();
  virtual uint32_t getTimeInMs(){     return millis();  }
public:
    NTPtime(uint32_t period = refreshPeriod):CSubjectPeriodic<time_t>(period,reRefreshPeriod){};
    void init();
    virtual bool readValue(time_t &);
};

#endif /* CLOCK_NTPTIME_H_ */
