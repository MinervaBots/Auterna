#ifndef SENSOR_READINGS_H
#define SENSOR_READINGS_H

#include <Arduino.h>
#include <tuple>
#include "pins.h"

using std::tuple;
using std::make_tuple;
using std::tie;

namespace Sensors {
	typedef struct {
		bool opponent[5]; // Can be optimized into a bitset, in case we need memory
		bool leftEdgeDetected;
		bool rightEdgeDetected;
		bool turnOnCommand;
		bool shutdownCommand;
	} Input;

	constexpr char onSignal = '1';
	constexpr char offSignal = '0';

	constexpr int edgeSensorsTimeThreshold = 150;

	void collectInput(Input &inp, Stream &reader);
	void collectMockInput(Input &inp, Stream &reader);

	// Configurar pinos como INPUT_PULLUP
	tuple<bool, bool>
	readEdgeSensorsDigital(const int leftEdgeSensorPin, const int rightEdgeSensorPin);

	// Configurar pinos como INPUT
	tuple<bool, bool>
	readEdgeSensorsTiming(const int leftEdgeSensorPin, const int rightEdgeSensorPin, int timeout = 2000);

	void printInput(const Input &inp, Print &printer);
}


#endif
