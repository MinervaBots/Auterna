#include "Auterna.h"

Auterna::Auterna(Print &printer) : StateMachine<Input, ActivationState>(
        ActivationState::turningOn), printer(printer), detector(printer) {}

tuple<ActivationState, ActivationState>
Auterna::getNextValues(const ActivationState &state,
                       const Input &inp) const {
    ActivationState nextState {ActivationState::off};
    switch (state) {
        case ActivationState::on:
            if (inp.shutdownCommand)
                nextState = ActivationState::off;
            else
                nextState = state;
            break;

        case ActivationState::turningOn:
            delay(5000);
            nextState = ActivationState::on;
            break;
        case ActivationState::off:
            if (inp.turnOnCommand)
                nextState = ActivationState::turningOn;
            else
                nextState = state;
            break;
    }

    return make_tuple(nextState, nextState);
}

void Auterna::step(const Input &inp) {
    ActivationState nextState {ActivationState::off};

    tie(nextState, std::ignore) = getNextValues(this->_state, inp);

    this->_state = nextState;

    switch (nextState) {
        case ActivationState::on:
            this->detector.step(inp);
            break;

        default:
            motion::drive(0, 0);
            break;
    }
}
