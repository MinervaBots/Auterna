#include "OpponentDetector.h"

tuple<Detection, Detection>
OpponentDetector::getNextValues(const Detection &state,
                                const Input &inp) const {
    Detection nextState;

    if(Sensors::isDetected(inp))
        nextState = Detection::Detected;
    else
        nextState = Detection::notDetected;

    return make_tuple(nextState, nextState);
}

void OpponentDetector::step(const Input &inp) {
    Detection nextState {Detection::notDetected};

    tie(nextState, std::ignore) = getNextValues(this->_state, inp);

    this->_state = nextState;

    double error = 0, signal = 0; 
    switch (nextState) {
        case Detection::Detected:
            error = Sensors::headingError(inp.opponent, Sensors::weights);
            printer.print("Error: ");
            printer.println(error);
            signal = Control::PIDRegulator(error);
            printer.print("Signal: ");
            printer.println(signal);

            double leftWheelSpeed, rightWheelSpeed, leftVoltage, rightVoltage, lin, ang;

            // constrain parameters
            tie(lin, ang) = motion::constrainSpeeds(0, signal);

            // Convert models
            tie(leftWheelSpeed, rightWheelSpeed) = motion::unicycleToDifferential(lin, ang);

            // Ensure angular speed
            tie(leftWheelSpeed, rightWheelSpeed) = motion::ensureAngularSpeed(leftWheelSpeed, rightWheelSpeed);  

            // Calculate corresponding voltages
            leftVoltage = motion::angularSpeedToControllerVoltage(leftWheelSpeed);
            rightVoltage = motion::angularSpeedToControllerVoltage(rightWheelSpeed);

            printer.print("leftVoltage: ");
            printer.println(leftVoltage);

            printer.print("rightVoltage: ");
            printer.println(rightVoltage);

            // Perseguir com PID
            //if(error == 0 && Sensors::centralDetected(inp))
              //  motion::drive(1000, 0);
            //else
                motion::drive(-motion::maxLinearSpeed/2, signal);

            break;
        case Detection::notDetected:
            motion::drive(0, 0);
            // search.step(inp);
            break;

    }
}

