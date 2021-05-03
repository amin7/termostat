/*
 * presets.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: ominenko
 */

#include "CPresets.h"
/***
 *
 */
size_t CPItem::printTo(Print& p) const {
	return serialize().prettyPrintTo(p);
}
/***
 *
 */

bool CPIIsActive::deSerialize(JsonObject& root){
	//const size_t bufferSizeIn = JSON_OBJECT_SIZE(1) + 20;
	isActive=root["isActive"];
	return 0;
}

JsonObject& CPIIsActive::serialize() const{
	const size_t bufferSize = JSON_OBJECT_SIZE(1);
	DynamicJsonBuffer jsonBuffer(bufferSize);
	JsonObject& root = jsonBuffer.createObject();
	root["isActive"]=isActive;
	return root;
}


/***
 *
 */
void CPI_BitField::setBit(uint8_t index,bool value){
    if(size<index)
        return;
    const uint32_t mask=((uint32_t)1)<<index;
    if(value)
        bitField|=mask;
    else
        bitField&=~mask;
}

bool CPI_BitField::deSerialize(JsonObject& root){
    JsonArray& data_hours_Value = root["Value"];
    for(uint8_t index=0;index<size;index++){
        setBit(index,data_hours_Value[index]);
    }
    return 0;
}

JsonObject& CPI_BitField::serialize() const{
	const size_t bufferSize = JSON_ARRAY_SIZE(size)+ JSON_OBJECT_SIZE(1);
	DynamicJsonBuffer jsonBuffer(bufferSize);
	JsonObject& root = jsonBuffer.createObject();

	JsonArray& bits = root.createNestedArray("bits");
    for(uint8_t index=0;index<size;index++){
    	bits.add(isSet(index));
    }
	return root;
}

/***
 *
 */
bool CPI_byWeekDay::deSerialize(JsonObject& root){
    if(CPIIsActive::deSerialize(root))return 1;
    JsonObject& data = root["data"];
    if(weekDay.deSerialize(data["weekDay"]))return 1;
    if(hours.deSerialize(data["hours"]))return 1;
    return 0;
}
size_t CPI_byWeekDay::printTo(Print& p) const{
    size_t sz=0;
    sz+=p.print("{");
    sz+=CPIIsActive::printTo(p);
    sz+=weekDay.printTo(p);
    sz+=hours.printTo(p);
    sz+=p.print("}");
    return sz;
}
/***
 *
 */

void CPresets::clear(){
	items.clear();
}

void CPresets::add(CPItem &item){
	items.push_back(&item);
}

void CPresets::addFromJSON(const String  &json){
	Serial.println(json);
	const size_t bufferSize = JSON_ARRAY_SIZE(7) + JSON_ARRAY_SIZE(24) + 4*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(4) + 290;
	DynamicJsonBuffer jsonBuffer(bufferSize);
	JsonObject& root = jsonBuffer.parseObject(json);
	auto item=new CPI_byWeekDay();
	items.push_back(item );
	item->deSerialize(root);
	Serial.println(*this);

}
size_t CPresets::printTo(Print& p) const{
	size_t sz=0;
	sz+=p.print("{");
	sz+=p.print("sz=");
	sz+=p.print(items.size());
	sz+=p.print("[");
	for(auto item:items){
		sz+=p.print(*item);
	}
	sz+=p.print("]");
	sz+=p.print("}");
	return sz;
}
#ifndef TEST
/***
 *
 */

void CPresetsConfig::onAdd(){
	Serial.println(__FUNCTION__);
	addFromJSON(server.arg("data"));


}
CPresetsConfig::CPresetsConfig(ESP8266WebServer &server):server(server){
	server.on("/PresetClear", std::bind(&CPresetsConfig::onClear, this));
	server.on("/PresetAdd", std::bind(&CPresetsConfig::onAdd, this));
}
#endif
