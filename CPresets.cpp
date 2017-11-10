/*
 * presets.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: ominenko
 */

#include "CPresets.h"

CPresets::CPresets() {
	// TODO Auto-generated constructor stub

}

CPresets::~CPresets() {
	// TODO Auto-generated destructor stub
}

bool CPresetItem::deSerialize(JsonObject& root){
	isActive=root["isActive"];
	return 0;
}

size_t CPresetItem::printTo(Print& p) const{
	size_t sz=0;
	sz+=p.print("{");
	sz+=p.print("isActive=");
	sz+=p.print(isActive);
	sz+=p.print("}");
	return sz;
}
/***
 *
 */

void CPresets::reset(){
	items.clear();
}

void CPresets::addFromJSON(const String  &json){
	Serial.println(json);
	const size_t bufferSize = JSON_ARRAY_SIZE(7) + JSON_ARRAY_SIZE(24) + 4*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(4) + 290;
	DynamicJsonBuffer jsonBuffer(bufferSize);
	JsonObject& root = jsonBuffer.parseObject(json);
	auto item=new CPresetItem();
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
/***
 *
 */

void CPresetsServer::onAdd(){
	Serial.println(__FUNCTION__);
	addFromJSON(server.arg("data"));


}
CPresetsServer::CPresetsServer(ESP8266WebServer &server):server(server){
	server.on("/PresetClear", std::bind(&CPresetsServer::onClear, this));
	server.on("/PresetAdd", std::bind(&CPresetsServer::onAdd, this));
}
