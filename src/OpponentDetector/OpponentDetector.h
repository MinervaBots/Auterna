#ifndef OPPONENT_DETECTOR_H
#define OPPONENT_DETECTOR_H

#include "../StateMachine/StateMachine.h"
#include "../StarStrategy/StarStrategy.h"
#include "../motion.h"
#include "../Sensors.h"
#include "../Control.h"
#include <Arduino.h>

using Sensors::Input;
using motion::drive;

enum class Detection {
    Detected,
    notDetected
};

class OpponentDetector
        : public StateMachine<Input, Detection> {
public:
    OpponentDetector(Print &printer) : StateMachine(Detection::notDetected), printer(printer) {}

    tuple<Detection, Detection>
    getNextValues(const Detection &state, const Input &inp) const;

    void step(const Input &inp);

private:
    StarStrategy search;
    Print &printer;
};

#endif
