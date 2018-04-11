#ifndef SENSOR_CONTROL_H
#define SENSOR_CONTROL_H

#include "SensorReadings.h"

class  SensorControl {
    public:
      SensorControl(unsigned int OE,unsigned int ODE, unsigned int OC,unsigned int ODD,unsigned int OD, unsigned int leftEdge,unsigned int rightEdge):
      _OE(OE),_ODE(ODE),_OC(OC),_ODD(ODD),_OD(OD),_leftEdge(leftEdge),_rightEdge(rightEdge) {};
      void sensorRead();
      void getReadings(SensorReadings& sr);
    
    private:
     bool _opponent[5];
     int  _leftEdgeValue;
     int _rightEdgeValue;    
     float _sum;
     float _error;
     int _OE;
     int _ODE;
     int _OC;
     int _ODD;
     int _OD;
     int _leftEdge;
     int _rightEdge;   
};
#endif
