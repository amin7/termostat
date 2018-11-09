/*
 * CTransformLine.cpp
 *
 *  Created on: Nov 8, 2018
 *      Author: ominenko
 */

#include "CTransformLine.h"
#include  <stdlib.h>

CTransformLine::CTransformLine() :
    result_offset(0)
{
  // TODO Auto-generated constructor stub

}
bool CTransformLine::deSerialize(const JsonObject& root) {
  result_offset = root["offset"].as<float>();
  JsonArray array = root["points"];
  adc2c.clear();
  for (JsonObject nested : array) {
    auto key = atoi(nested.begin()->key().c_str());
    auto value = nested.begin()->value().as<float>();
    adc2c.insert( { key, value });
  }
  return true;
}

bool CTransformLine::serialize(JsonObject& root) const {
  root["offset"] = result_offset;
  JsonArray array = root.createNestedArray("points");
  for (auto& point : adc2c) {
    JsonObject nested = array.createNestedObject();
    char key[10];
    sprintf(key, "%u", point.first);
    nested[key] = point.second;
  }
  return true;
}
float CTransformLine::convert(const uint8_t adc) {
  std::pair<const uint8_t, float> *beg = NULL, *end = NULL;
  for (auto& point : adc2c) {
    if (adc == point.first) {
      return point.second + result_offset;
    }
    beg = end;
    end = &point;
    if (adc < point.first) { //over range
      break;
    }
  }
  if (!beg && end) { //les range
    auto it = adc2c.begin();
    beg = &*it;
    it++;
    end = &*it;
  }
  if (beg && end) {
    const float k = (end->second - beg->second) / (end->first - beg->first);
    return (adc - beg->first) * k + beg->second + result_offset;
  }

  return 0;
}
