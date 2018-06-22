#ifndef AUTERNA_H
#define AUTERNA_H

#include "../StateMachine/StateMachine.h"
#include "../OpponentDetector/OpponentDetector.h"
#include "../Sensors.h"
#include <Arduino.h>

using Sensors::Input;

enum class ActivationState {
    off,
    turningOn,
    on
};

//enum class ActivationAction {
class Auterna : public StateMachine<Input, ActivationState> {
public:
    Auterna();

    tuple<ActivationState, ActivationState>
    getNextValues(const ActivationState &state,
                  const Input &inp) const;

    void step(const Input &inp);

private:
    OpponentDetector detector;
};

#endif
