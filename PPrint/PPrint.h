#ifndef PPRINT_H
#define PPRINT_H


#include <stdio.h> // for size_t

#include "WString.h"
#include "Printable.h"
#include "Print.h"
#include <inttypes.h>

#include "Stream.h"

class PPrint : public HardwareSerial
{
  public:
  
	using Print::write;
  
	// PPrint() : write_error(0){}
	
	// int getWriteError() { return write_error; }
    // void clearWriteError() { setWriteError(0); }
	
	// virtual size_t write(uint8_t) = 0;
    // size_t write(const char *str) {
      // if (str == NULL) return 0;
      // return write((const uint8_t *)str, strlen(str));
    // }
    // virtual size_t write(const uint8_t *buffer, size_t size);
	
	// virtual run();
	// void stop();
	// void tab();
	// void println(char[] cs);
	// void printArray(byte[] cs);
	// bool available();
	// char[] read();
	// void printf(char[] c);
	// void write(char[] c);
	// void printNum(uint8_t n);
	// void printf(char[] cs, char c);
	size_t pp(const String &s);
	size_t ln(const String &s);
	size_t ln(char);
	size_t ln(void);
	size_t printBin(const Printable&);
	
  private:
		int baud;
		int write_error;
  protected:
    void setWriteError(int err = 1) { write_error = err; }
};

extern HardwareSerial s;

extern void serialEventRun(void) __attribute__((weak));


#endif /* PPRINT_H */
