#include "motion.h"

void motion::drive_init() {
    analogWriteResolution(DAC_resolution);
}

void motion::drive(double linearSpeed, double angularSpeed) {
    double leftWheelSpeed, rightWheelSpeed, leftVoltage, rightVoltage;

    // constrain parameters
    tie(linearSpeed, angularSpeed) = constrainSpeeds(linearSpeed, angularSpeed);

    // Convert models
    tie(leftWheelSpeed, rightWheelSpeed) = unicycleToDifferential(linearSpeed, angularSpeed);

    // Ensure angular speed
    tie(leftWheelSpeed, rightWheelSpeed) = ensureAngularSpeed(leftWheelSpeed, rightWheelSpeed);  

    // Calculate corresponding voltages
    leftVoltage = angularSpeedToControllerVoltage(leftWheelSpeed);
    rightVoltage = angularSpeedToControllerVoltage(rightWheelSpeed);

    // Apply signal
    analogWrite(pins::dac_ch0, mapVoltageToDACInteger(leftVoltage));
    analogWrite(pins::dac_ch1, mapVoltageToDACInteger(rightVoltage));
}

constexpr tuple<double, double>
motion::ensureAngularSpeed(double leftWheelAngularSpeed, double rightWheelAngularSpeed) {
    double maxSpeed = max(leftWheelAngularSpeed, rightWheelAngularSpeed);
    double minSpeed = min(leftWheelAngularSpeed, rightWheelAngularSpeed);

    if (maxSpeed > maxWheelSpeed) {
        leftWheelAngularSpeed -= maxSpeed - maxWheelSpeed;
        rightWheelAngularSpeed -= maxSpeed - maxWheelSpeed;
    }              
    else if (minSpeed < -maxWheelSpeed) {
        leftWheelAngularSpeed -= minSpeed + maxWheelSpeed;
        rightWheelAngularSpeed -= minSpeed + maxWheelSpeed;
    }    

    return make_tuple(leftWheelAngularSpeed, rightWheelAngularSpeed);
}

constexpr tuple<double, double>
motion::constrainSpeeds(const double linearSpeed, const double angularSpeed) {
    return make_tuple(
        constrain(linearSpeed, -maxLinearSpeed, maxLinearSpeed),
        constrain(angularSpeed, -maxAngularSpeed, maxAngularSpeed)
    );
}

constexpr tuple<double, double>
motion::unicycleToDifferential(const double linearSpeed, const double angularSpeed) {
    return make_tuple(
        (2*linearSpeed - angularSpeed*wheelBase)/(2*wheelRadius), // Right wheel angular speed
        (2*linearSpeed + angularSpeed*wheelBase)/(2*wheelRadius)  // Left wheel angular speed
    );
}

constexpr double motion::angularSpeedToControllerVoltage(const double angularWheelSpeed) {
    return angularWheelSpeed/maxWheelSpeed + 1;
}

constexpr int motion::mapVoltageToDACInteger(const double voltage) {
    return (voltage/refVoltage) * ((1 << DAC_resolution) - 1);
}