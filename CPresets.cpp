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
  JsonObject data = root["data"];
  if (weekDay.deSerialize(data["weekDay"]))
    return false;
  if (hours.deSerialize(data["hours"]))
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

}


#ifndef TEST
/***
 *
 */

void CPresetsConfig::onSave() {
  Serial.println(__FUNCTION__);
  Serial.print("Payload=");
  Serial.println(server.arg("plain"));
}
void CPresetsConfig::onLoad() {
  Serial.println(__FUNCTION__);
  StaticJsonDocument<512> doc;
  JsonObject root = doc.to<JsonObject>();
  serialize(root);
  Serial.print("memoryUsage=");
  auto memuse = doc.memoryUsage();
  Serial.println(memuse);
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
