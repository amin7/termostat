/*
 * termostat.h
 *
 *  Created on: May 4, 2021
 *      Author: ominenko
 */

#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <LittleFS.h>
#include <LeifHomieLib.h>

#include <Wire.h> // must be included here so that Arduino library object file references work
#include <pgmspace.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

#include <NTPtime.h>

#include <DHTesp.h>

#include <misk.h>
#include <wifiHandle.h>
#include <TimeLib.h>
#include <Timezone.h>
#include <logs.h>
#include <CADC_filter.h>

#define SERIAL_BAUND 115200
constexpr auto DEVICE_NAME = "TERMOSTAT";
constexpr auto SERVER_PORT_WEB = 80;
constexpr auto TERMOSTAT_MAX_TEMPERATURE = 40;

constexpr auto RelayPin = D6;
constexpr auto DHTPin = D4;
constexpr auto TermistorPin = A0;

