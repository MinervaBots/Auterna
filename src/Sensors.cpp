#include "Sensors.h"

void Sensors::collectInput(Input &inp, Stream &reader) {
    // Read opponent sensors
    inp.opponent[0] = digitalReadFast(pins::od);
    inp.opponent[1] = digitalReadFast(pins::odd);
    inp.opponent[2] = digitalReadFast(pins::oc);
    inp.opponent[3] = digitalReadFast(pins::ode);
    inp.opponent[4] = digitalReadFast(pins::oe);

    // Read edge sensors
    tie(inp.leftEdgeDetected, inp.rightEdgeDetected) = readEdgeSensorsDigital(pins::bef, pins::bdf);

    // Bluetooth commands
    if(reader.available())
        switch(reader.read()) {
            case onSignal:
                inp.turnOnCommand = true;
                inp.shutdownCommand = false;
                break;
            case offSignal:
                inp.turnOnCommand = false;
                inp.shutdownCommand = true;
                break;
            default:
                inp.turnOnCommand = inp.shutdownCommand = false;
                break;
        }
    else
        inp.turnOnCommand = inp.shutdownCommand = false;
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

tuple<bool, bool>
Sensors::readEdgeSensorsDigital(const int leftEdgeSensorPin, const int rightEdgeSensorPin) {
    return make_tuple(
        digitalReadFast(leftEdgeSensorPin),
        digitalReadFast(rightEdgeSensorPin)
    );
}

tuple<bool, bool>
readEdgeSensorsTiming(const int leftEdgeSensorPin, const int rightEdgeSensorPin, unsigned int timeout = 2000) {
    // Carrega capacitores por 10 us
    pinMode(leftEdgeSensorPin, OUTPUT);
    pinMode(rightEdgeSensorPin, OUTPUT);

    digitalWriteFast(leftEdgeSensorPin, HIGH);
    digitalWriteFast(rightEdgeSensorPin, HIGH);

    delayMicroseconds(10);

    pinMode(leftEdgeSensorPin, INPUT);
    pinMode(rightEdgeSensorPin, INPUT);

    unsigned int leftReading = timeout;
    unsigned int rightReading = timeout;

    bool leftWait = true, rightWait = true; // Marca que os sensores ainda estão aguardando resposta

    bool leftTempReading = 0, rightTempReading = 0;
    
    unsigned int startTime = micros(), time = 0;
    while((time = micros() - startTime) < timeout) {
        if(!(leftTempReading = digitalReadFast(leftEdgeSensorPin)) && leftWait) {
            leftReading = time;
            leftWait = false;
        }

        if(!(rightTempReading = digitalReadFast(rightEdgeSensorPin)) && rightWait) {
            rightReading = time;
            rightWait = false;
        }

        if(!leftWait && !rightWait) break;
    }

    return make_tuple(
        leftReading > Sensors::edgeSensorsTimeThreshold,
        rightReading > Sensors::edgeSensorsTimeThreshold
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
    printer.println(inp.leftEdgeDetected ? "True" : "False");

    printer.print("RightEdgeDetected: ");
    printer.println(inp.rightEdgeDetected ? "True" : "False");
}

