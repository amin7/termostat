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
protected:
  typedef struct {
    CPItem *handler;
    const char *defvalue;
    const char *file_name;
  } def_items_t;
  std::map<String, def_items_t> items_;
  bool load(const char *file_name, CPItem &handler);
  bool save(const char *file_name, CPItem &handler);
public:
  CConfigFile() :
      items_( { }) {

  }

  void add(const String name, const char *defvalue, CPItem &item, const char *file_name) {
    items_[name] = {&item, defvalue, file_name};
  }
  void factoryReset();
  void begin();
  void info();
};

#endif /* CCONFIGFILE_H_ */
