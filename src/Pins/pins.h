#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

namespace pins {
    constexpr int led = 13;
    constexpr int button = 11;
    
    // DAC channels for motor control
    constexpr int dac_ch0 = A21;
    constexpr int dac_ch1 = A22;

    // Opponent sensors
    constexpr int ode = 25;
    constexpr int od = 26;
    constexpr int oc = 27;
    constexpr int oe = 28;
    constexpr int odd = 29;

    // Edge sensors
    constexpr int bef = 1;
    constexpr int bdf = 0;

    constexpr int servo = 20;
    
    void initPins();
}

#endif