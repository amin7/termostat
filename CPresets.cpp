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

void CPresets::reset(){
	items.clear();
}

void CPresets::addFromJSON(const char* json){
	const size_t bufferSize = JSON_ARRAY_SIZE(7) + JSON_ARRAY_SIZE(24) + 4*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(4) + 290;
	DynamicJsonBuffer jsonBuffer(bufferSize);
	JsonObject& root = jsonBuffer.parseObject(json);
	auto item=new CPresetItem();
	items.push_back(item );
	item->deSerialize(root);
}
