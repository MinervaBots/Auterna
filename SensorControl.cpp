#include "SensorControl.h"
#include "Arduino.h"
 
void SensorControl :: sensorRead(){
   
   _opponent[0] = digitalRead(_OE);
   _opponent[1] = digitalRead(_ODE);
   _opponent[2] = digitalRead(_OC);
   _opponent[3] = digitalRead(_ODD);
   _opponent[4] = digitalRead(_OD);
  _rightEdgeValue = analogRead(_rightEdge);
  _leftEdgeValue = analogRead(_leftEdge);
}

void SensorControl :: getReadings(SensorReadings& sr) {
  for(int i = 0; i != 5; ++i)
    sr.opponent[i] = _opponent[i];

  sr.leftEdgeValue = _leftEdgeValue;
  sr.rightEdgeValue = _rightEdgeValue;
}

