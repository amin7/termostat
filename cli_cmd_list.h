/*
 * cli_cmd_list.h
 *
 *  Created on: Nov 15, 2018
 *      Author: ominenko
 */

#ifndef CLI_CMD_LIST_H_
#define CLI_CMD_LIST_H_
#include "./libs/cmd.h"

void cli_info(int argc, char **argv) {
  Config.info();
  cmd_handler_list();
}

void cli_ifconfig(int argc, char **argv) {
  const auto mode = WiFi.getMode();

  Serial.print("WiFi mode=");
  Serial.println(mode);
  if (WIFI_STA == mode || WIFI_AP_STA == mode) {
    Serial.print("Connected  to ");
    Serial.println(wifi_ssid);
    Serial.print("Station IP address: ");
    Serial.println(WiFi.localIP());
  }
  if (WIFI_AP == mode || WIFI_AP_STA == mode) {
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
  }
}

void cli_format(int argc, char **argv) {
  bool result = SPIFFS.format();
  Serial.print("SPIFFS format: ");
  Serial.println(result);
}

void cli_pid(int argc, char **argv) {
  if (2 == argc) {
    if (false == RelayPID.set_mode(static_cast<CRelayBangBang::mode_t>(*argv[1] - '0'))) {
      Serial.println("err");
    }
  }
}

void cli_termo(int argc, char **argv) {
  Serial.print("dht status:");
  Serial.println(dht.getStatusString());
  Serial.print("Temperature= ");
  Serial.println(dht.getTemperature());
  Serial.print("Humidity= ");
  Serial.println(dht.getHumidity());

  auto ADCvalue = analogRead(TermistorPin);
  Serial.print("Analoge ");
  Serial.println(ADCvalue);
  Serial.print("transformed  ");
  Serial.println(Config.termistor_.convert(ADCvalue));
}

void cli_freset(int argc, char **argv) {
  Config.factoryReset();
}

void cli_time(int argc, char **argv) {
  Serial.print("timeStatus ");
  const auto stat = timeStatus();
  Serial.println(stat);
  if (timeNotSet != stat) {
    const auto local = get_local_time();
    Serial.printf("local %02u:%02u:%02u done\r\n", hour(local), minute(local),
        second(local));
  }
}

void cli_cmd_list_setup() {
  cmdInit();
  cmdAdd("info", cli_info);
  cmdAdd("ifconfig", cli_ifconfig);
  cmdAdd("pid", cli_pid);
  cmdAdd("term", cli_termo);
  cmdAdd("freset", cli_freset);
  cmdAdd("format", cli_format);
  cmdAdd("time", cli_time);
}


#endif /* CLI_CMD_LIST_H_ */
