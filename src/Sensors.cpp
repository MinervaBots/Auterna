#include "Sensors.h"

void collectInput(Input &inp, Stream &reader) {
    // Read opponent sensors
    inp.opponent[0] = digitalRead(pins::oc);
    inp.opponent[1] = digitalRead(pins::od);
    inp.opponent[2] = digitalRead(pins::odd);
    inp.opponent[3] = digitalRead(pins::ode);
    inp.opponent[4] = digitalRead(pins::oe);

    // Read edge sensors
    inp.leftEdgeDetected = digitalRead(pins::bef);
    inp.rightEdgeDetected = digitalRead(pins::bdf);

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

void collectMockInput(Input &inp, Stream &reader) {
    // Mock opponent sensor readings
    for(auto &op : inp.opponent)
        op = false;

    // Mock edge sensors readings
    inp.leftEdgeDetected = inp.rightEdgeDetected = false;

    // Mock bluetooth commands
    inp.turnOnCommand = true;
    inp.shutdownCommand = false;
}

