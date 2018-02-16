#ifndef DDHello_h
#define DDHello_h

#include <Device/DeviceDriver.h>
#include <Device/DeviceTable.h>
#include "LUHello.h"

#define MAX_HELLO_TEXT_LENGTH 31

/**
 * This class defines a simple device driver as an example
 * HelloWorld component for device drivers and their usage.
 */
class DDHello: public DeviceDriver {

public:

  DDHello(const char *unitName = "HELLO", int count = 1);

  int open(int opts, int flags, const char *name);
  int read(int handle, int flags, int reg, int count, byte *buf);
  int write(int handle, int flags, int reg, int count, byte *buf);
  int close(int handle, int flags);

  int processTimerEvent(int lun, int timerSelector, ClientReporter *r);

  enum class REG : int {
    INTERJECTION = 256,
    OBJECT = 257,
  };

};

#endif
