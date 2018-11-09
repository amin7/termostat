/*
 * CConfigFile.cpp
 *
 *  Created on: Nov 6, 2018
 *      Author: ominenko
 */

#include "CConfigFile.h"

void CConfigFile::factoryReset() {
  Serial.println(__FUNCTION__);
  StaticJsonDocument<1024> doc;
  for (auto item : items) {
    Serial.println(item.first);
    auto err = deserializeJson(doc, item.second.first);
    if (err) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(err.c_str());
      return;
    }
    serializeJsonPretty(doc, Serial);
    JsonObject root = doc.as<JsonObject>();
    item.second.second->deSerialize(root);
    save(item.first, *item.second.second);
  }
}

bool CConfigFile::load(const String &name, CPItem &handler) {
  Serial.print("load ");
  auto filename = getFileName(name);
  Serial.println(filename);
  File configFile = SPIFFS.open(filename, "r");
  if (!configFile) {
    Serial.println(F("Failed to open config file"));
    return false;
  }
  StaticJsonDocument<1024> doc;
  auto err = deserializeJson(doc, configFile);
  if (err) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(err.c_str());
    return false;
  }
  serializeJsonPretty(doc, Serial);
  JsonObject root = doc.as<JsonObject>();
  return handler.deSerialize(root);
}

bool CConfigFile::save(const String &name, CPItem &handler) {
  StaticJsonDocument<1024> doc;
  JsonObject root = doc.to<JsonObject>();
  if (false == handler.serialize(root)) {
    return false;
  }
  Serial.print("save ");
  auto filename = getFileName(name);
  Serial.println(filename);
  File configFile = SPIFFS.open(filename, "w");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return false;
  }
  serializeJson(doc, configFile);
  return true;
}

void CConfigFile::begin() {
  bool result = SPIFFS.begin();
  Serial.print("SPIFFS opened: ");
  Serial.println(result);
  if (!result) {
    return;
  }
  bool err = false;
  for (auto item : items) {
    if (false == load(item.first, *item.second.second)) {
      err = true;
      break;
    }
  }
  if (err)
    factoryReset();
}
  
void CConfigFile::info() {
  Serial.println("FSInfo");
  FSInfo fsInfo;
  SPIFFS.info(fsInfo);
  Serial.print("totalBytes=");
  Serial.println(fsInfo.totalBytes);
  Serial.print("usedBytes=");
  Serial.println(fsInfo.usedBytes);
  Serial.print("blockSize=");
  Serial.println(fsInfo.blockSize);
  Serial.print("pageSize=");
  Serial.println(fsInfo.pageSize);
  Serial.print("maxOpenFiles=");
  Serial.println(fsInfo.maxOpenFiles);
  Serial.print("maxPathLength=");
  Serial.println(fsInfo.maxPathLength);
}
