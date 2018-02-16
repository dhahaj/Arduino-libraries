#include "LogicalUnitInfo.h"
#include "DeviceDriver.h"
#include "DeviceTable.h"

extern DeviceTable *gDeviceTable;

  LogicalUnitInfo::LogicalUnitInfo() {

  previousTime[0] = 0;
  previousTime[1] = 0;
  intervalTime[0] = 0;
  intervalTime[1] = 0;

  eventAction[0].enabled = false;
  eventAction[1].enabled = false;

  }

  LogicalUnitInfo::~LogicalUnitInfo() {}

//----------------------------------------------------------------------------

// return true if pin was idle, now it's ours
// return false if pin was already in use by someone else

bool LogicalUnitInfo::lockPin(int pin) {
  return (gDeviceTable->claimPin(pin));
}

// return true if pin was ours, now it's not
// return false if pin was not in use by anyone!

bool LogicalUnitInfo::unlockPin(int pin) {
  return (gDeviceTable->releasePin(pin));
}

LogicalUnitInfo NULL_LUI;
const LogicalUnitInfo *OPEN_BUT_NOT_CONFIGURED = &NULL_LUI;

