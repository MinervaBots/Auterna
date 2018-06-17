#include "OpponentDetector.h"

bool OpponentDetector::isDetected(const Input &inp) const {
    for (int i = 0; i != 5; ++i) {
        if (inp.opponent[i])
            return true;
    }
    return false;
}

tuple<Detection, Detection>
OpponentDetector::getNextValues(const Detection &state,
                                const Input &inp) const {
    Detection nextState;

    if(isDetected(inp))
        nextState = Detection::Detected;
    else
        nextState = Detection::notDetected;

    return make_tuple(nextState, nextState);
}

void OpponentDetector::step(const Input &inp) {
    Detection nextState {Detection::notDetected};

    tie(nextState, std::ignore) = getNextValues(this->_state, inp);

    this->_state = nextState;

    switch (nextState) {
        case Detection::Detected:
            // Perseguir com PID
            break;
        case Detection::notDetected:
            search.step(inp);
            break;

    }
}

