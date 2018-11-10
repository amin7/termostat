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
#include "CPresets.h"

class CMainConfig: public CPItem {
  typedef enum {
    mode_off = 0,
    mode_vacation,
    mode_night,
    mode_day,
    mode_auto
  } heat_mode_t;
  heat_mode_t heat_mode_;
  float term_vacation;
  float term_night;
  float term_day;
  const float term_max = 40;
public:
  virtual bool serialize(JsonObject& root) const override;
  virtual bool deSerialize(const JsonObject& root) override;
};

#endif /* CMAINCONFIG_H_ */
