#include "PidControl.h"
#include "MotorControl.hpp"
#include "Auterna/Auterna.h"
#include "Sensors.h"

void setup() {
 

}

Auterna auterna;
void loop() {
  SensorReadings inp = {
    {false, false, false, false, false},
    10,
    0,
  };
  auterna.step(inp);
}



