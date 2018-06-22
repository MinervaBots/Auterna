#include "src/PidControl.h"
#include "src/motion.h"
#include "src/Auterna/Auterna.h"
#include "src/Sensors.h"
#include "src/pins.h"

using Sensors::Input;
using Sensors::collectInput;
using Sensors::printInput;

void setup() {
  // Opponent sensors
  // pins::initPins();

  pinMode(pins::led, OUTPUT);

  pinMode(pins::ode, INPUT);
  pinMode(pins::od, INPUT);
  pinMode(pins::oc, INPUT);
  pinMode(pins::oe, INPUT);
  pinMode(pins::odd, INPUT);

  // Usar em conjunto com readEdgeSensorsDigital
  pinMode(pins::bef, INPUT_PULLUP);
  pinMode(pins::bdf, INPUT_PULLUP);

  // Usar em conjunto com readEdgeSensorsTiming
  // pinMode(bef, INPUT);
  // pinMode(bdf, INPUT);

  pinMode(pins::dac_ch0, OUTPUT);
  pinMode(pins::dac_ch1, OUTPUT);
  Serial.begin(9600);

  digitalWrite(pins::led, HIGH);
}

Auterna auterna;
Input inp;
void loop() {
  collectInput(inp, Serial);
  printInput(inp, Serial);
  delay(800);
  // auterna.step(inp);
}



