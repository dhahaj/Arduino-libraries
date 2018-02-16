#ifndef DDServo_h
#define DDServo_h

#include <Device/DeviceDriver.h>
#include <Device/DeviceTable.h>
#include "LUServo.h"

class DDServo: public DeviceDriver {

public:
  DDServo(const char *unitName = "Servo", int count = 2);

  int open(int opts, int flags, const char *name);
  int read(int handle, int flags, int reg, int count, byte *buf);
  int write(int handle, int flags, int reg, int count, byte *buf);
  int close(int handle, int flags);
  int processTimerEvent(int lun, int timerSelector, ClientReporter *report);

  enum class REG : int {
    PIN = 256,
    RANGE_MICROSECONDS = 257,
    POSITION_DEGREES = 258,
    POSITION_MICROSECONDS = 259
  };

private:
  LUServo *servos;
};

#endif
