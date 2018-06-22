#include "motion.h"

int minVel = 0;
int maxVel = 0;

void motion::drive_init() {
    analogWriteResolution(12);
}

void motion::drive(const double linearSpeed, const double angularSpeed) {
 float leftVel = (2*linearSpeed - angularSpeed*wheelBase)/2*wheelRadius;
 float rightVel = (2*linearSpeed + angularSpeed*wheelBase)/2*wheelRadius;

 int rightMotor = constrain(rightVel,minVel,maxVel);
 int leftMotor = constrain(leftVel,minVel,maxVel);

 analogWrite(pins::dac_ch0,leftMotor);
 analogWrite(pins::dac_ch1,rightMotor);
}

// constexpr tuple<double, double>
// motion::ensureAngularSpeed(const double linearSpeed, const double angularSpeed) {

// }

// constexpr tuple<double, double>
// motion::limitSpeeds(const double leftAngularSpeed, const double rightAngularSpeed) {
//     return make_tuple(
//         constrain(leftAngularSpeed, -motion::maxWheelVel, motion::maxWheelVel)
//         constrain(rightAngularSpeed, -motion::maxWheelVel, motion::maxWheelVel)
//     );
// }