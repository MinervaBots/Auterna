#include "src/PidControl.h"
#include "src/motion.h"
#include "src/Auterna/Auterna.h"
#include "src/Sensors.h"
#include "src/pins/pins.h"
#include "src/motion.h"

using Sensors::Input;
using Sensors::collectInput;
using Sensors::printInput;

void setup() {
  pins::initPins();
  motion::drive_init();
  motion::drive(0, 0);
  Serial.begin(9600);

  digitalWrite(pins::led, HIGH);
}

Auterna auterna(Serial);
Input inp;
void loop() {
  collectInput(inp, Serial);
  // printInput(inp, Serial);
  // delay(800);
  auterna.step(inp);
}



