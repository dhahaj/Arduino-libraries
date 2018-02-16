#include "DDHello.h"

//---------------------------------------------------------------------------

extern DeviceTable *gDeviceTable;

/**
 * This class defines a simple device driver as a sort of
 * HelloWorld component for device drivers and their usage.
 */
DDHello::DDHello(const char *dName, int count) : DeviceDriver(dName, count) {
  DEFINE_VERSION_PRE(0, 9, 0, beta)
}

//---------------------------------------------------------------------------

int DDHello::open(int opts, int flags, const char *name) {
  int lun;
  int status = DeviceDriver::open(opts, flags, name);
  if (status < 0) {
    return status;
  }

  lun = status;
  LUHello *currentUnit = new LUHello("World");

  // Any further validation of the current unit's appropriateness goes here ...

  logicalUnits[lun] = currentUnit;
  return lun;
}

//---------------------------------------------------------------------------

int DDHello::read(int handle, int flags, int reg, int count, byte *buf) {

  if (count < 0) return EINVAL;

  // First, handle connection-optional requests

  switch (reg) {

  case (int)(CDR::DriverVersion):
    return DeviceDriver::buildVersionResponse(count, buf);

  case (int)(CDR::UnitNamePrefix):
      return DeviceDriver::buildPrefixResponse(count,buf);

  case (int)(CDR::Intervals):
    return DeviceDriver::readIntervals(handle, flags, reg, count, buf);

 }

  // Second, deal with connection-required requests

  int lun = getUnitNumber(handle);
  if (lun < 0 || lun >= logicalUnitCount) return EINVAL;
  LUHello *currentUnit = static_cast<LUHello *>(logicalUnits[lun]);
  if (currentUnit == 0) return ENOTCONN;

  // Take action regarding continuous read, if requested

  if (flags == (int)DAF::MILLI_RUN) {
    DeviceDriver::milliRateRun((int)DAC::READ, handle, flags, reg, count);
  } else if (flags == (int)DAF::MILLI_STOP) {
    DeviceDriver::milliRateStop((int)DAC::READ, handle, flags, reg, count);
  }

  switch (reg) {

  case (int)(CDR::Stream):
    if ((size_t)count >= (strlen(currentUnit->getWho()) + strlen(currentUnit->getWhat()) + 4)) {
      buf[0] = (uint8_t)'\0';
      strcat((char *)buf, currentUnit->getWhat());
      strcat((char *)buf, ", ");
      strcat((char *)buf, currentUnit->getWho());
      strcat((char *)buf, "!");
      return strlen((char *)buf);
    } else {
      return EMSGSIZE;
    }

  case (int)(REG::INTERJECTION):
    strlcpy((char *)buf, currentUnit->getWhat(), count);
    return strlen(currentUnit->getWhat());

  case (int)(REG::OBJECT):
    strlcpy((char *)buf, currentUnit->getWho(), count);
    return strlen(currentUnit->getWho());

  default:
    return ENOTSUP;
  }
}

int DDHello::write(int handle, int flags, int reg, int count, byte *buf) {

  // First, handle connection-optional requests

  switch (reg) {

  case (int)(CDR::Intervals):
    return DeviceDriver::writeIntervals(handle, flags, reg, count, buf);

  }

  // Second, deal with connection-required requests

  int lun = getUnitNumber(handle);
  if (lun < 0 || lun >= logicalUnitCount) return EINVAL;
  LUHello *currentUnit = static_cast<LUHello *>(logicalUnits[lun]);
  if (currentUnit == 0) return ENOTCONN;

  switch (reg) {

  case (int)(REG::INTERJECTION):
    currentUnit->setWhat((char *)buf);
    return strlen(currentUnit->getWhat());

  case (int)(REG::OBJECT):
    currentUnit->setWho((char *)buf);
    return strlen(currentUnit->getWho());

  default:
    return ENOTSUP;
  }
  return EPANIC;
}

int DDHello::close(int handle, int flags) {
  return DeviceDriver::close(handle, flags);
}

//---------------------------------------------------------------------------

// If a continuous read has been requested, process it.

int DDHello::processTimerEvent(int lun, int timerSelector, ClientReporter *report) {

  LogicalUnitInfo *cU = logicalUnits[getUnitNumber(lun)];
  if (cU == 0) return ENOTCONN;

  int h = cU->eventAction[1].handle;
  int f = cU->eventAction[1].flags;
  int r = cU->eventAction[1].reg;
  int c = min(cU->eventAction[1].count,RESPONSE_BUFFER_SIZE);

  if (timerSelector == 1) {
    if (cU->eventAction[1].enabled) {
      if ((cU->eventAction[1].action & 0xF) == (int)(DAC::READ))  {
        int status = gDeviceTable->read(h,f,r,c,cU->eventAction[1].responseBuffer);
        report->reportRead(status, h, f, r, c, (const byte *)(cU->eventAction[1].responseBuffer));
        return status;
      }
    }
  }
  return ESUCCESS;
}
