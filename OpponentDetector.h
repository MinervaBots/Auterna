#ifndef OPPONENT_DETECTOR_H
#define OPPONENT_DETECTOR_H

#include "SensorControl.h"
#include "StateMachine.h"
#include "StarStrategy.h"

enum class Detection {
  Detected,
  notDetected
};


class OpponentDetector : public StateMachine<SensorReadings, Detection, Detection>{
  public:
    OpponentDetector() : StateMachine(Detection::notDetected){}

    Detection getNextValues(Detection state,Detection inp,Detection& outState);
    void step(SensorReadings inp);
    
  private:
    StarStrategy search;
    //CorrendoAtras Traking();

    Detection isDetected(SensorReadings inp);
    SearchStrategyInput createSearchStrategyInput(SensorReadings inp);
};
#endif
