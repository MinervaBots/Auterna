#ifndef PINS_H
#define PINS_H

namespace pins {
    constexpr int led = 13;

    // DAC channels for motor control
    constexpr int dac_ch1 = 8;
    constexpr int dac_ch2 = 9;

    // Opponent sensors
    constexpr int ode = 1;
    constexpr int od = 2;
    constexpr int oc = 3;
    constexpr int oe = 4;
    constexpr int odd = 5;

    // Edge sensors
    constexpr int bef = 6;
    constexpr int bdf = 7;
}

#endif