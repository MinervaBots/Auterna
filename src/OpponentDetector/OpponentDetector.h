#ifndef OPPONENT_DETECTOR_H
#define OPPONENT_DETECTOR_H

#include "../StateMachine/StateMachine.h"
#include "../StarStrategy/StarStrategy.h"
#include "../motion.h"

using Sensors::Input;
using motion::drive;

enum class Detection {
    Detected,
    notDetected
};

class OpponentDetector
        : public StateMachine<Input, Detection> {
public:
    OpponentDetector() : StateMachine(Detection::notDetected) {}

    tuple<Detection, Detection>
    getNextValues(const Detection &state, const Input &inp) const;

    void step(const Input &inp);

private:
    StarStrategy search;
    //CorrendoAtras Traking();

    bool isDetected(const Input &inp) const;
};

#endif
