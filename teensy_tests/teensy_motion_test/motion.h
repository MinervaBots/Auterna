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
    // Dynamics related constants
    constexpr double wheelBase = 10;  // Distance between wheels
    constexpr double wheelRadius = 5;

    constexpr int maxRPM = 8000;             // Physical maximum
    constexpr int limitRPM = maxRPM / 4;     // Artificial limit
    constexpr int limitRPS = limitRPM / 60;
    constexpr double maxWheelSpeed = limitRPS*2*M_PI;

    constexpr double maxAngularSpeed = 2*wheelRadius/wheelBase*maxWheelSpeed;
    constexpr double maxLinearSpeed = wheelRadius*maxWheelSpeed;

    // Signal related constants
    constexpr int DAC_resolution = 12; // Any integer in the interval [2, 16]
    constexpr double refVoltage = 3.6;
    constexpr int minSignalVoltage = 0;
    constexpr int maxSignalVoltage = 2;

    // DAC setup
    void drive_init();

    // Main motion function
    void drive(double linearSpeed, double angularSpeed);

    // Corrects the wheels speeds in order to guarantee the desired robot's angular velocity
    // Consequently, the robot's linear velocity might be altered
    constexpr tuple<double, double> 
    ensureAngularSpeed(double leftWheelAngularSpeed, double rightWheelAngularSpeed);

    // Restrict the parameters to the physical limits of the robot
    constexpr tuple<double, double>
    constrainSpeeds(const double linearSpeed, const double angularSpeed);

    // Convert the control model's motion parameters, linear speed and angular speed,
    // to the robot's motion parameters, the angular speeds of the wheels
    constexpr tuple<double, double>
    unicycleToDifferential(const double linearSpeed, const double angularSpeed);

    // The motor controller expects a signal in the interval 0-2V, where 0V = full reverse,
    // 1V = stop and 2V = full forward.
    constexpr double angularSpeedToControllerVoltage(const double angularWheelSpeed);

    // Map a desired voltage to an integer in the interval expected by the analogWrite function
    constexpr int mapVoltageToDACInteger(const double voltage);
}

#endif

