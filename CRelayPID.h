/*
 * CRelayPID.h
 *
 *  Created on: Nov 15, 2018
 *      Author: ominenko
 */

#ifndef CRELAYPID_H_
#define CRELAYPID_H_
#include <Arduino.h>
#include <stdint.h>
#include "./libs/PID_v1.h"
#include "./libs/PID_AutoTune_v0.h"

class CRelayPID {
public:
  typedef enum {
    relay_off = 0,
    relay_power,
    relay_auto,
    pid_tune
  } mode_t;

  private:
  const uint8_t RelayPin_;
  mode_t mode_ = relay_off;
  double input_ = 0;
  double output_ = 0;
  double setpoint_ = 0;
  const uint32_t WindowSize = 10 * 60 * 1000;
  const uint32_t RelayMinSample = 60 * 1000;
  unsigned long windowStartTime = 0;
  uint32_t relaySwitchCount; //count allowed to switch in window
  const double Kp = 7011;
  const double Ki = 175;
  const double Kd = 70117;
  PID_ATune aTune;
  PID myPID;
  bool RelayOutState_;
  void setupAutoTune();
  void loop_tune();
  void loop_relay();
  void setRelayOut(bool isHigh);

  public:
  CRelayPID(uint8_t RelayPin);
  bool set_mode(mode_t mode);

  void setInput(float temperature) {
    input_ = temperature;
  }
  void setTarget(float temperature) {
    setpoint_ = temperature;
  }
  void setup();
  void loop();
  friend class CPID_tune;
};

#endif /* CRELAYPID_H_ */
