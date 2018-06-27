#include "pins.h"

void pins::initPins() {
        pinMode(led, OUTPUT);

        pinMode(ode, INPUT);
        pinMode(od, INPUT);
        pinMode(oc, INPUT);
        pinMode(oe, INPUT);
        pinMode(odd, INPUT);

        // Usar em conjunto com readEdgeSensorsDigital
        pinMode(bef, INPUT);
        pinMode(bdf, INPUT);

        // Usar em conjunto com readEdgeSensorsTiming
        // pinMode(bef, INPUT);
        // pinMode(bdf, INPUT);

        pinMode(dac_ch0, OUTPUT);
        pinMode(dac_ch1, OUTPUT);
    }