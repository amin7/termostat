/*
 * CRelayPID.h
 *
 *  Created on: Nov 15, 2018
 *      Author: ominenko
 */

#ifndef CRELAYPID_H_
#define CRELAYPID_H_
#include <PID_v1.h>
class CRelayPID {
public:
  CRelayPID();
  void loop();
};

#endif /* CRELAYPID_H_ */
