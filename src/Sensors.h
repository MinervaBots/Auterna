#ifndef SENSOR_READINGS_H
#define SENSOR_READINGS_H

#include <Arduino.h>
#include <tuple>
#include <QTRSensors.h>
#include "pins/pins.h"

using std::tuple;
using std::make_tuple;
using std::tie;

namespace Sensors {
	typedef struct {
		bool opponent[5]; // Can be optimized into a bitset, in case we need memory
		int leftEdgeDetected;
		int rightEdgeDetected;
		bool turnOnCommand;
		bool shutdownCommand;
	} Input;

	constexpr char onSignal = '1';
	constexpr char offSignal = '0';
	
	// Edge sensors constants
	constexpr int num_samples_per_sensor = 4;
	constexpr int num_edge_sensors = 2;
	constexpr int edgeSensorThreshold = 150;

	extern QTRSensorsRC _qtrrc;
	extern unsigned int _edgeSensorValues[num_edge_sensors];

	void collectInput(Input &inp, Stream &reader);
	void collectMockInput(Input &inp, Stream &reader);

	// Configurar pinos como INPUT
	tuple<int, int>
	readEdgeSensors();

	void printInput(const Input &inp, Print &printer);
}

#endif
