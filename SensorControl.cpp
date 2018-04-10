#include "PidControl.h"

#define SENSOR_ODD  0
#define SENSOR_OCC  1
#define SENSOR_ODE  2
#define SENSOR_OCE  3
#define SENSOR_OCD  4

int ODD;
int ODE;
int OCE;
int OCD;
int OCC;
    
float sensorRead(){
    ODD = digitalRead(SENSOR_ODD);
    ODE = digitalRead(SENSOR_ODE);
    OCE = digitalRead(SENSOR_OCE);
    OCD = digitalRead(SENSOR_OCD);
    OCC = digitalRead(SENSOR_OCC);


    int sum = 0;
    float error = 0;
    //faz uma média entre os sensores. Os pesos escolhidos precisam ser testados
    int  soma = (-2*ODE + -1*OCE + 0*OCC + OCD +2*ODD);

    error = soma/10;

    return error;
}
 
  


