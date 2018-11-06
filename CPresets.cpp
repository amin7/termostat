/*
 * presets.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: ominenko
 */

#include "CPresets.h"
bool CPI_byWeekDay::serialize(JsonObject& root) {
  weekDay.serialize(root);
  hours.serialize(root);
  return true;
}

bool CPI_byWeekDay::deSerialize(const JsonObject& root) {
  if (weekDay.deSerialize(root))
    return false;
  if (hours.deSerialize(root))
    return false;
  return true;
}
/***
 *
 */

void CPresets::init() {

}
bool CPresets::serialize(JsonObject& root) {
  JsonArray array = root.createNestedArray("Presets");
  for (auto day : items) {
    JsonObject nested = array.createNestedObject();
    day.serialize(nested);
  }
}
bool CPresets::deSerialize(const JsonObject& root) {
  JsonArray array = root["Presets"];
  items.clear();
  for (JsonObject nested : array) {
    CPI_byWeekDay item;
    item.deSerialize(nested);
    items.push_back(item);
  }
}

#ifndef TEST
/***
 *
 */

void CPresetsConfig::onSave() {
  Serial.println(__FUNCTION__);
  Serial.println(server.arg("plain"));
  StaticJsonDocument < 512 > doc;
  deserializeJson(doc, server.arg("plain"));
  Serial.print("memoryUsage=");
  Serial.println(doc.memoryUsage());
  JsonObject root = doc.as<JsonObject>();
  deSerialize(root);


}
void CPresetsConfig::onLoad() {
  Serial.println(__FUNCTION__);
  StaticJsonDocument<512> doc;
  JsonObject root = doc.to<JsonObject>();
  serialize(root);
  Serial.print("memoryUsage=");
  Serial.println(doc.memoryUsage());
  String tt;
  serializeJson(root, tt);
  server.send(200, "text/json", tt);
  Serial.println(tt);
}

CPresetsConfig::CPresetsConfig(ESP8266WebServer &server):server(server){
  server.on("/PresetSave", std::bind(&CPresetsConfig::onSave, this));
  server.on("/PresetLoad", std::bind(&CPresetsConfig::onLoad, this));
}
#endif
