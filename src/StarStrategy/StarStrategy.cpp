#include "StarStrategy.h"

tuple<StarSearchState, StarSearchInsideAction>
StarStrategy::getNextValues(const StarSearchState &state,
                            const Input &inp) const {
    StarSearchState nextState {false, StarSearchInsideAction::forward, 0};

    if (Sensors::isEdgeDetected(inp)) {
        if (state.action == StarSearchInsideAction::forward) {
            nextState.action = StarSearchInsideAction::backward;
            nextState.actionTimeout = millis() + BACKWARD_TIME_MILLIS;
        }

    } else {
        switch (state.action) {

            case StarSearchInsideAction::backward:
                if (millis() > state.actionTimeout) {
                    nextState.action = StarSearchInsideAction::curve;
                    nextState.actionTimeout = millis() + CURVE_TIME_MILLIS;
                }
                break;

            case StarSearchInsideAction::curve:
                if (millis() > state.actionTimeout)
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
            motion::drive(-motion::maxLinearSpeed/4, 0);
            break;
        case StarSearchInsideAction::backward:
            motion::drive(motion::maxLinearSpeed/4, 0);
            break;
        case StarSearchInsideAction::curve:
            motion::drive(0, motion::maxAngularSpeed/4);
            break;
    }
}
