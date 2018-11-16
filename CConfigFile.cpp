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
  for (auto item : items_) {
    Serial.println(item.first);
    if (!item.second.defvalue) {
      Serial.println("no init file,use from class def");
      continue;
    }
    auto err = deserializeJson(doc, item.second.defvalue);
    if (err) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(err.c_str());
      Serial.println(item.second.defvalue);
      return;
    }
    serializeJsonPretty(doc, Serial);
    Serial.println();
    JsonObject root = doc.as<JsonObject>();
    item.second.handler->deSerialize(root);
    if (item.second.file_name)
      save(item.second.file_name, *item.second.handler);
  }
}

bool CConfigFile::load(const char *file_name, CPItem &handler) {
  Serial.print("load ");
  Serial.println(file_name);
  File configFile = SPIFFS.open(file_name, "r");
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

bool CConfigFile::save(const char *file_name, CPItem &handler) {
  Serial.print("save ");
  Serial.println(file_name);

  StaticJsonDocument<1024> doc;
  JsonObject root = doc.to<JsonObject>();
  if (false == handler.serialize(root)) {
    return false;
  }
  File configFile = SPIFFS.open(file_name, "w");
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
  for (auto item : items_) {
    if (item.second.file_name)
      if (false == load(item.second.file_name, *item.second.handler)) {
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
