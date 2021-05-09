/*
 * CLightSensor.cpp
 *
 *  Created on: 11 ???. 2017 ?.
 *      Author: User
 */
#include <ESP8266WiFi.h>
#include "CADC_filter.h"

int CADC_filter::getValue() {
    const auto now = millis();
    if (now >= m_nextRead) {
        m_nextRead = now + m_refreshPeriod;
        std::rotate(m_filter.rbegin(), m_filter.rbegin() + 1, m_filter.rend());
        m_filter[0] = analogRead(A0);
        if (m_count < m_filter.size()) {
            m_count++;
        }
    }
    return m_count ? (std::accumulate(m_filter.begin(), m_filter.end(), 0) / m_count) : 0;

}

