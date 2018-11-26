/*
 * CMainConfig.cpp
 *
 *  Created on: Nov 17, 2017
 *      Author: ominenko
 */

#include "CMainConfig.h"
#include "./libs/timeLib.h"
extern time_t get_local_time();
bool CMainConfig::isVacation(const time_t &time, float &term) {
  //check vacation period
  if (0 == vocation_start_ && 0 == vocation_end_) { //must be set at list one
    return false;
  }

  if (0 == vocation_start_) { //from now
    if (time <= vocation_end_) {
      term = term_vacation_;
      return true;
    }
    vocation_end_ = 0; //to remova call again
    return false;
  }

  if (time < vocation_start_) { //not time yet
    return false;
  }
  if (time <= vocation_end_) {
    term = term_vacation_;
    return true;
  }
  //time pass
  vocation_end_ = 0;
  vocation_start_ = 0;
  return false;
}
float CMainConfig::getDesiredTemperature() {
  if (false == isOn_) {
    return 0;
  }

  const auto time = now();
  if (mode_off != in_out_mode_) {
    if (time > (in_out_time_ + 59 * 60)) { //till end of hour
      in_out_mode_ = mode_off;
      }
    //check period
    switch (in_out_mode_) {
      case mode_night:
        return term_night_;
      case mode_day:
        return term_day_;
    }
  }
  float tmp = 0;
  if (isVacation(time, tmp)) {
    return tmp;
  }

  const auto local_time = get_local_time();
    //convert 1-7 (sanday=1) to 0-6 (sanday=6)
  auto day_of_week = weekday(local_time) - 2;
  if (-1 == day_of_week) {
    day_of_week = 6;
  }
  auto preset = presets_.find(day_of_week);
  if (preset) {
    if (preset->isInHome(hour(local_time))) {
      return term_day_;
    }
  }
  return term_night_;
}

bool CMainConfig::serialize(JsonObject& root) const {
  switch (in_out_mode_) {
    case mode_day:
      root["mode_in"] = in_out_time_;
      break;
    case mode_night:
      root["mode_out"] = in_out_time_;
      break;
  }

  root["term_vacation"] = term_vacation_;
  root["term_night"] = term_night_;
  root["term_day"] = term_day_;
  root["term_max"] = term_max_;
  root["isOn"] = isOn_;

  root["vocation_start"] = vocation_start_;
  root["vocation_end"] = vocation_end_;

//  root["is_err_cooling"] = is_err_cooling_;
//  root["term_err_cooling"] = term_err_cooling_;
  return true;
}

bool CMainConfig::deSerialize(const JsonObject& root) {
  in_out_mode_ = mode_off;
  if (root.containsKey("mode_in")) {
    in_out_mode_ = mode_day;
    in_out_time_ = root["mode_in"].as<time_t>();
  }
  if (root.containsKey("mode_out")) {
    in_out_mode_ = mode_night;
    in_out_time_ = root["mode_out"].as<time_t>();
  }

  vocation_start_ = root["vocation_start"].as<time_t>();
  vocation_end_ = root["vocation_end"].as<time_t>();

  term_vacation_ = root["term_vacation"];
  term_night_ = root["term_night"];
  term_day_ = root["term_day"];
  isOn_ = root["isOn"];
  return true;
}

