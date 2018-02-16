#include <Device/DeviceDriver.h>

//---------------------------------------------------------------------------

extern DeviceTable *gDeviceTable;

//---------------------------------------------------------------------------

DeviceDriver::DeviceDriver(const char *pre, const int count) :
  unitNamePrefix((char *)pre),
  logicalUnitCount(count),
  logicalUnits(new LogicalUnitInfo * [count]) {

  if (logicalUnits == 0) {  // out of memory
    logicalUnitCount = 0;
  }

  for (int idx = 0; idx < logicalUnitCount; idx++) {
    logicalUnits[idx] = 0;
  }
};

//---------------------------------------------------------------------------

int DeviceDriver::open(int opts, int flags, const char *name) {
  int lun;

  int prefixLength = strcspn(name, ":");
  if ((strlen(unitNamePrefix) != prefixLength) || (strncmp(unitNamePrefix, name, prefixLength) != 0)) {
    return ENODEV;
  }

  lun = atoi(&name[prefixLength + 1]);
  if (lun < 0 || lun >= logicalUnitCount) {
    return ENXIO;
  }

  if (logicalUnits[lun] == 0) {
    return lun;
  }

  if (flags == (int)(DAF::FORCE)) {
    delete logicalUnits[lun];
    return lun;
  } else {
    return EADDRINUSE;
  }

  return ENXIO;
}

int DeviceDriver::close(int handle, int flags) {
  LogicalUnitInfo *currentUnit = logicalUnits[getUnitNumber(handle)];
  if (currentUnit != 0) {
    delete currentUnit;
    logicalUnits[getUnitNumber(handle)] = 0;
  }
  return ESUCCESS;
}

//---------------------------------------------------------------------------

// Any subclass of DeviceDriver that requires additional functionality in its
// processTimerEvent() or reset() methods should override these implementations
// appropriately.

int DeviceDriver::processTimerEvent(int lun, int timerSelector, ClientReporter * r) {
  return ESUCCESS;
}

void DeviceDriver::reset() {}

//---------------------------------------------------------------------------

int DeviceDriver::checkForTimerEvents(ClientReporter *r) {
  int status;
  int result = ESUCCESS;
  for (int lun = 0; lun < logicalUnitCount; lun++) {
    LogicalUnitInfo *currentUnit = logicalUnits[lun];
    if (currentUnit != 0) {
      for (int timer = 0; timer < 2; timer++) {
        if (currentUnit->intervalTime[timer] > 0) {
          currentUnit->deltaTime[timer] = calculateElapsedTime(currentUnit, timer);
          if (currentUnit->deltaTime[timer] >= currentUnit->intervalTime[timer]) {
            status = this->processTimerEvent(lun, timer, r);
            currentUnit->previousTime[timer] = currentUnit->currentTime[timer];
            result = (status == ESUCCESS) ? result : status;
          }
        }
      }
    }
  }
  return result;
}
//---------------------------------------------------------------------------

int DeviceDriver::readIntervals(int handle, int flags, int reg, int count, byte *buf) {
  LogicalUnitInfo *currentUnit = logicalUnits[getUnitNumber(handle)];
  if (currentUnit == 0) return ENOTCONN;
  if (count < 8) return EMSGSIZE;

  fromHostTo32LE(currentUnit->intervalTime[0], &buf[0]);
  fromHostTo32LE(currentUnit->intervalTime[1], &buf[4]);
  return 8;
}

//---------------------------------------------------------------------------

/**
 * [DeviceDriver::writeIntervals description]
 * @param  handle [description]
 * @param  flags  [description]
 * @param  reg    [description]
 * @param  count  [description]
 * @param  buf    [description]
 * @return        [description]
 */
int DeviceDriver::writeIntervals(int handle, int flags, int reg, int count, byte *buf) {
  LogicalUnitInfo *currentUnit = logicalUnits[getUnitNumber(handle)];
  if (currentUnit == 0) return ENOTCONN;
  if (count < 8) return EMSGSIZE;

  currentUnit->intervalTime[0] = from32LEToHost(&buf[0]);
  currentUnit->intervalTime[1] = from32LEToHost(&buf[4]);
  return 8;
}

//---------------------------------------------------------------------------

/**
 * This method returns two null-terminated strings in the given buffer.
 * The first string is the unit name associated with this device driver when
 * the constructor was originally called during compile and link.  The second
 * string is the name of the device driver, the same name as in the version
 * response, but without any of the release information.  Note that these are
 * two distinct null-terminated strings.  The second string starts after the
 * null that terminates the first string.
 *
 * @param  count The number of bytes in the provided buffer
 * @param  buf   The buffer in which to return the two strings
 * @return       Two null-terminated strings: the unit name root and the name
 * of the device driver
 */
