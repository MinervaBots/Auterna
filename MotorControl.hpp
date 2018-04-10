#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

// void MotorControl(int linear, float angular);

class MotorControl {
  public:
    MotorControl(const int leftChannel, const int rightChannel): 
      _leftChannel(leftChannel), _rightChannel(rightChannel);

    void drive(const int linearSpeed, const double angularSpeed) const;
  private:
    int _leftChannel,
        _rightChannel
};

#endif
