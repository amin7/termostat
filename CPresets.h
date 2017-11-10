/*
 * presets.h
 *
 *  Created on: Nov 2, 2017
 *      Author: ominenko
 */

#ifndef CPRESETS_H_
#define CPRESETS_H_
#include <stdint.h>
#include <vector>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>//https://github.com/bblanchon/ArduinoJson.git
						//https://bblanchon.github.io/ArduinoJson/assistant/
using namespace std ;
class CPresetItem:public Printable{
	bool isActive;
public:
	bool isIsActive() const {
		return isActive;
	}
	virtual bool deSerialize(JsonObject& root);
	virtual size_t printTo(Print& p) const;
};

class CPresetItem_byWeekDay:public CPresetItem{

};
class CPresets :public Printable{
	vector<CPresetItem*> items;
public:
	CPresets();
	virtual ~CPresets();
	void reset();
	void addFromJSON(const String  &json);
	void getFirstJSON(char* json);
	void getNextJSON(char* json);
	virtual size_t printTo(Print& p) const;
	friend class presetsTest_deserialize_Test;
};

class CPresetsServer:private CPresets{
ESP8266WebServer &server;
void onClear(){};
void onAdd();
public:
	CPresetsServer(ESP8266WebServer &server);
};

#endif /* CPRESETS_H_ */
