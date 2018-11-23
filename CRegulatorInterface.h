/*
 * CPIDtune.h
 *
 *  Created on: 17 ????. 2018 ?.
 *      Author: User
 */

#ifndef CREGULATORINTERFACE_H_
#define CREGULATORINTERFACE_H_
#include <stdint.h>
#include "CPItem.h"
#include "CRelayBangBang.h"
using namespace std;
class CRegulatorInterface: public CPItem {
  CRelayBangBang &retulator_;
  public:
  CRegulatorInterface(CRelayBangBang &);
  virtual bool deSerialize(const JsonObject& root);
  virtual bool serialize(JsonObject& root) const;
};

#endif /* CPIDTUNE_H_ */
