/*
 * CPIDtune.h
 *
 *  Created on: 17 ????. 2018 ?.
 *      Author: User
 */

#ifndef CPIDTUNE_H_
#define CPIDTUNE_H_
#include <stdint.h>
#include "CPItem.h"
#include "CRelayPID.h"
using namespace std;
class CPID_tune: public CPItem {
  CRelayPID &RelayPID;
  public:
  CPID_tune(CRelayPID &);
  virtual bool deSerialize(const JsonObject& root);
  virtual bool serialize(JsonObject& root) const;
};

#endif /* CPIDTUNE_H_ */
