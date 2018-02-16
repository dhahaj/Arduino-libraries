#include "DDMeta.h"
#include <Device/DeviceTable.h>
#include <Device/ByteOrder.h>
#include <limits.h>

//---------------------------------------------------------------------------

extern DeviceTable *gDeviceTable;

/**
 * This DDMeta class is an administrative and development tool.  As a device
 * driver, it provides an API for:
 * <ul>
 * <li>access to the DeviceTable (how many devices, device driver versions, etc)</li>
 * <li>code analysis capabilities (memory usage, timing, etc)</li>
 * </ul>
 */
DDMeta::DDMeta(const char *dName, int count) :
  DeviceDriver(dName, count) {
  DEFINE_VERSION_PRE(0, 9, 0, beta)
}

//---------------------------------------------------------------------------

int DDMeta::open(int opts, int flags, const char *name) {
  int lun;
  int status = DeviceDriver::open(opts, flags, name);
  if (status < 0) return status;

  lun = status;
  LUMeta *currentUnit = new LUMeta();

  logicalUnits[lun] = currentUnit;
  return lun;
}

//---------------------------------------------------------------------------

int DDMeta::read(int handle, int flags, int reg, int count, byte *buf) {
  int status;
  byte versionBuffer[RESPONSE_BUFFER_SIZE];

  // First, handle connection-optional requests

  switch (reg) {

  case (int)(CDR::DriverVersion):
    return DeviceDriver::buildVersionResponse(count, buf);

  case (int)(CDR::UnitNamePrefix):
      return DeviceDriver::buildPrefixResponse(count,buf);

  case (int)(REG::DRIVER_COUNT):
    if (count < 2) return EMSGSIZE;
    fromHostTo16LE(gDeviceTable->deviceCount, buf);
    return 2;

  case (int)(REG::DRIVER_VERSION_LIST):
    for (int idx=0; idx<gDeviceTable->deviceCount; idx++) {
      status = gDeviceTable->read(makeHandle(idx,0), flags, (int)(CDR::DriverVersion), RESPONSE_BUFFER_SIZE, versionBuffer);
      gDeviceTable->cr->reportRead(status, handle, flags, (int)(CDR::DriverVersion), RESPONSE_BUFFER_SIZE, versionBuffer);
    }
    return ESUCCESS;

  case (int)(REG::UNIT_NAME_PREFIX_LIST):
    for (int idx=0; idx<gDeviceTable->deviceCount; idx++) {
      status = gDeviceTable->read(makeHandle(idx,0), flags, (int)(CDR::UnitNamePrefix), RESPONSE_BUFFER_SIZE, versionBuffer);
      gDeviceTable->cr->reportRead(status, handle, flags, (int)(CDR::UnitNamePrefix), RESPONSE_BUFFER_SIZE, versionBuffer);
    }
    return ESUCCESS;
}

  // Second, deal with connection-required requests

  int lun = getUnitNumber(handle);
  if (lun < 0 || lun >= logicalUnitCount) return EINVAL;
  LUMeta *currentUnit = static_cast<LUMeta *>(logicalUnits[lun]);
  if (currentUnit == 0) return ENOTCONN;

  // Take action regarding continuous read, if requested

  if (flags == (int)DAF::MILLI_RUN) {
    DeviceDriver::milliRateRun((int)DAC::READ, handle, flags, reg, count);
  } else if (flags == (int)DAF::MILLI_STOP) {
    DeviceDriver::milliRateStop((int)DAC::READ, handle, flags, reg, count);
  }

  switch (reg) {

  case (int)(CDR::Intervals):
    return DeviceDriver::readIntervals(handle, flags, reg, count, buf);

  case (int)(REG::AVG_INTERVALS):
    return readATI(handle, flags, reg, count, buf);

  default:
    return ENOTSUP;
  }
}

int DDMeta::write(int handle, int flags, int reg, int count, byte *buf) {
  int unitNameLength;

  // First, handle connection-optional requests

  switch (reg) {

  }

  // Second, deal with connection-required requests

  int lun = getUnitNumber(handle);
  if (lun < 0 || lun >= logicalUnitCount) return EINVAL;
  LUMeta *currentUnit = static_cast<LUMeta *>(logicalUnits[lun]);
  if (currentUnit == 0) return ENOTCONN;

  switch (reg) {

  case (int)(CDR::Intervals):
    return DeviceDriver::writeIntervals(handle, flags, reg, count, buf);

  default:
    return ENOTSUP;
  }
}

int DDMeta::close(int handle, int flags) {
  return DeviceDriver::close(handle, flags);
}

//---------------------------------------------------------------------------

// Collect duration samples.  The sample array is actually 0..SAMPLE_COUNT,
// and the useful samples are in 1..SAMPLE_COUNT.

int DDMeta::processTimerEvent(int lun, int timerSelector, ClientReporter *report) {

  LUMeta *cU = static_cast<LUMeta *>(logicalUnits[getUnitNumber(lun)]);
  if (cU == 0) return ENOTCONN;

  switch (timerSelector) {

  case 0:       // microsecond timer
  case 1:       // millisecond timer

    cU->samples[timerSelector][cU->sampleIndex[timerSelector]] = cU->deltaTime[timerSelector];
    cU->isSampleBufferFull[timerSelector] |= (cU->sampleIndex[timerSelector] == SAMPLE_COUNT);
    cU->sampleIndex[timerSelector] = 1 + ((cU->sampleIndex[timerSelector]) % (int)(SAMPLE_COUNT));

    if (timerSelector == 1) {

      int h = cU->eventAction[1].handle;
      int f = cU->eventAction[1].flags;
      int r = cU->eventAction[1].reg;
      int c = min(cU->eventAction[1].count,RESPONSE_BUFFER_SIZE);

      if (cU->eventAction[1].enabled) {
        if ((cU->eventAction[1].action & 0xF) == (int)(DAC::READ))  {
          int status = gDeviceTable->read(h,f,r,c,cU->eventAction[1].responseBuffer);
          report->reportRead(status, h, f, r, c, (const byte *)(cU->eventAction[1].responseBuffer));
          return status;
        }
      }
    }
    return ESUCCESS;

  default:      // unrecognized timer index
    return ENOTSUP;

  }
}

//---------------------------------------------------------------------------

int DDMeta::readATI(int handle, int flags, int reg, int count, byte *buf) {
  unsigned long avg;
  LUMeta *cU = static_cast<LUMeta *>(logicalUnits[getUnitNumber(handle)]);
  if (cU == 0) return ENOTCONN;

  if (count < 8) return EMSGSIZE;

  for (int timerIndex = 0; timerIndex < 2; timerIndex++) {
    unsigned long sum = 0;

    if ((cU->intervalTime[timerIndex] == 0) ||
      (!(cU->isSampleBufferFull[timerIndex]))) {
      return ENODATA;
    }
    for (int idx = 1; idx <= SAMPLE_COUNT; idx++) {
      sum += cU->samples[timerIndex][idx];
    }
    avg = sum / SAMPLE_COUNT;
    fromHostTo32LE(avg, buf + (4 * timerIndex));
  }
  return 8;
}
