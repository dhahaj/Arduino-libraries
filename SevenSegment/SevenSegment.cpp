/**
 *  \file SevenSegment.cpp
 *  
 *  \brief Brief Helper for using seven-segment displays
 */
 
 #include "SevenSegment.h"
 
 // static inline void begin(){
	// SevenSegment sevenSegment;
 // }
 
 SevenSegment::SevenSegment() {
	COM_X = 1;
 }
 
 SevenSegment::SevenSegment(uint8_t i) {
	COM_X = i;
 }
 
 void SevenSegment::begin(){
	
 }
 
 uint8_t	 SevenSegment::getDisplay(){
	uint8_t display[] = { ZERO, ONE, TWO, THREE };
	return &display;
 }
 
 // class SevenSegment 
 // {
	 
	// static void begin(uint8_t type)
	// {
		// COM_X = type;
	// }
	 
 // }