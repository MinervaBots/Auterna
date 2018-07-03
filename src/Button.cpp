/*
	Button - a small library for Arduino to handle button debouncing
	
	MIT licensed.
*/

#include "Button.h"
#include <Arduino.h>

Button::Button(uint8_t pin)
:  _pin(pin)
,  _delay(50)
,  _has_changed(false)
,  _ignore_until(0)
{
}

void Button::setState(int state) {
    _initialState = state;
    _state = state;
}

// 
// public methods
// 

bool Button::read()
{
	// ignore pin changes until after this delay time
	if (_ignore_until > millis())
	{
		// ignore any changes during this period
	}
	
	// pin has changed 
	else if (digitalRead(_pin) != _state)
	{
		_ignore_until = millis() + _delay;
		_state = !_state;
		_has_changed = true;
	}
	
	return _state != _initialState;
}

// has the button been toggled from on -> off, or vice versa
bool Button::toggled()
{
	read();
	return has_changed();
}

// mostly internal, tells you if a button has changed after calling the read() function
bool Button::has_changed()
{
	if (_has_changed == true)
	{
		_has_changed = false;
		return true;
	}
	return false;
}

// has the button gone from off -> on
bool Button::pressed()
{
	if (read() == PRESSED && has_changed() == true)
		return true;
	else
		return false;
}

// has the button gone from on -> off
bool Button::released()
{
	if (read() == RELEASED && has_changed() == true)
		return true;
	else
		return false;
}
