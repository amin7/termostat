/*
 * CRelayPID.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: ominenko
 */
#include "CRelayBangBang.h"

CRelayBangBang::CRelayBangBang(uint8_t RelayPin) :
    RelayPin_(RelayPin) {
}

void CRelayBangBang::setRelayOut(bool isHigh) {
  if (isHigh != output_) {
    relaySwitchCount++;
  }
  output_ = isHigh;
  digitalWrite(RelayPin_, output_);
  Serial.print("setRelayOut  ");
  Serial.println(output_);
}
void CRelayBangBang::setup() {
  pinMode(RelayPin_, OUTPUT);
  digitalWrite(RelayPin_, 0);
  output_ = false;
}

bool CRelayBangBang::set_mode(mode_t mode) {
  switch (mode) {
    case relay_off:
      setRelayOut(LOW);
      break;
    case relay_auto:
      break;
  }
  mode_ = mode;
  Serial.print(__FUNCTION__);
  Serial.print(" setmode ");
  Serial.println(mode_);
  return true;
}


void CRelayBangBang::loop() {
  if (relay_off == mode_) {
    return;
  }
  if (input_ > (setpoint_ + threshold_)) {
    setRelayOut(false);
  }

  if (input_ < (setpoint_ - threshold_)) {
    setRelayOut(true);
  }

}
