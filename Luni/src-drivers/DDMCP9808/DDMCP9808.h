#ifndef DDMCP9808_h
#define DDMCP9808_h

#include <Silicon/I2CPort.h>
#include <Device/DeviceDriver.h>
#include <Device/DeviceTable.h>
#include "LUMCP9808.h"

class DDMCP9808: public DeviceDriver {

public:
  DDMCP9808(const char *unitName = "TC", int count = 8, int base = 0x18);

  int open(int opts, int flags, const char *name);
  int read(int handle, int flags, int reg, int count, byte *buf);
  int write(int handle, int flags, int reg, int count, byte *buf);
  int close(int handle, int flags);

  int processTimerEvent(int lun, int timerSelector, ClientReporter *r);

  enum class REG : int {
    RESERVED = 0,
    CONFIG = 1,
    UPPER_TEMP = 2,
    LOWER_TEMP = 3,
    CRIT_TEMP = 4,
    AMBIENT_TEMP = 5,
    MANUF_ID = 6,
    DEVICE_ID = 7,
    RESOLUTION = 8
  };

private:
  int baseAddress;
  I2CPort i2c;

};

#endif
