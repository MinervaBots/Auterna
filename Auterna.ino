#include "src/PidControl.h"
#include "src/MotorControl.hpp"
#include "src/Auterna/Auterna.h"
#include "src/Sensors.h"

void setup() {
}

Auterna auterna;
void loop() {
  Input inp = collectInput();
  auterna.step(inp);
}



