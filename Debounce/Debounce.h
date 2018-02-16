

#ifndef Debounce_h
#define Debounce_h

#include <inttypes.h>

class Debounce
{

public:
  Debounce(unsigned long interval_millis, int pin );
  void interval(unsigned long interval_millis);
  int update();
  int read();
  // Contributed by Jim Schimpf
  void write(int new_state);
  int getPin();
  int isPassed();
  void setPassed();
  int isFailed();
  void printParams();
	
private:
  uint8_t pin;
  unsigned long previous_millis, wait_time;
  uint8_t state;
  
  int passed;
};

#endif


