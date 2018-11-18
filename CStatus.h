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
  const uint8_t config_version_ = 0;
public:
  float air_term_;
  float air_humm_;
  float floor_term_;
  float desired_temperature_;
  uint8_t adc_;
  bool heater_on_;
  virtual bool serialize(JsonObject& root) const override;
  virtual bool deSerialize(const JsonObject& root) override;
};

#endif /* CSTATUS_H_ */
