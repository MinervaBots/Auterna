#include "StarStrategy.h"

StarSearchInsideAction StarStrategy::getNextValues(StarSearchState state, SearchStrategyInput inp, StarSearchState& outState) {
  if(inp.leftEdgeValue || inp.rightEdgeValue) {
    if(state.action == StarSearchInsideAction::forward) {
      outState.action = StarSearchInsideAction::backward;
      outState.actionTimeout = millis() + BACKWARD_TIME_MILLIS;
    }
    
  } else {
    switch(state.action) {
        
        case StarSearchInsideAction::backward:
          if(millis() > state.actionTimeout) {
            outState.action = StarSearchInsideAction::curve;
            outState.actionTimeout = millis() + CURVE_TIME_MILLIS;
          }
          break;
        
        case StarSearchInsideAction::curve:
          if(millis() > state.actionTimeout)
            outState.action = StarSearchInsideAction::forward;
          break;
      }
  }

  return outState.action;
}

void StarStrategy::step(SearchStrategyInput inp) {
  StarSearchState outState(false, StarSearchInsideAction::forward, 0);
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
