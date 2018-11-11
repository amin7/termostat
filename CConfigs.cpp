/*
 * CConfigs.cpp
 *
 *  Created on: Nov 9, 2018
 *      Author: ominenko
 */

#include "CConfigs.h"

CConfigs::CConfigs(ESP8266WebServer &server) :
    server(server) {
  server.on("/ConfigSave", std::bind(&CConfigs::onSave, this));
  server.on("/ConfigLoad", std::bind(&CConfigs::onLoad, this));
  addItems();
}
;

void CConfigs::onLoad() {
  Serial.println(__FUNCTION__);
  const auto name = server.arg("name");
  Serial.println(name);
  auto it = items_.find(name);
  if (it == items_.end()) {
    Serial.println("not found");
    server.send(404, "text/json", "");
    return;
  }

  StaticJsonDocument<1024> doc;
  JsonObject root = doc.to<JsonObject>();
  it->second.handler->serialize(root);

  Serial.print("memoryUsage=");
  Serial.println(doc.memoryUsage());
  String tt;
  serializeJson(root, tt);
  server.send(200, "text/json", tt);
  Serial.println(tt);
}

void CConfigs::onSave() {
  Serial.println(__FUNCTION__);
  const auto name = server.arg("name");
  Serial.println(name);
  auto it = items_.find(name);
  if (it == items_.end()) {
    Serial.println("not found");
    server.send(404, "text/html", "");
    return;
  }

  Serial.print("plain=");
  Serial.println(server.arg("plain"));

  StaticJsonDocument<1024> doc;
  deserializeJson(doc, server.arg("plain"));
  JsonObject root = doc.as<JsonObject>();
  it->second.handler->deSerialize(root);
  Serial.print("memoryUsage=");
  Serial.println(doc.memoryUsage());
  if (it->second.file_name)
    save(it->second.file_name, *(it->second.handler));
  server.send(200, "text/html", "");
}

