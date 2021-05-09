/*
 * CADCimpl.h
 *
 *  Created on: May 4, 2021
 *      Author: ominenko
 */

#pragma once
#include <stdint.h>
#include <array>

class CADC_impl {
    std::array<int, 6> m_filter { 0 };
    uint8_t m_count = 0; //avarage count
    void sensor_loop() {
        const long now = millis();
        static long nextSensor = 0;
        if (now < nextSensor) {
            return;
        }
        nextSensor = now + SENSOR_REFRESH_PERIOD;

        const auto air_term = dht.getTemperature();
        if (!isnan(air_term)) {
            Config.status_.air_term_ = air_term;
        }
        const auto air_humm = dht.getHumidity();
        if (!isnan(air_humm)) {
            Config.status_.air_humm_ = air_humm;
        }

        std::rotate(ADC_filter.rbegin(), ADC_filter.rbegin() + 1, ADC_filter.rend());
        ADC_filter[0] = analogRead(TermistorPin);
        if (ADC_count < ADC_filter.size()) {
            ADC_count++;
        }
        const auto averADCvalue = accumulate(ADC_filter.begin(), ADC_filter.end(), 0) / ADC_count;
    }
    ;

