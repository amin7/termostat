/*
 * CMainConfig.h
 *
 *  Created on: Nov 17, 2017
 *      Author: ominenko
 */

#ifndef CMAINCONFIG_H_
#define CMAINCONFIG_H_
#include <stdint.h>
#include <ArduinoJson.h>//https://github.com/bblanchon/ArduinoJson.git
//https://bblanchon.github.io/ArduinoJson/assistant/
#include "CPresets.h"

class CMainConfig: public CPItem {
    CPresetsConfig presetsConfig;
    ESP8266WebServer &server;
    const float def_tempAirMin = 18;
    const float def_tempAirMax = 23;
    const float def_tempFlourMax = 40;
    const float def_tempFlour = 30;
    const float def_tempHisteresis = 0.50;
    const uint8_t def_PWM = 50;
    const uint32_t def_dutyCircle = 60 * 60 * 1000; //ms
    float tempAirMin;
    float tempAirMax;
    float tempFlour;
    float tempHisteresis;
    uint8_t PWM;

    void onFactoryReset();
    public:
    bool deSerialize(JsonObject &root) {
        return 0;
    }
    ;
    JsonObject& serialize() const;
    CMainConfig(ESP8266WebServer &server);
    virtual ~CMainConfig();
    bool begin();
    size_t printTo(Print &p) const;
};

#endif /* CMAINCONFIG_H_ */
