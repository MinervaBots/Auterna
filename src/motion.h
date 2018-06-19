#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>
#include "pins.h"

namespace motion {
    constexpr double wheel_base = 10;  // Distance between wheels
    constexpr double wheel_radius = 5;

    // DAC setup
    void drive_init();

    // Monocycle model to differential drive model mapping
    void drive(const double linearSpeed, const double angularSpeed);
}

#endif
