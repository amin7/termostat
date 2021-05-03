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
#ifndef TEST
	#include <ESP8266WebServer.h>
#else
#include <WString.h>
#include <Printable.h>
#endif
#include <ArduinoJson.h>//https://github.com/bblanchon/ArduinoJson.git
						//https://bblanchon.github.io/ArduinoJson/assistant/
using namespace std ;

class CPItem:public Printable{
public:
    virtual bool deSerialize(JsonObject& root)=0;
    virtual JsonObject& serialize() const=0;
    size_t printTo(Print& p) const;
    virtual ~CPItem(){};
};

class CPIIsActive:public CPItem{
	bool isActive;
public:
	bool isIsActive() const {
		return isActive;
	}
	bool deSerialize(JsonObject& root);
	JsonObject& serialize() const;
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
    bool deSerialize(JsonObject& root);
    JsonObject& serialize() const;

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
	void add(CPItem &item);
	void addFromJSON(const String  &json);
	void getFirstJSON(char* json);
	void getNextJSON(char* json);
	virtual size_t printTo(Print& p) const;
	friend class presetsTest_deserialize_Test;
};

#ifndef TEST
class CPresetsConfig:public CPresets{
ESP8266WebServer &server;
void onClear(){};
void onAdd();
public:
	CPresetsConfig(ESP8266WebServer &server);
	void begin(){};
};
#endif

#endif /* CPRESETS_H_ */
