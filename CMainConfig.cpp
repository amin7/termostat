/*
 * CMainConfig.cpp
 *
 *  Created on: Nov 17, 2017
 *      Author: ominenko
 */

#include "CMainConfig.h"
#include <FS.h>
const char* configFile PROGMEM ={"//mainconfig.json"};

CMainConfig::CMainConfig(ESP8266WebServer &_server) :
    server(_server),
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

	/***
	 * Resed data in file system , set configs in default value;
	 */
void CMainConfig::onFactoryReset(){
	bool result=SPIFFS.format();
	Serial.print("SPIFFS format: ");
	Serial.println(result);
	delay(1000);
}

bool CMainConfig::serialize(JsonObject& root) {
  return true;
}

const size_t bufferSize = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(3);
bool CMainConfig::deSerialize(const JsonObject& root) {
  root["tempAirMin"] = tempAirMin;
  root["tempAirMax"] = tempAirMax;
  root["tempFlour"] = tempFlour;
  root["tempHisteresis"] = tempHisteresis;
  root["PWM"] = PWM;
  return true;
}





