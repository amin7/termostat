/*
 * CTransformLine.h
 *
 *  Created on: Nov 8, 2018
 *      Author: ominenko
 */

#ifndef CTRANSFORMLINE_H_
#define CTRANSFORMLINE_H_
#include <stdint.h>
#include <map>
#include "CPItem.h"
class CTransformLine: public CPItem {
  std::map<int16_t, float> adc2c;
  float result_offset;
public:
  CTransformLine();
  virtual bool deSerialize(const JsonObject& root) override;
  virtual bool serialize(JsonObject& root) const override;
  float convert(const int16_t adc);
};

#endif /* CTRANSFORMLINE_H_ */
