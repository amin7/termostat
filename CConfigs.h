/*
 * CConfigs.h
 *
 *  Created on: Nov 9, 2018
 *      Author: ominenko
 */

#ifndef CCONFIGS_H_
#define CCONFIGS_H_
#include <ESP8266WebServer.h>
#include "CConfigFile.h"
#include "CTransformLine.h"
#include "CMainConfig.h"
#include "CPresets.h"
#include "CStatus.h"

extern const char* _frontend_def_preset_json_ PROGMEM;
extern const char* _frontend_def_termistor_json_ PROGMEM;
extern const char* _frontend_def_main_config_json_ PROGMEM;

class CConfigs: public CConfigFile {
  ESP8266WebServer &server;
  void onLoad();
  void onSave();
  void addItems() {
    add("presets", _frontend_def_preset_json_, presets_, "/presets.json");
    add("termistor", _frontend_def_termistor_json_, termistor_, "/termistor.json");
    add("mainconfig", NULL, mainConfig_, "/mainconfig.json");
    add("status", NULL, status_, NULL);
  }
public:
  CPresets presets_;
  CTransformLine termistor_;
  CMainConfig mainConfig_;
  CStatus status_;
  CConfigs(ESP8266WebServer &server);

};

#endif /* CCONFIGS_H_ */
