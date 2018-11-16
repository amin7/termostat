/*
 * CRelayPID.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: ominenko
 */
#include "CRelayPID.h"

CRelayPID::CRelayPID(uint8_t RelayPin) :
    RelayPin_(RelayPin),
        aTune(&input_, &output_),
        myPID(&input_, &output_, &setpoint_, Kp, Ki, Kd, DIRECT) {
}

void CRelayPID::setRelayOut(bool isHigh) {
  RelayOutState_ = isHigh;
  digitalWrite(RelayPin_, isHigh);
}
void CRelayPID::setup() {
  pinMode(RelayPin_, OUTPUT);
  setRelayOut(LOW);
  //tell the PID to range between 0 and the full window size
  myPID.SetOutputLimits(0, WindowSize);

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}
bool CRelayPID::set_mode(mode_t mode) {
  switch (mode) {
    case relay_off:
      setRelayOut( LOW);
      break;
    case relay_on:
      setRelayOut( HIGH);
      break;
    case relay_auto:
      relaySwitchCount = 2;
      windowStartTime = millis();
      break;
    case pid_tune:
      if (relay_off != mode_) {
        return false;
      }
      setupAutoTune();
      relaySwitchCount = 2;
      windowStartTime = millis();
      break;
  }
  mode_ = mode;
  Serial.print(__FUNCTION__);
  Serial.print(" setmode ");
  Serial.println(mode_);
  return true;
}

void CRelayPID::setupAutoTune() {
  //Set the output to the desired starting frequency.
  aTune.Cancel();
  output_ = 0; //aTuneStartValue;
  aTune.SetNoiseBand(0.25);
  aTune.SetOutputStep(WindowSize);
  aTune.SetControlType(1); //PID
  aTune.SetLookbackSec(20);
}

void CRelayPID::loop_tune()
{
  const auto now = millis();
  static long next_info = 0;
  if (next_info < now) {
    next_info = now + 5 * 1000; //once in 5 sec
    Serial.print("tuning mode (input: ");
    Serial.print(input_);
    Serial.print(" output: ");
    Serial.print(output_);
    Serial.println(")");
  }

  if (aTune.Runtime()) {
    Serial.println("auto tune is done");
    Serial.print("kp: ");
    Serial.print(aTune.GetKp());
    Serial.print(" ");
    Serial.print("ki: ");
    Serial.print(aTune.GetKi());
    Serial.print(" ");
    Serial.print("kd: ");
    Serial.print(aTune.GetKd());
    Serial.println();
    set_mode(relay_off);
  }
}

void CRelayPID::loop_relay() {
  const auto now = millis();
  auto inWindow = now - windowStartTime;
  /************************************************
   * turn the output pin on/off based on pid output
   ************************************************/
  if (inWindow > WindowSize) { //time to shift the Relay Window
    windowStartTime = now;
    relaySwitchCount = RelayOutState_ ? 1 : 2; //of on allowed off only
    inWindow = 0;
  }
  const bool isRequestOn = (output_ >= inWindow);
  if (isRequestOn == RelayOutState_) {
    return;
  }
  if (isRequestOn) {
    if (output_ < RelayMinSample) { //do not on on short period
      return;
    }
  } else {
    if (output_ > (WindowSize - RelayMinSample)) { //do not off on short period
      return;
    }
  }
  if (relaySwitchCount) {
    relaySwitchCount--;
    setRelayOut(isRequestOn);
  }
}

void CRelayPID::loop() {
  switch (mode_) {
    case pid_tune:
      loop_tune();
      loop_relay();
      break;
    case relay_auto:
      myPID.Compute();
      loop_relay();
      break;
  }
}
