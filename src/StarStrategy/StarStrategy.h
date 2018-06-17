#ifndef STAR_STRATEGY_H
#define STAR_STRATEGY_H

#define BACKWARD_TIME_MILLIS 2000
#define CURVE_TIME_MILLIS 1000

#include "../StateMachine/StateMachine.h"
#include "../Sensors.h"
#include "../MotorControl.hpp"
#include "Arduino.h"

enum class StarSearchInsideAction {
    forward,
    backward,
    curve,
};

class StarSearchState {
public:
    StarSearchState(bool edge, StarSearchInsideAction action,
                    unsigned long actionTimeout) : edgeDetected(edge),
                                                   action(action),
                                                   actionTimeout(
                                                           actionTimeout) {}

    bool edgeDetected;
    StarSearchInsideAction action;
    unsigned long actionTimeout;
};

class StarStrategy
        : public StateMachine<Input, StarSearchState, StarSearchInsideAction> {
public:
    StarStrategy() : StateMachine(
            StarSearchState(false, StarSearchInsideAction::forward, 0)) {}

    tuple<StarSearchState, StarSearchInsideAction>
    getNextValues(const StarSearchState &state, const Input &inp) const;

    void step(const Input &inp);
};

#endif
