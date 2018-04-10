#include "PidControl.h"
#include "SensorControl.h"
#include "MotorControl.h"


void setup() {
  InitRobot();  

}

void loop() {
  if (OCC == 0 && sensorRead == 0){
    MotorControl(1,-1); // em tese fará o robô girar pra direita caso ele não esteja vendo nada
  }
  else{
   float angular = PID(sensorRead(),2);
    MotorControl(1,angular);
  }
}

void InitRobot(){
  pinMode(SENSOR_OCD,INPUT);
  pinMode(SENSOR_OCE,INPUT);
  pinMode(SENSOR_ODD,INPUT);
  pinMode(SENSOR_ODE,INPUT);
  pinMode(SENSOR_OCC,INPUT);
  pinMode(LEFT_MOTOR,OUTPUT);
  pinMode(RIGHT_MOTOR,OUTPUT);
}

