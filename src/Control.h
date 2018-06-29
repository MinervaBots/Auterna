#ifndef CONTROL_H
#define CONTROL_H

namespace Control {
    constexpr double Kp = 5;
    constexpr double Ki = 0;
    constexpr double Kd = 0;

    double PIDRegulator(double error);
}

#endif