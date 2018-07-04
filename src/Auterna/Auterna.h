#ifndef AUTERNA_H
#define AUTERNA_H

#include "../StateMachine/StateMachine.h"
#include "../OpponentDetector/OpponentDetector.h"
#include "../Sensors.h"
#include "../motion.h"
#include <Arduino.h>
#include <Servo.h>

using Sensors::Input;

constexpr int flagUpPosition = 0;
constexpr int flagDownPosition = 90;

enum class ActivationState {
    off,
    turningOn,
    on
};

class Auterna : public StateMachine<Input, ActivationState> {
public:
    Auterna(Print &printer);

    tuple<ActivationState, ActivationState>
    getNextValues(const ActivationState &state,
                  const Input &inp) const;

    void step(const Input &inp);

private:
    OpponentDetector detector;
    Print &printer;
    Servo servo;
};

#endif
