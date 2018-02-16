/**
 *  \file 		ShiftRegister74HC595.h
 *  \revision	rev1.0
 *  \brief 		Library for easy control of the 74HC595 shift register.
 */
 
#ifndef ShiftRegister74HC595_h
#define ShiftRegister74HC595_h

#include "Arduino.h"

class ShiftRegister74HC595 
{
    public:
        ShiftRegister74HC595(int numberOfShiftRegisters, int serialDataPin, int clockPin, int latchPin);
		// ShiftRegister74HC595(void);
        void setAll(uint8_t * digitalValues);
        uint8_t * getAll(); 
        void set(int pin, uint8_t value);
        void setAllLow();
        void setAllHigh(); 
        uint8_t get(int pin);
		uint8_t size;

    private:
        int _numberOfShiftRegisters;
        int _clockPin;
        int _serialDataPin;
        int _latchPin;
        uint8_t * _digitalValues;
};

#endif