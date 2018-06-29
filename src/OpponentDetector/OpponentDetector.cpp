#include "OpponentDetector.h"

tuple<Detection, Detection>
OpponentDetector::getNextValues(const Detection &state,
                                const Input &inp) const {
    Detection nextState;

    if(Sensors::isDetected(inp))
        nextState = Detection::Detected;
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
        case Detection::Detected:
            error = Sensors::headingError(inp.opponent, Sensors::weights);
            printer.print("Error: ");
            printer.println(error);
            signal = Control::PIDRegulator(error);
            printer.print("Signal: ");
            printer.println(signal);
            // Perseguir com PID
             motion::drive(0, signal);

            break;
        case Detection::notDetected:
            motion::drive(0, 0);
            // search.step(inp);
            break;

    }
}

