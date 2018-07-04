#include "OpponentDetector.h"

tuple<Detection, Detection>
OpponentDetector::getNextValues(const Detection &state,
                                const Input &inp) const {
    Detection nextState;
    if(Sensors::isEdgeDetected(inp))
        nextState = Detection::edgeDetected;
    else if(Sensors::isDetected(inp))
        nextState = Detection::opponentDetected;
    else
        nextState = Detection::notDetected;

    return make_tuple(nextState, nextState);
}

void OpponentDetector::step(const Input &inp) {
    Detection nextState {Detection::notDetected};

    tie(nextState, std::ignore) = getNextValues(this->_state, inp);

    this->_state = nextState;

    double error = 0, signal = 0; 
    switch (nextState) {
        case Detection::edgeDetected:
            motion::drive(motion::maxLinearSpeed/4, 0);
            break;
        case Detection::opponentDetected:
            error = Sensors::headingError(inp.opponent, Sensors::weights);
            signal = Control::PIDRegulator(error);
            
            motion::drive(-motion::maxLinearSpeed/2, signal);
            break;
        case Detection::notDetected:
            motion::drive(0, 0);
            // search.step(inp);
            break;

    }
}

