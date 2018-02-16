/**
 * @file			ShiftRegister74HC595.cpp
 * @revision:	rev1.0
**/

#include "Arduino.h"
#include "ShiftRegister74HC595.h"

#define DEBUG_SERIAL 1

uint8_t size;

/**
 *  @brief constructor
 *  
 *  @param [in] numberOfShiftRegisters The number of shift registers
 *  @param [in] serialDataPin          SDA pin
 *  @param [in] clockPin               SCK pin
 *  @param [in] latchPin               Latch Pin
*/
ShiftRegister74HC595::ShiftRegister74HC595(int numberOfShiftRegisters, int serialDataPin, int clockPin, int latchPin) {
    // set attributes
    _numberOfShiftRegisters = numberOfShiftRegisters;
    _clockPin = clockPin;
    _serialDataPin = serialDataPin;
    _latchPin = latchPin;
    
    // define pins as outputs
    pinMode(clockPin, OUTPUT);
    pinMode(serialDataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    
    // set pins low
    digitalWrite(clockPin, LOW);
    digitalWrite(serialDataPin, LOW);
    digitalWrite(latchPin, LOW);
    
    // allocates the specified number of bytes and initializes them to zero
    _digitalValues = (uint8_t *) calloc(numberOfShiftRegisters, sizeof(uint8_t));
    size = sizeof(_digitalValues);
    setAll(_digitalValues); // reset shift register
}

/**
 *  @brief default constructor
 */
/* ShiftRegister74HC595::ShiftRegister74HC595(void) {
	_numberOfShiftRegisters = 1;
    _clockPin = 1;
    _serialDataPin = 0;
    _latchPin = 2;
	
	// define pins as outputs
    pinMode(clockPin, OUTPUT);
    pinMode(serialDataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
	
	digitalWrite(clockPin, LOW);
    digitalWrite(serialDataPin, LOW);
    digitalWrite(latchPin, LOW);
	
	_digitalValues = (uint8_t *) calloc(numberOfShiftRegisters, sizeof(uint8_t));
	setAll(_digitalValues); // reset shift register
} */

/**
 *  @brief setAll
 *  
 *  @param [in] digitalValues Parameter_Description
 *  @return void
 *  
 *  @details Sets all the outputs to the provided value (Most significant bit first)
 */
void ShiftRegister74HC595::setAll(uint8_t * digitalValues) {
    // go through all bytes (most significant byte first)
    for (int byte = 0 ; byte < _numberOfShiftRegisters; byte++) 
			shiftOut(_serialDataPin, _clockPin, MSBFIRST, digitalValues[byte]);
    
    _digitalValues = digitalValues; 
    
    digitalWrite(_latchPin, HIGH); 
    digitalWrite(_latchPin, LOW); 
}

/**
 *  @brief getAll
 *  
 *  @return Values of all the outputs
 *  
 *  @details Details
 */
uint8_t * ShiftRegister74HC595::getAll() {
    return _digitalValues; 
}

/**
 *  @brief ShiftRegister74HC595
 *  
 *  @param [in] pin   The pin to set
 *  @param [in] value The value to set
 *  @return void
 *  
 *  @details Sets a single pin to the specified value
 */
void ShiftRegister74HC595::set(int pin, uint8_t value) {
    if (value == 1)
			_digitalValues[pin / 8] |= 1 << (pin % 8);
    else 
			_digitalValues[pin / 8] &= ~(1 << (pin % 8));
    setAll(_digitalValues);
}

/**
 *  @brief get
 *  
 *  @param [in] pin The pin to read
 *  @return The value of the specified pin
 *  
 *  @details Gets the value of a single pin
 */
uint8_t ShiftRegister74HC595::get(int pin) {
    return (_digitalValues[pin / 8] >> (pin % 8)) & 1;
}

/**
 *  @brief setAllHigh
 *  
 *  @return void
 *  
 *  @details Set all outputs high
 */
void ShiftRegister74HC595::setAllHigh() {
    for (int i = 0; i < _numberOfShiftRegisters; i++)
			_digitalValues[i] = 255;
    setAll(_digitalValues); 
}

/**
 *  @brief setAllLow
 *  
 *  @return void
 *  
 *  @details Set all outputs low
 */
void ShiftRegister74HC595::setAllLow() {
    for (int i = 0; i < _numberOfShiftRegisters; i++) 
			_digitalValues[i] = 0; 
    setAll(_digitalValues); 
}