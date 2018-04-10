#include "PidControl.h"

int lastRunTime;
int sampleTime = 2; //estudar tempo
int integrativeSum = 0;

float KI = 0;
float KD = 0;
float KP = 0;

float lastOutput = 0;
float lastInput = 0;

int minOutput = 0;
int maxOutput = 0;

float PID (float input,float setPoint)
{
  unsigned long runTime = millis();
  unsigned long timeChange = (runTime - lastRunTime);
  if (timeChange < sampleTime)
  {
    return lastOutput;
  }

  float error = setPoint - input;

 
  integrativeSum += error * KI * sampleTime;

  float dInput = (KD * (input - lastInput)) / sampleTime;

  lastOutput = (KP * error) + (integrativeSum) - (dInput);
  
  lastOutput = constrain(lastOutput, minOutput, maxOutput);

  lastInput = input;
  lastRunTime = runTime;

  return lastOutput;
}
