#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
	#else
  #include "WProgram.h"
  #include "pins_arduino.h"
#endif

#include "wiring_private.h"
#include "Debounce.h"

Debounce::Debounce(unsigned long wait_time, int pin)
{
	interval(wait_time);
	previous_millis = millis();
	state = digitalRead(pin);
	this -> pin = pin;
	this -> passed = 0;
}

// Contributed by Jim Schimpf
void Debounce::write(int new_state)
{
	passed = new_state;
	state = new_state;
	digitalWrite(pin, new_state);
}

void Debounce::setPassed()
{
	// write(true);
	this -> passed = true;
}

int Debounce::isFailed()
{
	return passed;
}

int Debounce::isPassed()
{
	int b = passed;
	return b;
	// passed = false;
	// state = new_state;
	// digitalWrite(pin, 1);
}

void Debounce::interval(unsigned long wait_time)
{
  this->wait_time = wait_time;
}

int Debounce::update()
{
	// if(passed){
	// digitalWrite(pin, 1);
	// return 1;
	// }
	uint8_t newState = digitalRead(pin);
	if (state != newState ) {
		if (millis() - previous_millis >= wait_time) {
			previous_millis = millis();
			state = newState;
			return 1;
		}
	}
  return 0;
}

int Debounce::getPin()
{
	int i = pin;
	return (int)i;
}

int Debounce::read()
{
	return (int)state;
}

void Debounce::printParams()
{
	Serial.println("MotorParams:");
	Serial.print("\tpin=");
	Serial.print(pin,DEC);
	Serial.println();
	Serial.print("\tstate=");
	Serial.print(state,DEC);
	Serial.println();
	Serial.print("\tpassed=");
	Serial.print(passed, HEX);
	Serial.println();
}
