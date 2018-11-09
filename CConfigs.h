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

class CConfigs: public CConfigFile {
public:
  CPresetsConfig presets;
  CTransformLine termistor;
  //CMainConfig mainConfig(server);
  CConfigs(ESP8266WebServer &server);
};

#endif /* CCONFIGS_H_ */
