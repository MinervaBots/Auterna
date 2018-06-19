#include "motion.h"

int minVel = 0;
int maxVel = 0;

void motion::drive_init() {
    analogWriteResolution(12);
}

void motion::drive(const double linearSpeed, const double angularSpeed) {
 float leftVel = (2*linearSpeed - angularSpeed*wheel_base)/2*wheel_radius;
 float rightVel = (2*linearSpeed + angularSpeed*wheel_base)/2*wheel_radius;

 int rightMotor = constrain(rightVel,minVel,maxVel);
 int leftMotor = constrain(leftVel,minVel,maxVel);

 analogWrite(pins::dac_ch1,leftMotor);
 analogWrite(pins::dac_ch2,rightMotor);
}
