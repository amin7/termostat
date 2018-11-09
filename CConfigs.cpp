/*
 * CConfigs.cpp
 *
 *  Created on: Nov 9, 2018
 *      Author: ominenko
 */

#include "CConfigs.h"

extern const char* _frontend_def_preset_json_ PROGMEM;
extern const char* _frontend_def_termistor_json_ PROGMEM;

CConfigs::CConfigs(ESP8266WebServer &server) :
    server(server) {
  server.on("/ConfigSave", std::bind(&CConfigs::onSave, this));
  server.on("/ConfigLoad", std::bind(&CConfigs::onLoad, this));

  add("presets", _frontend_def_preset_json_, presets);
  add("termistor", _frontend_def_termistor_json_, termistor);
}
;

void CConfigs::onLoad() {
  Serial.println(__FUNCTION__);
  const auto name = server.arg("name");
  Serial.println(name);
  auto it = items.find(name);
  if (it == items.end()) {
    Serial.println("not found");
    server.send(404, "text/json", "");
    return;
  }

  StaticJsonDocument<1024> doc;
  JsonObject root = doc.to<JsonObject>();
  it->second.second->serialize(root);

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
  auto it = items.find(name);
  if (it == items.end()) {
    Serial.println("not found");
    server.send(404, "text/html", "");
    return;
  }

  Serial.print("plain=");
  Serial.println(server.arg("plain"));

  StaticJsonDocument<1024> doc;
  deserializeJson(doc, server.arg("plain"));
  JsonObject root = doc.as<JsonObject>();
  it->second.second->deSerialize(root);
  Serial.print("memoryUsage=");
  Serial.println(doc.memoryUsage());

  save(name, *(it->second.second));
  server.send(200, "text/html", "");
}

