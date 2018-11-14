/*
 * CStatus.cpp
 *
 *  Created on: 11 ????. 2018 ?.
 *      Author: User
 */

#include "CStatus.h"
#include <TimeLib.h>
#include <math.h>

extern time_t get_local_time();

bool CStatus::deSerialize(const JsonObject& root) {
  //not expected
  return false;
}
bool CStatus::serialize(JsonObject& root) const {
  if (!isnan(air_term_)) {
    root["air_term"] = air_term_;
  }
  if (!isnan(air_humm_)) {
    root["air_humm"] = air_humm_;
  }
  root["floor_term"] = floor_term_;
  root["desired_temperature"] = desired_temperature_;
  root["time_status"] = timeStatus();
  root["time"] = get_local_time(); //to ms
  return true;
}
