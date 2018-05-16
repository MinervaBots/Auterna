#include "OpponentDetector.h"

Detection OpponentDetector::isDetected(SensorReadings inp){ 
    for(int i = 0; i != 5; ++i){
      if (inp.opponent[i])
          return Detection::Detected;
    }
      return Detection::notDetected;
}

SearchStrategyInput OpponentDetector::createSearchStrategyInput(SensorReadings inp) {
  SearchStrategyInput input;

  input.leftEdgeValue = inp.leftEdgeValue;
  input.rightEdgeValue = inp.rightEdgeValue;

  return input;
}

Detection OpponentDetector::getNextValues(Detection state,Detection inp,Detection& outState){
  switch(inp) {
    case Detection::Detected:    
      outState = Detection::Detected;
      break;
    case Detection::notDetected:
      outState = Detection::Detected;
      break;
    }
    return outState;
 }

void OpponentDetector::step(SensorReadings inp){
    Detection outState = Detection::notDetected;

    getNextValues(this->_state, this->isDetected(inp), outState);

    this->_state = outState;
    
    switch(outState){
      case Detection::Detected:
         //CasoTavendo tracking.steps
         break;
      case Detection::notDetected:
        SearchStrategyInput input = createSearchStrategyInput(inp);
        search.step(input);
        break;
      
    }
}

