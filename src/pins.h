#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

namespace pins {
    constexpr int led = 13;

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

    // void initPins() {
    //     pinMode(led, OUTPUT);

    //     pinMode(ode, INPUT);
    //     pinMode(od, INPUT);
    //     pinMode(oc, INPUT);
    //     pinMode(oe, INPUT);
    //     pinMode(odd, INPUT);

    //     // Usar em conjunto com readEdgeSensorsDigital
    //     pinMode(bef, INPUT_PULLUP);
    //     pinMode(bdf, INPUT_PULLUP);

    //     // Usar em conjunto com readEdgeSensorsTiming
    //     // pinMode(bef, INPUT);
    //     // pinMode(bdf, INPUT);

    //     pinMode(dac_ch0, OUTPUT);
    //     pinMode(dac_ch1, OUTPUT);
    // }
}

#endif