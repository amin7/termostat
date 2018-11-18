/*
 * presets.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: ominenko
 */

#include "CPresets.h"
bool CPI_byWeekDay::serialize(JsonObject& root) const {
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

const CPI_byWeekDay* CPresets::find(int8_t day_of_week) const {
  for (const auto &day : items) {
    if (day.isConsis(day_of_week)) {
      return &day;
    }
  }
  return NULL;
}
bool CPresets::serialize(JsonObject& root) const {
  JsonArray array = root.createNestedArray("Presets");
  for (auto day : items) {
    JsonObject nested = array.createNestedObject();
    day.serialize(nested);
  }
  return true;
}
bool CPresets::deSerialize(const JsonObject& root) {
  JsonArray array = root["Presets"];
  items.clear();
  for (JsonObject nested : array) {
    CPI_byWeekDay item;
    if (false == item.deSerialize(nested)) {
      return false;
    }
    items.push_back(item);
  }
  return true;
}
