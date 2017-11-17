/*
 * CMainConfig.cpp
 *
 *  Created on: Nov 17, 2017
 *      Author: ominenko
 */

#include "CMainConfig.h"
#include <FS.h>

CMainConfig::CMainConfig(ESP8266WebServer &server):presetsConfig(server),server(server),
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

bool CMainConfig::begin(){
	if(SPIFFS.begin())return 1;
	presetsConfig.begin();
	return 0;
}

	/***
	 * Resed data in file system , set configs in default value;
	 */
void CMainConfig::onFactoryReset(){
	bool result=SPIFFS.format();
	Serial.print("SPIFFS format: ");
	Serial.println(result);
	delay(1000);
}

size_t CMainConfig::printTo(Print& p) const{
	size_t sz=0;
	sz+=p.print("{");
	sz+=p.print("CMainConfig");
	sz+=p.print("}");
	return sz;
}

