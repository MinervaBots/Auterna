#ifndef SENSOR_READINGS_H
#define SENSOR_READINGS_H

typedef struct {
  bool opponent[5]; // Can be optimized into a bitset, in case we need memory
  bool leftEdgeDetected;
  bool rightEdgeDetected;
  bool turnOnCommand;
  bool shutdownCommand;
} Input;

Input collectInput();

#endif