int DeviceDriver::buildPrefixResponse(int count, byte *buf) {
  int scopeNameLength = strlen(scopeName);
  int prefixLength = strlen(unitNamePrefix);
  if (count < prefixLength + scopeNameLength + 2) return EMSGSIZE;
  strlcpy((char *)buf, unitNamePrefix,count);
  strlcpy((char *)buf+prefixLength+1, scopeName, count);
  return prefixLength + scopeNameLength + 2;
}

//---------------------------------------------------------------------------

int DeviceDriver::buildVersionResponse(int count, byte *buf) {

  int packetSize = releaseVersion[0];
  int nameLength = strlen(scopeName);
  int prLength = strlen(preReleaseLabel);
  int bLength = strlen(buildLabel);

  if (count < (1 + packetSize + nameLength + 1 + prLength + 1 + bLength + 1)) {
    return EMSGSIZE;
  }

  int byteIndex = 0;

  // name (including terminating null)

  for (int idx = 0; idx <= nameLength; idx++) {
    buf[byteIndex++] = scopeName[idx];
  }

  // version

  buf[byteIndex++] = packetSize;
  for (int idx = 0; idx < packetSize; idx++) {
    buf[byteIndex++] = releaseVersion[idx + 1];
  }

  // preReleaseLabel (including terminating null)

  for (int idx = 0; idx <= prLength; idx++) {
    buf[byteIndex++] = preReleaseLabel[idx];
  }

  // buildLabel (including terminating null)

  for (int idx = 0; idx <= bLength; idx++) {
    buf[byteIndex++] = buildLabel[idx];
  }

  return byteIndex;
}

//---------------------------------------------------------------------------

unsigned long DeviceDriver::calculateElapsedTime(LogicalUnitInfo *lui, int timerIndex) {
  unsigned long elapsedTime;

  lui->currentTime[timerIndex] = (timerIndex == 0) ? micros() : millis();

  if (lui->currentTime[timerIndex] >= lui->previousTime[timerIndex]) {
    elapsedTime = lui->currentTime[timerIndex] - lui->previousTime[timerIndex];
  } else {
    elapsedTime = (ULONG_MAX - lui->previousTime[timerIndex]) + (lui->currentTime[timerIndex] + 1);
  }
  return elapsedTime;
}

//---------------------------------------------------------------------------

int DeviceDriver::microRateRun(int action, int handle, int flags, int reg, int count, byte *buf) {
  return timerRateRun(0, action, handle, flags, reg, count, buf);
}

int DeviceDriver::milliRateRun(int action, int handle, int flags, int reg, int count, byte *buf) {
  return timerRateRun(1, action, handle, flags, reg, count, buf);
}

int DeviceDriver::microRateStop(int action, int handle, int flags, int reg, int count, byte *buf) {
  return timerRateStop(0, action, handle, flags, reg, count, buf);
}

int DeviceDriver::milliRateStop(int action, int handle, int flags, int reg, int count, byte *buf) {
  return timerRateStop(1, action, handle, flags, reg, count, buf);
}

int DeviceDriver::timerRateRun(int timerSelector,int action, int handle, int flags, int reg, int count, byte *buf) {
  int lun = getUnitNumber(handle);
  if (lun < 0 || lun >= logicalUnitCount) return EINVAL;
  LogicalUnitInfo *currentUnit = logicalUnits[lun];
  if (currentUnit == 0) return ENOTCONN;

  if (timerSelector != 0 && timerSelector != 1) return EINVAL;
  if (flags != (int)(DAF::MILLI_RUN) && flags != (int)(DAF::MICRO_RUN)) return EINVAL;

  currentUnit->eventAction[timerSelector].action = action;
  currentUnit->eventAction[timerSelector].handle = handle;
  currentUnit->eventAction[timerSelector].flags = flags;
  currentUnit->eventAction[timerSelector].reg = reg;
  currentUnit->eventAction[timerSelector].count = count;
  currentUnit->eventAction[timerSelector].enabled = true;
  return ESUCCESS;
}

int DeviceDriver::timerRateStop(int timerSelector, int action, int handle, int flags, int reg, int count, byte *buf) {
  int lun = getUnitNumber(handle);
  if (lun < 0 || lun >= logicalUnitCount) return EINVAL;
  LogicalUnitInfo *currentUnit = logicalUnits[lun];
  if (currentUnit == 0) return ENOTCONN;

  if (timerSelector != 0 && timerSelector != 1) return EINVAL;
  if (flags != (int)(DAF::MILLI_STOP) && flags != (int)(DAF::MICRO_STOP)) return EINVAL;

  currentUnit->eventAction[timerSelector].enabled = false;
  return ESUCCESS;
}
