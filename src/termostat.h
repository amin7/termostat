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

#include <Wire.h> // must be included here so that Arduino library object file references work
#include <pgmspace.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

#include <libs/NTPtime.h>

#include "DHTesp.h"

#include "./libs/CMQTT.h"
#include <libs/misk.h>
#include "./libs/wifiHandle.h"
#include <TimeLib.h>
#include "./libs/Timezone.h"
#include <libs/logs.h>
#include <libs/CConfig.h>
#include <libs/CADC_filter.h>

#define SERIAL_BAUND 115200
constexpr auto DEVICE_NAME = "TERMOSTAT";
constexpr auto SERVER_PORT_WEB = 80;
constexpr auto SYSTEM_CONFIG_FILE = "/www/config/config.json";
constexpr auto TERMOSTAT_CONFIG_FILE = "/www/config/termostat.json";
constexpr auto TERMOSTAT_MAX_TEMPERATURE = 40;

constexpr auto RelayPin = D6;
constexpr auto DHTPin = D4;
constexpr auto TermistorPin = A0;

