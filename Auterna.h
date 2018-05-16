#ifndef AUTERNA_H
#define AUTERNA_H

#include "StateMachine.h"
#include "SensorReadings.h"
#include "Arduino.h"
#include "MotorControl.hpp"

enum class ActivationState {
  off,
  turningOn,
  on
};

//enum class ActivationAction {
class Auterna : public StateMachine<SensorReadings, ActivationState, ActivationState> {
public:
  Auterna() : StateMachine(ActivationState::off) {
    // this->detector = OpponentDetector();  
  }

  ActivationState getNextValues(ActivationState state, SensorReadings inp, ActivationState& outState);
  void step(SensorReadings inp);

private:
  // OpponentDetector detector;
};

#endif