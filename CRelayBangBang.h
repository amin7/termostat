/*
 * CRelayPID.h
 *
 *  Created on: Nov 15, 2018
 *      Author: ominenko
 */

#ifndef CRELAYBANGBANG_H_
#define CRELAYBANGBANG_H_
#include <Arduino.h>
#include <stdint.h>

class CRelayBangBang {
public:
  typedef enum {
    relay_off = 0,
    relay_auto
  } mode_t;
  private:
  const uint8_t RelayPin_;
  mode_t mode_ = relay_off;
  double input_ = 0;
  double setpoint_ = 12;
  bool output_;
  double hysteresis_ = 0.5;
  uint32_t relaySwitchCount = 0;
  void setRelayOut(bool isHigh);

  public:
  CRelayBangBang(uint8_t RelayPin);
  bool set_mode(mode_t mode);
  void setInput(float temperature) {
    input_ = temperature;
  }
  void setTarget(float temperature) {
    setpoint_ = temperature;
  }
  void setup();
  void loop();
  friend class CRegulatorInterface;
};

#endif /* CRELAYBANGBANG_H_ */
