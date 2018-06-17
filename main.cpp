#include <iostream>
#include "Auterna/Auterna.h"
#include "Sensors.h"

int main() {
    // Entrypoint state machine
    Auterna auterna;

    // Sample input
    Input inp;
    // loop
    while(true) {
        inp = collectInput();
        auterna.step(inp);
    }
}

