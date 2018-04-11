#include "MotorControl.hpp"
#include "Arduino.h"

#define LEFT_MOTOR  5
#define RIGHT_MOTOR  6

int minVel = 0;
int maxVel = 0;

void MotorControl::drive(const int linearSpeed, const double angularSpeed) const {
  float leftVel = linearSpeed - angularSpeed;
  float rightVel = linearSpeed + angularSpeed;

  int rightMotor = constrain(rightVel,minVel,maxVel);
  int leftMotor = constrain(leftVel,minVel,maxVel);

  analogWrite(LEFT_MOTOR,leftMotor);
  analogWrite(RIGHT_MOTOR,rightMotor);
}
