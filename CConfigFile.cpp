/*
 * CConfigFile.cpp
 *
 *  Created on: Nov 6, 2018
 *      Author: ominenko
 */

#include "CConfigFile.h"

CConfigFile::CConfigFile(ESP8266WebServer &server) :
    server(server) {
  server.on("/ConfigSave", std::bind(&CConfigFile::onSave, this));
  server.on("/ConfigLoad", std::bind(&CConfigFile::onLoad, this));
}
;

void CConfigFile::factoryReset() {
  Serial.println(__FUNCTION__);
  StaticJsonDocument<1024> doc;
  for (auto item : items) {
    JsonObject root = doc.to<JsonObject>();
    //item.handler.getDefault(root);
    save(item);
  }
}

bool CConfigFile::load(const initList_t &item) {
  Serial.print("load ");
  Serial.println(item.filename);
  File configFile = SPIFFS.open(item.filename, "r");
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
  JsonObject root = doc.as<JsonObject>();
  return item.handler.deSerialize(root);
}

bool CConfigFile::save(const initList_t &item) {
  StaticJsonDocument<1024> doc;
  JsonObject root = doc.to<JsonObject>();
  if (item.handler.serialize(root)) {
    return false;
  }
  Serial.print("save ");
  Serial.println(item.filename);
  File configFile = SPIFFS.open(item.filename, "w");
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
    if (load(item)) {
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
