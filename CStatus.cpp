/*
 * CStatus.cpp
 *
 *  Created on: 11 ????. 2018 ?.
 *      Author: User
 */

#include "CStatus.h"
#include "./libs/TimeLib.h"
#include <math.h>

extern time_t get_local_time();
extern void set_local_time(time_t time);
extern const char* DEVICE_NAME;
extern const char* DEVICE_VERSION;
bool CStatus::deSerialize(const JsonObject& root) {
  if (root.containsKey("time")) {
    const auto time = root["time"].as<time_t>();
    set_local_time(time);
  }
  return true;
}
bool CStatus::serialize(JsonObject& root) const {
  if (!isnan(air_term_)) {
    root["air_term"] = air_term_;
  }
  if (!isnan(air_humm_)) {
    root["air_humm"] = air_humm_;
  }
  root["floor_term"] = floor_term_;
  root["adc_"] = adc_;
  root["desired_temperature"] = desired_temperature_;
  root["time_status"] = static_cast<int8_t>(timeStatus());
  root["time"] = now(); //to ms
  root["device_name"] = DEVICE_NAME;
  root["device_version"] = DEVICE_VERSION;
  return true;
}
