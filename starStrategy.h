#ifndef STAR_STRATEGY_H
#define STAR_STRATEGY_H

#define BACKWARD_TIME_MILLIS 2000
#define CURVE_TIME_MILLIS 1000

#include "StateMachine.h"
#include "SensorReadings.h"

enum class StarSearchInsideAction {
  forward;
  backward;
  curve;
};

class StarSearchState{
public:
  StarSearchState(edge, action, actionTimeout) : edgeDetected(edge), action(action), actionTimeout(timestamp) {}

  bool edgeDetected;
  StarSearchInsideAction action;
  unsigned long actionTimeout;
};

class StarStrategy : public StateMachine<SearchStrategyInput, void, StarSearchState> {
    StarStrategy() : StateMachine(StarSearchState(false, StarSearchInsideAction::forward, 0)) {}

    void getNextValues(StarSearchState state, SearchStrategyInput inp) {
      switch() {
        case inp.edgeDetected:
          if(state.action == StarSearchInsideAction::forward) {
            state.action == StarSearchInsideAction::backward;
            state.actionTimeout = millis() + BACKWARD_TIME;
          }
          break;
          
        default:
          switch(state.action) {
            
            case StarSearchInsideAction::backward:
              if(millis() > state.actionTimeout) {
                state.action == StarSearchInsideAction::curve;
                state.actionTimeout == millis() + CURVE_TIME;
              }
              break;
            
            case StarSearchInsideAction::curve:
              if(millis() > state.actionTimeout)
                state.action == StarSearchInsideAction::forward;
              break;
          }
          break;
      }
    }

    void step(SearchStrategyInput inp) {
      //
    }
};

#endif
