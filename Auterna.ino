#include "src/PidControl.h"
#include "src/motion.h"
#include "src/Auterna/Auterna.h"
#include "src/Sensors.h"
#include "src/pins.h"

void setup() {
  Serial1.begin(9600);
}

Auterna auterna;
Input inp;
void loop() {
  collectInput(inp, Serial1);
  auterna.step(inp);
}



