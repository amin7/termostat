/*
 * CConfigFile.h
 *
 *  Created on: Nov 6, 2018
 *      Author: ominenko
 */

#ifndef CCONFIGFILE_H_
#define CCONFIGFILE_H_
#include <stdint.h>
#include <map>
#include "FS.h"
#include "CPItem.h"

class CConfigFile {
  String getFileName(String name) {
    return "/" + name + ".json";
  }
protected:
  std::map<String, std::pair<const char *, CPItem *>> items;
  bool load(const String &name, CPItem &handler);
  bool save(const String &name, CPItem &handler);
public:
  CConfigFile() :
      items( { }) {

  }
  void add(const String name, const char *defvalue, CPItem &item) {
    items[name] = {defvalue, &item};
  }
  void factoryReset();
  void begin();
  void info();
};

#endif /* CCONFIGFILE_H_ */
