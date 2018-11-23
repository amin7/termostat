/*
 * CMainConfig.cpp
 *
 *  Created on: Nov 17, 2017
 *      Author: ominenko
 */

#include "CMainConfig.h"
#include <timeLib.h>
extern time_t get_local_time();
float CMainConfig::getDesiredTemperature() {
  if (false == isOn_) {
    return 0;
  }
  const auto now = get_local_time();
  if (mode_off != in_out_mode_) {
    //check period
    switch (in_out_mode_) {
      case mode_night:
        return term_night_;
      case mode_day:
        return term_day_;
    }
  }

  if (isVacationSet_) {
    //check vacation period
  }

    //convert 1-7 (sanday=1) to 0-6 (sanday=6)
  auto day_of_week = weekday(now) - 2;
  if (-1 == day_of_week) {
    day_of_week = 6;
  }
  auto preset = presets_.find(day_of_week);
  if (preset) {
    if (preset->isInHome(hour(now) - 1)) {
      return term_day_;
    }
  }
  return term_night_;
}

bool CMainConfig::serialize(JsonObject& root) const {
  root["in_out_mode"] = static_cast<uint8_t>(in_out_mode_);
  if (mode_off != in_out_mode_) {
    root["in_out_time"] = static_cast<uint32_t>(in_out_time_) * 1000;
  }
  root["term_vacation"] = term_vacation_;
  root["term_night"] = term_night_;
  root["term_day"] = term_day_;
  root["term_max"] = term_max_;
  root["isOn"] = isOn_;
  root["isVacationSet"] = isVacationSet_;
  root["is_err_cooling"] = is_err_cooling_;
  root["term_err_cooling"] = term_err_cooling_;
  return true;
}

bool CMainConfig::deSerialize(const JsonObject& root) {
  in_out_mode_ = static_cast<in_out_mode_t>(root["in_out_mode"].as<uint8_t>());
  if (mode_off != in_out_mode_) {
    in_out_time_ = root["in_out_time"].as<uint32_t>() / 1000;
  }
  term_vacation_ = root["term_vacation"];
  term_night_ = root["term_night"];
  term_day_ = root["term_day"];
  isOn_ = root["isOn"];
  isVacationSet_ = root["isVacationSet"];
  return true;
}

