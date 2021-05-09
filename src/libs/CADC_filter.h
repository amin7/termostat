/*
 * CLightSensor.h
 *
 *  Created on: 11 ???. 2017 ?.
 *      Author: User
 */

#pragma once
#include <stdint.h>
#include <array>
#include "CSignal.h"
/*
 term     10K
 +3    o---/\/\/--.--/\/\/---o GND
 |
 Pin 0 o-----------
 */

class CADC_filter: public SignalChange<int> {
    std::array<int, 10> m_filter;
    uint8_t m_count = 0; //avarage count
    static constexpr int m_refreshPeriod = 100; // ms
    unsigned long m_nextRead = 0;
    public:
    int getValue();
};

