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

extern const char* _frontend_def_preset_json_ PROGMEM;
extern const char* _frontend_def_termistor_json_ PROGMEM;
extern const char* _frontend_def_main_config_json_ PROGMEM;

class CConfigs: public CConfigFile {
  ESP8266WebServer &server;
  void onLoad();
  void onSave();
  void addItems() {
    add("presets", _frontend_def_preset_json_, presets);
    add("termistor", _frontend_def_termistor_json_, termistor);
    add("mainconfig", _frontend_def_main_config_json_, mainConfig);

  }
public:
  CPresets presets;
  CTransformLine termistor;
  CMainConfig mainConfig;
  CConfigs(ESP8266WebServer &server);

};

#endif /* CCONFIGS_H_ */
