#ifndef LUServo_h
#define LUServo_h

#include <Servo.h>

class LUServo: public LogicalUnitInfo, public Servo {

  friend class DDServo;

public:

  LUServo() {}
  ~LUServo() {}

private:
  int pin;
  int minPulse = MIN_PULSE_WIDTH;
  int maxPulse = MAX_PULSE_WIDTH;

  // Track the current continuous write profile.

  int pulseIncrement;
  int stepIncrement = +1;   // +1 or -1
  const int stepCount = 10; // x-axis ticks
  int currentStep = 0;      // x-value

};

#endif
