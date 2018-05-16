#include "Auterna.h"

ActivationState Auterna::getNextValues(ActivationState state, SensorReadings inp, ActivationState& outState) {
  switch(state) {
    case ActivationState::on:
      if(/* Sinal para desligar  */true)
        outState = ActivationState::off;
      else
        outState = state;
      break;
      
    case ActivationState::turningOn:
      delay(5000);
      outState = ActivationState::on;
      break;
    case ActivationState::off:
      if(/* Sinal para ligar */false)
        outState = ActivationState::turningOn;
      else
        outState = state;
      break;
  }

  return outState;
}

void Auterna::step(SensorReadings inp) {
    ActivationState outState = ActivationState::off;

    getNextValues(this->_state, inp, outState);

    this->_state = outState;

    switch(outState) {
      case ActivationState::on:
        this->detector.step(inp);
        break;

      case ActivationState::off:
        drive(0, 0);
        break;
    }
}
