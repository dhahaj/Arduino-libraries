/**
 *  7Segment.h
 *  Helper file for interfacing with 7-segment displays
 *  
 *  @author dmh
 *  
 */

#ifndef _SEVENSEGMENT_H
#define _SEVENSEGMENT_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class SevenSegment {

public:

	SevenSegment();
	SevenSegment(uint8_t i);
	uint8_t COM_X;
	void begin();
	uint8_t getDisplay();
	
private:	

};

// #ifndef COM_ANODE 
// #ifndef COM_CATHODE
	// #error MUST DEFINE COM_ANODE OR COM_CATHODE!
// #endif
// #endif

#ifdef COM_CATHODE
	#define ZERO	0x3F
	#define ONE		0x06
	#define TWO		0x5B
	#define THREE	0x4F
	#define FOUR	0x66
	#define FIVE	0x6D
	#define SIX		0x7D
	#define SEVEN	0x07
	#define EIGHT	0x7F
	#define NINE	0x6F
	#define A		0x66
	#define B		0x6D
	#define C		0x7D
	#define D		0x07
	#define E		0x7F
	#define F		0x6F
#endif

#ifdef COM_ANODE
	#define ZERO	0xC0
	#define ONE		0xF9
	#define TWO		0xA4
	#define THREE	0xB0
	#define FOUR	0x99
	#define FIVE	0x92
	#define SIX		0x82
	#define SEVEN	0xF8
	#define EIGHT	0x80
	#define NINE	0x90
	#define A		0x88
	#define B		0x83
	#define C		0xC6
	#define D		0xA1
	#define E		0x86
	#define F		0x8E
#endif
// #endif


#endif  /* _SEVENSEGMENT_H  */