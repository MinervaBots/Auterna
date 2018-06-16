#ifndef STAR_STRATEGY_H
#define STAR_STRATEGY_H

#define BACKWARD_TIME_MILLIS 2000
#define CURVE_TIME_MILLIS 1000

#include "Arduino.h"
#include "../StateMachine/StateMachine.h"
#include "../SensorReadings.h"
#include "../MotorControl.hpp"

enum class StarSearchInsideAction {
  forward,
  backward,
  curve,
};

class StarSearchState{
public:
  StarSearchState(bool edge, StarSearchInsideAction action, unsigned long actionTimeout) : edgeDetected(edge), action(action), actionTimeout(actionTimeout) {}

  bool edgeDetected;
  StarSearchInsideAction action;
  unsigned long actionTimeout;
};

class StarStrategy : public StateMachine<SearchStrategyInput, StarSearchState, StarSearchInsideAction> {
public:
    StarStrategy() : StateMachine(StarSearchState(false, StarSearchInsideAction::forward, 0)) {}

    StarSearchInsideAction getNextValues(StarSearchState state, SearchStrategyInput inp, StarSearchState& outState);
    void step(SearchStrategyInput inp);
};

#endif
