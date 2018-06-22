#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>
#include <tuple>
#include <cmath>
#include "pins.h"

using std::tuple;
using std::make_tuple;
using std::tie;

namespace motion {
    constexpr double wheelBase = 10;  // Distance between wheels
    constexpr double wheelRadius = 5;

    constexpr int maxRPM = 3000;
    constexpr int maxRPS = maxRPM / 60;
    constexpr double maxAngularVel = maxRPS*2*M_PI;

    // DAC setup
    void drive_init();

    // Monocycle model to differential drive model mapping
    void drive(const double linearSpeed, const double angularSpeed);

    // constexpr tuple<double, double> 
    // ensureAngularSpeed(const double linearSpeed, const double angularSpeed);

    // constexpr tuple<double, double> 
    // limitSpeeds(const double leftAngularSpeed, const double rightAngularSpeed);
}

#endif
