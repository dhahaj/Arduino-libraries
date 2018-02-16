#ifndef DDMeta_h
#define DDMeta_h

#include <Device/DeviceDriver.h>
#include <Device/DeviceTable.h>
#include "LUMeta.h"

class DDMeta: public DeviceDriver {

public:

  DDMeta(const char *unitName = "Meta", int count = 1);

  int open(int opts, int flags, const char *name);
  int read(int handle, int flags, int reg, int count, byte *buf);
  int write(int handle, int flags, int reg, int count, byte *buf);
  int close(int handle, int flags);

  int processTimerEvent(int lun, int timerSelector, ClientReporter *r);

  enum class REG : int {
    AVG_INTERVALS = 256,
    DRIVER_COUNT = 257,
    DRIVER_VERSION_LIST = 258,
    UNIT_NAME_PREFIX_LIST = 259
  };

private:
  const DeviceTable *theDeviceTable;

  int readATI(int handle, int flags, int reg, int count, byte *buf);

  unsigned long calculateAverageInterval(int idx);

};

#endif
