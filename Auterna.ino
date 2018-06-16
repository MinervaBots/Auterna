#include "PidControl.h"
#include "SensorControl.h"
#include "MotorControl.hpp"
#include "Auterna/Auterna.h"
#include "SensorReadings.h"

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



