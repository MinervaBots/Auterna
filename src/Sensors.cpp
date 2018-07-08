#include "Sensors.h"

QTRSensorsRC Sensors::_qtrrc((unsigned char[]) {pins::bef, pins::bdf}, 
  		num_edge_sensors, 2500, QTR_NO_EMITTER_PIN);

unsigned int Sensors::_edgeSensorValues[num_edge_sensors];

Button Sensors::button {pins::button};

void Sensors::sensorsInit() {
    Sensors::button.setState(digitalRead(pins::button));
}

void Sensors::collectInput(Input &inp, Stream &reader) {
    // Read opponent sensors
    inp.opponent[0] = digitalReadFast(pins::oe);
    inp.opponent[1] = digitalReadFast(pins::ode);
    inp.opponent[2] = digitalReadFast(pins::oc);
    inp.opponent[3] = digitalReadFast(pins::odd);
    inp.opponent[4] = digitalReadFast(pins::od);

    // Read edge sensors
    tie(inp.leftEdgeDetected, inp.rightEdgeDetected) = readEdgeSensors();

    // Bluetooth commands
    // if(reader.available())
    //     switch(reader.read()) {
    //         case onSignal:
    //             inp.turnOnCommand = true;
    //             inp.shutdownCommand = false;
    //             break;
    //         case offSignal:
    //             inp.turnOnCommand = false;
    //             inp.shutdownCommand = true;
    //             break;
    //         default:
    //             inp.turnOnCommand = inp.shutdownCommand = false;
    //             break;
    //     }
    // else
    //     inp.turnOnCommand = inp.shutdownCommand = false;

    // Button
    inp.turnOnCommand = Sensors::button.read();
    inp.shutdownCommand = !inp.turnOnCommand;
}

void Sensors::collectMockInput(Input &inp, Stream &reader) {
    // Mock opponent sensor readings
    for(auto &op : inp.opponent)
        op = false;

    // Mock edge sensors readings
    inp.leftEdgeDetected = inp.rightEdgeDetected = false;

    // Mock bluetooth commands
    inp.turnOnCommand = true;
    inp.shutdownCommand = false;
}

tuple<int, int>
Sensors::readEdgeSensors() {
    Sensors::_qtrrc.read(Sensors::_edgeSensorValues);

    return make_tuple(
        Sensors::_edgeSensorValues[0] < edgeSensorThreshold,
        Sensors::_edgeSensorValues[1] < edgeSensorThreshold
    );
}

void Sensors::printInput(const Input &inp, Print &printer) {
    printer.print("Op sensors: [");
    printer.print(inp.opponent[0]);
    printer.print(", ");
    printer.print(inp.opponent[1]);
    printer.print(", ");
    printer.print(inp.opponent[2]);
    printer.print(", ");
    printer.print(inp.opponent[3]);
    printer.print(", ");
    printer.print(inp.opponent[4]);
    printer.println("]");

    printer.print("LeftEdgeDetected: ");
    printer.println(inp.leftEdgeDetected);

    printer.print("RightEdgeDetected: ");
    printer.println(inp.rightEdgeDetected);

    printer.print("turnOnCommand: ");
    printer.println(inp.turnOnCommand);

    printer.print("shutdownCommand: ");
    printer.println(inp.shutdownCommand);
}

bool Sensors::isDetected(const Input &inp) {
    for (int i = 0; i != 5; ++i) {
        if (inp.opponent[i])
            return true;
    }
    return false;
}

bool Sensors::centralDetected(const Input &inp) {
    if(inp.opponent[2])
        return true;
    return false;
}

bool Sensors::isEdgeDetected(const Input &inp) {
    return inp.leftEdgeDetected || inp.rightEdgeDetected;
}

double Sensors::headingError(const bool (&readings)[opponent_sensors_number], const double (&weights)[opponent_sensors_number]) {
    double error = 0;
    int n_triggered = 0;
    for(int i = 0; i < opponent_sensors_number; i++) {
        error += readings[i]*weights[i];
        n_triggered += readings[i];
    }
    return n_triggered == 0 ? 0 : error/n_triggered;
}

