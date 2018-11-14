/*
 * CMainConfig.cpp
 *
 *  Created on: Nov 17, 2017
 *      Author: ominenko
 */

#include "CMainConfig.h"

bool CMainConfig::serialize(JsonObject& root) const {
  root["heat_mode"] = static_cast<uint8_t>(heat_mode_);
  root["term_vacation"] = term_vacation_;
  root["term_night"] = term_night_;
  root["term_day"] = term_day_;
  root["term_max"] = term_max_;
  return true;
}

bool CMainConfig::deSerialize(const JsonObject& root) {
  heat_mode_ = static_cast<heat_mode_t>(root["heat_mode"].as<uint8_t>());
  term_vacation_ = root["term_vacation"];
  term_night_ = root["term_night"];
  term_day_ = root["term_day"];
  return true;
}





