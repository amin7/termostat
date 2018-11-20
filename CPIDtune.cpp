/*
 * CPIDtune.cpp
 *
 *  Created on: 17 ????. 2018 ?.
 *      Author: User
 */

#include "CPIDtune.h"
CPID_tune::CPID_tune(CRelayPID &RelayPID) :
    RelayPID(RelayPID) {

}
bool CPID_tune::deSerialize(const JsonObject& root) {
  RelayPID.set_mode(static_cast<CRelayPID::mode_t>(root["mode"].as<uint8_t>()));
  if (root.containsKey("output")) {
    RelayPID.output_ = root["output"];
  }

}

bool CPID_tune::serialize(JsonObject& root) const {
  root["mode"] = static_cast<uint8_t>(RelayPID.mode_);
  root["input"] = RelayPID.input_;
  root["output"] = RelayPID.output_;
  root["setpoint_"] = RelayPID.setpoint_;
  if (!isnan(RelayPID.aTune.GetKp())) {
    root["atune_kp"] = RelayPID.aTune.GetKp();
  }
  if (!isnan(RelayPID.aTune.GetKi())) {
    root["atune_ki"] = RelayPID.aTune.GetKi();
  }
  if (!isnan(RelayPID.aTune.GetKd())) {
    root["atune_kd"] = RelayPID.aTune.GetKd();
  }
  root["peakCount"] = RelayPID.aTune.getPeakCount();
  root["WindowSize"] = RelayPID.WindowSize;
  root["atune_mode"] = RelayPID.aTune.getMode();
  root["atune_setpoint"] = RelayPID.aTune.setpoint_;
  root["atune_absMin"] = RelayPID.aTune.absMin;
  root["atune_absMax"] = RelayPID.aTune.absMax;
}
