#include <Sensors.h>
#include "StarStrategy.h"

tuple<StarSearchState, StarSearchInsideAction>
StarStrategy::getNextValues(const StarSearchState &state,
                            const Input &inp) const {
    // TODO Uncomment Arduino functions
    StarSearchState nextState {false, StarSearchInsideAction::forward, 0};

    if (inp.leftEdgeDetected || inp.rightEdgeDetected) {
        if (state.action == StarSearchInsideAction::forward) {
            nextState.action = StarSearchInsideAction::backward;
            nextState.actionTimeout = /*millis() */0 + BACKWARD_TIME_MILLIS;
        }

    } else {
        switch (state.action) {

            case StarSearchInsideAction::backward:
                if (/*millis()*/0 > state.actionTimeout) {
                    nextState.action = StarSearchInsideAction::curve;
                    nextState.actionTimeout = /*millis()*/ 0 + CURVE_TIME_MILLIS;
                }
                break;

            case StarSearchInsideAction::curve:
                if (/*millis()*/0 > state.actionTimeout)
                    nextState.action = StarSearchInsideAction::forward;
                break;
        }
    }

    return make_tuple(nextState, nextState.action);
}

void StarStrategy::step(const Input &inp) {
    StarSearchState nextState {false, StarSearchInsideAction::forward, 0};
    StarSearchInsideAction action;

    tie(nextState, action) = getNextValues(this->_state, inp);

    this->_state = nextState;

    switch (action) {
        case StarSearchInsideAction::forward:
            drive(255, 0);
            break;
        case StarSearchInsideAction::backward:
            drive(0, 0);
            break;
        case StarSearchInsideAction::curve:
            drive(0, 255);
            break;
    }
}
