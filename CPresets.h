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
#include <ArduinoJson.h>//https://github.com/bblanchon/ArduinoJson.git
						//https://bblanchon.github.io/ArduinoJson/assistant/
using namespace std ;
class CPresetItem{
	bool isActive;
public:
	bool isIsActive() const {
		return isActive;
	}
	virtual bool deSerialize(JsonObject& root);
};

class CPresetItem_byWeekDay:public CPresetItem{

};
class CPresets {
	vector<CPresetItem*> items;
public:
	CPresets();
	virtual ~CPresets();
	void reset();
	void addFromJSON(const char* json);
	void getFirstJSON(char* json);
	void getNextJSON(char* json);
	friend class presetsTest_deserialize_Test;
};

#endif /* CPRESETS_H_ */
