/*
 * CMainConfig.h
 *
 *  Created on: Nov 17, 2017
 *      Author: ominenko
 */

#ifndef CMAINCONFIG_H_
#define CMAINCONFIG_H_
#include <stdint.h>
#include <ArduinoJson.h>
//https://github.com/bblanchon/ArduinoJson.git
						//https://bblanchon.github.io/ArduinoJson/assistant/
#include "CPItem.h"
#include "CPresets.h"

class CMainConfig: public CPItem {
  typedef enum {
    mode_off = 0,
    mode_night,
    mode_day,
  } in_out_mode_t;

  bool isOn_ = false;
  in_out_mode_t in_out_mode_ = mode_off;
  time_t in_out_time_;
  float term_vacation_ = 16;
  time_t vocation_start_ = 0;
  time_t vocation_end_ = 0;
  float term_night_ = 18;
  float term_day_ = 24;
  const float term_max_ = 40;
  bool is_err_cooling_ = false;
  const float term_err_cooling_ = 20;
  const CPresets &presets_;
  bool isVacation(const time_t &time, float &term);
public:
  CMainConfig(const CPresets &presets) :
      presets_(presets) {
  }
  bool isOn() {
    return isOn_;
  }
  float getDesiredTemperature();
  virtual bool serialize(JsonObject& root) const override;
  virtual bool deSerialize(const JsonObject& root) override;
};

#endif /* CMAINCONFIG_H_ */
