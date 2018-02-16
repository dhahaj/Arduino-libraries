#ifndef LogicalUnitInfo_h
#define LogicalUnitInfo_h

#include <arduino.h>
#include "DeviceDefine.h"

class LogicalUnitInfo {

  friend class DeviceDriver;
  friend class DDMeta;              // in order to have access to the intervalTimes

public:
  LogicalUnitInfo();
  virtual ~LogicalUnitInfo();

  struct RateAction {
    bool enabled;
    int action;
    int handle;
    int flags;
    int reg;
    int count;
    byte queryBuffer[QUERY_BUFFER_SIZE];
    byte responseBuffer[RESPONSE_BUFFER_SIZE];
  };

  // timer[0] counts in microseconds, timer[1] counts in milliseconds

  unsigned long intervalTime[2];    // desired length of time between calls to update() and report()
  unsigned long previousTime[2];    // the time the last interval expired
  unsigned long currentTime[2];     // the current values from micros() and millis()
  unsigned long deltaTime[2];       // amount of time since last interval expired
  RateAction eventAction[2];        // action to take when timer expires

protected:

    bool lockPin(int p);
    bool unlockPin(int p);

};

#endif
