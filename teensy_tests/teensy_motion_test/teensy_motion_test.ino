
#include <tuple>

using std::tuple;
using std::make_tuple;
using std::tie;

#include <tuple>
#include <cmath>
#include "pins.h"

using std::tuple;
using std::make_tuple;
using std::tie;

namespace motion {
    // Dynamics related constants
    constexpr double wheelBase = 10;  // Distance between wheels
    constexpr double wheelRadius = 5;

    constexpr int maxRPM = 8000;             // Physical maximum
    constexpr int limitRPM = maxRPM / 4;     // Artificial limit
    constexpr int limitRPS = limitRPM / 60;
    constexpr double maxWheelSpeed = limitRPS*2*M_PI;

    constexpr double maxAngularSpeed = 2*wheelRadius/wheelBase*maxWheelSpeed;
    constexpr double maxLinearSpeed = wheelRadius*maxWheelSpeed;

    // Signal related constants
    constexpr int DAC_resolution = 12; // Any integer in the interval [2, 16]
    constexpr double refVoltage = 3.3;
    constexpr int minSignalVoltage = 0;
    constexpr int maxSignalVoltage = 2;

    // DAC setup
    void drive_init();

    // Main motion function
    void drive(double linearSpeed, double angularSpeed);

    // Corrects the wheels speeds in order to guarantee the desired robot's angular velocity
    // Consequently, the robot's linear velocity might be altered
    constexpr tuple<double, double> 
    ensureAngularSpeed(double leftWheelAngularSpeed, double rightWheelAngularSpeed);

    // Restrict the parameters to the physical limits of the robot
    constexpr tuple<double, double>
    constrainSpeeds(const double linearSpeed, const double angularSpeed);

    // Convert the control model's motion parameters, linear speed and angular speed,
    // to the robot's motion parameters, the angular speeds of the wheels
    constexpr tuple<double, double>
    unicycleToDifferential(const double linearSpeed, const double angularSpeed);

    // The motor controller expects a signal in the interval 0-2V, where 0V = full reverse,
    // 1V = stop and 2V = full forward.
    constexpr double angularSpeedToControllerVoltage(const double angularWheelSpeed);

    // Map a desired voltage to an integer in the interval expected by the analogWrite function
    constexpr int mapVoltageToDACInteger(const double voltage);
}

void motion::drive_init() {
    analogWriteResolution(motion::DAC_resolution);
}

void motion::drive(double linearSpeed, double angularSpeed) {
    double leftWheelSpeed, rightWheelSpeed, leftVoltage, rightVoltage;
    
    // constrain parameters
    tie(linearSpeed, angularSpeed) = constrainSpeeds(linearSpeed, angularSpeed);
    
    // Convert models
    tie(leftWheelSpeed, rightWheelSpeed) = unicycleToDifferential(linearSpeed, angularSpeed);

    // Ensure angular speed
    tie(leftWheelSpeed, rightWheelSpeed) = ensureAngularSpeed(leftWheelSpeed, rightWheelSpeed);  

    // Calculate corresponding voltages
    leftVoltage = angularSpeedToControllerVoltage(leftWheelSpeed);
    rightVoltage = angularSpeedToControllerVoltage(rightWheelSpeed);

    // Apply signal
    
}

constexpr tuple<double, double>
motion::ensureAngularSpeed(double leftWheelAngularSpeed, double rightWheelAngularSpeed) {
    double maxSpeed = max(leftWheelAngularSpeed, rightWheelAngularSpeed);
    double minSpeed = min(leftWheelAngularSpeed, rightWheelAngularSpeed);

    if (maxSpeed > motion::maxWheelSpeed) {
        leftWheelAngularSpeed -= maxSpeed - motion::maxWheelSpeed;
        rightWheelAngularSpeed -= maxSpeed - motion::maxWheelSpeed;
    }              
    else if (minSpeed < -motion::maxWheelSpeed) {
        leftWheelAngularSpeed -= minSpeed + motion::maxWheelSpeed;
        rightWheelAngularSpeed -= minSpeed + motion::maxWheelSpeed;
    }    

    return make_tuple(leftWheelAngularSpeed, rightWheelAngularSpeed);
}

constexpr tuple<double, double>
motion::constrainSpeeds(const double linearSpeed, const double angularSpeed) {
    return make_tuple(
        constrain(linearSpeed, -motion::maxLinearSpeed, motion::maxLinearSpeed),
        constrain(angularSpeed, -motion::maxAngularSpeed, motion::maxAngularSpeed)
    );
}

constexpr tuple<double, double>
motion::unicycleToDifferential(const double linearSpeed, const double angularSpeed) {
    return make_tuple(
        (2*linearSpeed - angularSpeed*motion::wheelBase)/(2*motion::wheelRadius), // Right wheel angular speed
        (2*linearSpeed + angularSpeed*motion::wheelBase)/(2*motion::wheelRadius)  // Left wheel angular speed
    );
}

constexpr double motion::angularSpeedToControllerVoltage(const double angularWheelSpeed) {
    return angularWheelSpeed/motion::maxWheelSpeed + 1;
}

constexpr int motion::mapVoltageToDACInteger(const double voltage) {
    return (voltage/motion::refVoltage) * ((1 << motion::DAC_resolution) - 1);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(A21, OUTPUT);
  pinMode(A22, OUTPUT);

  Serial.begin(9600);
  motion::drive_init();
}

double linear = motion::maxLinearSpeed/2, ang = 0;

void loop() {
  // put your main code here, to run repeatedly:
    double leftWheelSpeed, rightWheelSpeed, leftVoltage, rightVoltage;
    Serial.print("linear: ");
    Serial.print(linear);
    Serial.print('\t');
    Serial.print("Angular: ");
    Serial.println(ang);
    // constrain parameters
    tie(linear, ang) = motion::constrainSpeeds(linear, ang);
    
    // Convert models
    tie(leftWheelSpeed, rightWheelSpeed) = motion::unicycleToDifferential(linear, ang);

    Serial.print("left: ");
    Serial.print(leftWheelSpeed);
    Serial.print('\t');
    Serial.print("right: ");
    Serial.println(rightWheelSpeed);

    Serial.print("Is equal to max angular speed: ");
    Serial.println(leftWheelSpeed == motion::maxWheelSpeed);
    
    // Ensure angular speed
    tie(leftWheelSpeed, rightWheelSpeed) = motion::ensureAngularSpeed(leftWheelSpeed, rightWheelSpeed);  
    Serial.println("Depois do ensure");
    Serial.print("left: ");
    Serial.print(leftWheelSpeed);
    Serial.print('\t');
    Serial.print("right: ");
    Serial.println(rightWheelSpeed);
    // Calculate corresponding voltages
    leftVoltage = motion::angularSpeedToControllerVoltage(leftWheelSpeed);
    rightVoltage = motion::angularSpeedToControllerVoltage(rightWheelSpeed);

    Serial.print("Left voltage: ");
    Serial.print(leftVoltage);
    Serial.print('\t');
    Serial.print("Right voltage: ");
    Serial.println(rightVoltage);
    // Apply signal
    analogWrite(pins::dac_ch0, motion::mapVoltageToDACInteger(leftVoltage));
    analogWrite(pins::dac_ch1, motion::mapVoltageToDACInteger(rightVoltage));

    delay(2000);
}
