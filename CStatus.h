/*
 * CStatus.h
 *
 *  Created on: 11 ????. 2018 ?.
 *      Author: User
 */

#ifndef CSTATUS_H_
#define CSTATUS_H_
#include <stdint.h>
#include "CPItem.h"

class CStatus: public CPItem {
public:
  float air_term_;
  float air_humm_;
  float floor_term_;
  float desired_temperature_;
  int16_t adc_;
  virtual bool serialize(JsonObject& root) const override;
  virtual bool deSerialize(const JsonObject& root) override;
};

#endif /* CSTATUS_H_ */
