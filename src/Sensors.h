#ifndef SENSOR_READINGS_H
#define SENSOR_READINGS_H

#include <Arduino.h>
#include <tuple>
#include <QTRSensors.h>
#include "pins/pins.h"
#include "Button.h"

using std::tuple;
using std::make_tuple;
using std::tie;

namespace Sensors {
	constexpr char onSignal = '1';
	constexpr char offSignal = '0';
	
	// Opponent sensors constants
	constexpr int opponent_sensors_number = 5;
	constexpr double weights[opponent_sensors_number] = {4, 2, 0, -2, -4};

	// Edge sensors constants
	constexpr int num_samples_per_sensor = 4;
	constexpr int num_edge_sensors = 2;
	constexpr int edgeSensorThreshold = 150;

	extern QTRSensorsRC _qtrrc;
	extern unsigned int _edgeSensorValues[num_edge_sensors];

	// Button
	extern Button button;

	typedef struct {
		bool opponent[opponent_sensors_number]; // Can be optimized into a bitset, in case we need memory
		bool leftEdgeDetected;
		bool rightEdgeDetected;
		bool turnOnCommand;
		bool shutdownCommand;
	} Input;

	void sensorsInit();
	void collectInput(Input &inp, Stream &reader);
	void collectMockInput(Input &inp, Stream &reader);

	// Configurar pinos como INPUT
	tuple<int, int>
	readEdgeSensors();

	void printInput(const Input &inp, Print &printer);

	double pid_control(double error);

    // returns true if at least one of the opponent sensors is triggered
    bool isDetected(const Input &inp);

	// Retursn true if at least one of the edge sensors is triggered	
	bool isEdgeDetected(const Input &inp);
	
    // Returns true if and only if the central opponent sensor is triggered
    bool centralDetected(const Input &inp);

    double headingError(const bool (&readings)[opponent_sensors_number], const double (&weights)[opponent_sensors_number]);
}

#endif
