/*
 * CConfigFile.h
 *
 *  Created on: Nov 6, 2018
 *      Author: ominenko
 */

#ifndef CCONFIGFILE_H_
#define CCONFIGFILE_H_
#include <stdint.h>
#include <vector>
#include <ArduinoJson.h>
#include "FS.h"
#include "CPresets.h"

class CConfigFile {
  ESP8266WebServer &server;
  typedef struct {
    const char *filename;
    CPItem &handler;
    //const PROGMEM char* defValue;
  } initList_t;
  vector<initList_t> items;
  bool load(const initList_t &item);
  bool save(const initList_t &item);
  void onLoad() {
  }
  ;
  void onSave() {
  }
  ;
  void factoryReset();
public:
  CConfigFile(ESP8266WebServer &server);
  void add(const char *filename, CPItem &item) {
    items.push_back( { filename, item });
  }
  void begin();
  void info();
};

#endif /* CCONFIGFILE_H_ */
