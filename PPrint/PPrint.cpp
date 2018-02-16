#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "WString.h"
#include "Printable.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#ifndef _BV
  #define _BV(x) (1 << (x))
#endif

#include "PPrint.h"

/* default implementation: may be overridden */
size_t PPrint::write(const uint8_t *buffer, size_t size)
{
  size_t n = 0;
  while (size--)
    n += write(*buffer++);
  return n;
}

size_t PPrint::print(const __FlashStringHelper *ifsh)
{
  const char PROGMEM *p = (const char PROGMEM *)ifsh;
  size_t n = 0;
  while (1) {
    unsigned char c = pgm_read_byte(p++);
    if (c == 0) break;
    n += write(c);
	}
  return n;
}

size_t PPrint::print(const char str[])
{
  return write(str);
}

String PPrint::replace(const char *format, ...)
{
  String ret;
  int c = timedRead();
  while (c >= 0 && c != terminator) {
    ret += (char)c;
    c = timedRead();
	}
  return ret;
}

void PPrint::init(int b)
{
	Serial.begin(b);
	this->b = b;
	// return write(0);
}

size_t Print::printBin(unsigned long n) {
	char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
	char *str = &buf[sizeof(buf) - 1];

	*str = '\0';

	// prevent crash if called with base == 1
	base = 2;

	do {
		unsigned long m = n;
		n /= base;
		char c = m - base * n;
		*--str = c < 10 ? c + '0' : c + 'A' - 10;
	} while(n);

	return write(str);
}


size_t PPrint::printf(const char c[], char replace)
{
	int size = sizeof(c);
	char buf[size-1]; // Assumes 8-bit chars plus zero byte.
	// char *str = &buf[sizeof(buf) - 1];
	// *str = '\0';
	for(int i=0 ; i<=size ; i++) {
		if(c[i]=='%') {
			c[i] = '\0';
			c[i+1] = replace;
			break;
		}
	}
	return write(buf);
}

void PPrint::println(const char chars[])
{
	size_t n = print(c);
	n += println();
	return n;
}

size_t PPrint::line()
{
	// Serial.println();
	return write('\n');
}

size_t PPrint::tab()
{
	// Serial.print('\t'); 	
	return write('\t');
}


// size_t PPrint::read()
// {
// return Serial.read();
// }

// bool PPrint::available()
// {
// return Serial.available();
// }