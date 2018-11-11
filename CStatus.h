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
  float temperature_;
  float humidity_;
  float floor_temperature_;
  float desired_temperature_;
  uint8_t adc_;
  bool relay_on_;
  virtual bool serialize(JsonObject& root) const override;
  virtual bool deSerialize(const JsonObject& root) override;
};

#endif /* CSTATUS_H_ */
