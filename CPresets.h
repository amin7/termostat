/*
 * presets.h
 *
 *  Created on: Nov 2, 2017
 *      Author: ominenko
 */

#ifndef CPRESETS_H_
#define CPRESETS_H_
#include <stdint.h>
#include <vector>
#include "CPItem.h"
using namespace std ;

template<size_t _size>
class CPI_BitField: public CPItem {
  bool bitField[_size + 1];
  const char *_name;
public:
  CPI_BitField(const char *name) :
      _name(name) {
  }
  ;
  bool &operator[](int index) {
    if (_size <= index) //to prevent mem error
      index = _size;
    return bitField[index];
  }
  const bool &operator[](int index) const {
    if (_size <= index) //to prevent mem error
      index = _size;
    return bitField[index];
  }

  bool deSerialize(const JsonObject& root) override {
    const uint32_t bits = root[_name];
    for (auto index = 0; index < _size; index++) {
      this->operator [](index) = (bits & (1 << index)) ? true : false;
    }
    return 0;
  }

  bool serialize(JsonObject& root) const override {
    uint32_t bits = 0;
    for (auto index = 0; index < _size; index++) {
      if (this->operator [](index)) {
        bits |= (1 << index);
      }
    }
    root[_name] = bits;
    return true;
  }
};

class CPI_byWeekDay: public CPItem {
public:
  CPI_BitField<7> weekDay;
  CPI_BitField<24> hours;
  virtual bool serialize(JsonObject& root) const override;
  virtual bool deSerialize(const JsonObject& root) override;
  CPI_byWeekDay() :
      weekDay("weekDay"), hours("hours") {
  }
  ;
};


class CPresets: public CPItem {
  vector<CPI_byWeekDay> items;
  public:
  virtual bool serialize(JsonObject& root) const override;
  virtual bool deSerialize(const JsonObject& root) override;
	friend class presetsTest_deserialize_Test;
};

#endif /* CPRESETS_H_ */
