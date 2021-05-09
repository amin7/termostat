/*
 *
 *  Created on: May 9, 2021
 *      Author: ominenko
 */

#pragma once
#include <libs/CConfig.h>
auto config = CConfig<512>();
auto config_termostat = CConfig<512>();
auto config_weekday = CConfig<512>();

bool settings_config(const char *fileName) {
    config.getConfig().clear();
    config.getConfig()["DEVICE_NAME"] = DEVICE_NAME;
    config.getConfig()["MQTT_SERVER"] = "";
    config.getConfig()["MQTT_PORT"] = 0;
    config.getConfig()["MQTT_PERIOD"] = 60 * 1000;
    config.getConfig()["OTA_USERNAME"] = "";
    config.getConfig()["OTA_PASSWORD"] = "";
    config.getConfig()["WIFI_CONNECT_TIMEOUT"] = 20000;
    return config.loadWE(fileName);
}

bool settings_termostat(const char *fileName) {
    config_termostat.getConfig().clear();
    config_termostat.getConfig()["HISTERESIS"] = 0.50;
    return config_termostat.loadWE(fileName);
}

bool settings_weekday(const char *fileName) {
    config_weekday.getConfig().clear();
    config_weekday.getConfig()["T_Day"] = 25;
    config_weekday.getConfig()["T_Night"] = 18;
    return config_weekday.loadWE(fileName);
}
