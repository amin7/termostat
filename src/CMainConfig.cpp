/*
 * CMainConfig.cpp
 *
 *  Created on: Nov 17, 2017
 *      Author: ominenko
 */

#include "CMainConfig.h"
#include <FS.h>

const char *configFile PROGMEM = { "//mainconfig.json" };

CMainConfig::CMainConfig(ESP8266WebServer &server) :
        presetsConfig(server), server(server),
                tempAirMin(def_tempAirMin),
                tempAirMax(def_tempAirMax),
                tempFlour(def_tempFlour),
                tempHisteresis(def_tempHisteresis),
                PWM(def_PWM)
{

}

CMainConfig::~CMainConfig() {
    // TODO Auto-generated destructor stub
}

bool CMainConfig::begin() {
    auto item = new CPI_byWeekDay();
    presetsConfig.add(*item);
//	if(SPIFFS.begin())return 1;
//
//	File f = SPIFFS.open(configFile, "r");
//	if (!f) {
//	  Serial.println("no config file/ncreating");
//	  f=SPIFFS.open(configFile,"w");
//	}
//
//
//	f.close();
//	presetsConfig.begin();
    return 0;
}

