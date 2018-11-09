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
    CConfigFile(server), presets(server) {
  add("/presets.json", _frontend_def_preset_json_, presets);
  add("/termistor.json", _frontend_def_termistor_json_, termistor);
}
;
