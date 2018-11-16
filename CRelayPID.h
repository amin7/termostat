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
    relay_on,
    relay_auto,
    pid_tune
  } mode_t;
  private:
  const uint8_t RelayPin_;
  mode_t mode_ = relay_off;
  double input_ = 0;
  double output_ = 0;
  double setpoint_ = 0;
  const int16_t WindowSize = 10 * 60 * 1000;
  const int16_t RelayMinSample = 60 * 1000;
  unsigned long windowStartTime = 0;
  uint8_t relaySwitchCount; //count allowed to switch in window
  const double Kp = 2, Ki = 5, Kd = 1;
  PID_ATune aTune;
  PID myPID;
  bool RelayOutState_;
  void setupAutoTune();
  void loop_tune();
  void loop_relay();

  public:
  void setRelayOut(bool isHigh);
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
};

#endif /* CRELAYPID_H_ */
