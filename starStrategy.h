#ifndef STAR_STRATEGY_H
#define STAR_STRATEGY_H

#define BACKWARD_TIME_MILLIS 2000
#define CURVE_TIME_MILLIS 1000

#include "StateMachine.h"
#include "SensorReadings.h"
#include "MotorControl.hpp"

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

class StarStrategy : public StateMachine<SearchStrategyInput, StarSearchState, StarSearchInsideAction> {
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
      StarSearchState outState;
      StarSearchInsideAction action = getNextValues(this->_state, inp, outState);

      this->_state = outState;

      switch(action) {
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
};

#endif
