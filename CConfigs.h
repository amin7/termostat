/*
 * CConfigs.h
 *
 *  Created on: Nov 9, 2018
 *      Author: ominenko
 */

#ifndef CCONFIGS_H_
#define CCONFIGS_H_
#include "CConfigFile.h"
#include "CTransformLine.h"
#include "CMainConfig.h"
#include "CPresets.h"

class CConfigs: public CConfigFile {
  ESP8266WebServer &server;
  void onLoad();
  void onSave();
public:
  CPresets presets;
  CTransformLine termistor;
  CConfigs(ESP8266WebServer &server);

};

#endif /* CCONFIGS_H_ */
