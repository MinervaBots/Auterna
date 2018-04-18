#ifndef SENSOR_READINGS_H
#define SENSOR_READINGS_H

typedef struct {
  bool opponent[5];
  int leftEdgeValue;
  int rightEdgeValue;
} SensorReadings;

typedef struct {
  int leftEdgeValue;
  int rightEdgeValue;
} SearchStrategyInput;

#endif
