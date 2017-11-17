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

class CPItem:public Printable{
public:
    virtual bool deSerialize(JsonObject& root)=0;
    virtual ~CPItem(){};
};

class CPIIsActive:public CPItem{
	bool isActive;
public:
	bool isIsActive() const {
		return isActive;
	}
	virtual bool deSerialize(JsonObject& root);
	virtual size_t printTo(Print& p) const;
};

class CPI_BitField:public CPItem{
    uint32_t bitField;
    const uint8_t size;
public:
    CPI_BitField(uint8_t size):bitField(0),size(size){};
    void setBit(uint8_t index,bool value);
    bool isSet(uint8_t index)const {  return (bitField&(((uint32_t)1)<<index))?true:false;}
    uint32_t getBitField() const {    return bitField;   }
    void setBitField(uint32_t bitField) {   this->bitField = bitField; }
    virtual bool deSerialize(JsonObject& root);
    virtual size_t printTo(Print& p) const;
};

class CPI_byWeekDay:public CPIIsActive{
public:
    CPI_BitField weekDay;
    CPI_BitField hours;
    CPI_byWeekDay(): weekDay(7),hours(24){};
    virtual bool deSerialize(JsonObject& root);
    virtual size_t printTo(Print& p) const;
};
class CPresets :public Printable{
	vector<CPItem*> items;
public:
	CPresets(){};
	virtual ~CPresets(){};
	void clear();
	void addFromJSON(const String  &json);
	void getFirstJSON(char* json);
	void getNextJSON(char* json);
	virtual size_t printTo(Print& p) const;
	friend class presetsTest_deserialize_Test;
};

class CPresetsConfig:private CPresets{
ESP8266WebServer &server;
void onClear(){};
void onAdd();
public:
	CPresetsConfig(ESP8266WebServer &server);
	void begin(){};
};

#endif /* CPRESETS_H_ */
