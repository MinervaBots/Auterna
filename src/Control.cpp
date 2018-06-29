#include "Control.h"

double Control::PIDRegulator(double error) {
    static double integral = 0, last_error = 0, output = 0;
    
    integral = integral + Ki*error;
    output = Kp * error + integral + Kd *(error-last_error);
    last_error = error;
    
    return output;
}