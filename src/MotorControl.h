#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#define LEFT_CHANNEL_PIN 1
#define RIGHT_CHANNEL_PIN 2

#include <Arduino.h>

//class MotorControl {
//  public:
//    MotorControl(const int leftChannel, const int rightChannel): 
//    _leftChannel(leftChannel), _rightChannel(rightChannel) {};
//
//    void drive(const int linearSpeed, const double angularSpeed) const;
//  private:
//    int _leftChannel,
//        _rightChannel;
//};

void drive(const double linearSpeed, const double angularSpeed);

#endif
