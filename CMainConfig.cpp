/*
 * CMainConfig.cpp
 *
 *  Created on: Nov 17, 2017
 *      Author: ominenko
 */

#include "CMainConfig.h"
#include <FS.h>

const char* configFile PROGMEM ={"//mainconfig.json"};

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
	auto item=new CPI_byWeekDay();
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

	/***
	 * Resed data in file system , set configs in default value;
	 */
void CMainConfig::onFactoryReset(){
	bool result=SPIFFS.format();
	Serial.print("SPIFFS format: ");
	Serial.println(result);
	delay(1000);
}
const size_t bufferSize = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(3);
JsonObject& CMainConfig::serialize()const{
	DynamicJsonBuffer jsonBuffer(bufferSize);
	JsonObject& root = jsonBuffer.createObject();
	root["tempAirMin"]=tempAirMin;
	root["tempAirMax"]=tempAirMax;
	root["tempFlour"]=tempFlour;
	root["tempHisteresis"]=tempHisteresis;
	root["PWM"]=PWM;
	return root;
}

size_t CMainConfig::printTo(Print& p) const{
	size_t sz=0;
	sz+=p.print("{");
	sz+=p.print("\"CMainConfig\":");
	sz+=serialize().prettyPrintTo(p);

	sz+=p.print("}");
	return sz;
}

