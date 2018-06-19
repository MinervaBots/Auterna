#ifndef SENSOR_READINGS_H
#define SENSOR_READINGS_H

#include <Arduino.h>
#include "pins.h"

typedef struct {
  bool opponent[5]; // Can be optimized into a bitset, in case we need memory
  bool leftEdgeDetected;
  bool rightEdgeDetected;
  bool turnOnCommand;
  bool shutdownCommand;
} Input;

constexpr char onSignal = '1';
constexpr char offSignal = '0';

void collectInput(Input &inp, Stream &reader);
void collectMockInput(Input &inp, Stream &reader);

#endif
