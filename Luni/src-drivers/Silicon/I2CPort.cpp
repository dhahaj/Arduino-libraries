#include "I2CPort.h"

//----------------------------------------------------------------------------

I2CPort::I2CPort() {
  Wire.begin();
}

I2CPort::~I2CPort() {
#ifdef WIRE_HAS_END
  Wire.end();
#endif
}

//----------------------------------------------------------------------------

void I2CPort::readBytes(int addr, uint8_t reg, uint8_t *buf, int count) {
  Wire.beginTransmission((uint8_t)addr);
  Wire.write((uint8_t)reg);
  Wire.endTransmission();

  Wire.requestFrom((uint8_t)addr, (uint8_t)count);

  for (int idx = 0; idx < count; idx++) {
    buf[idx] = Wire.read();
  }
}

//----------------------------------------------------------------------------

uint8_t I2CPort::read8(int addr, uint8_t reg) {
  uint8_t bytesRead[1];
  readBytes(addr, reg, bytesRead,1);
  return bytesRead[0];
}

uint8_t I2CPort::read8LE(int addr, uint8_t reg) {
  return read8(addr,reg);
}

uint8_t I2CPort::read8BE(int addr, uint8_t reg) {
  return read8(addr,reg);
}

uint16_t I2CPort::read16LE(int addr, uint8_t reg) {
  uint8_t bytesRead[2];
  readBytes(addr, reg, bytesRead,2);
  return from16LEToHost(bytesRead);
}

uint16_t I2CPort::read16BE(int addr, uint8_t reg) {
  uint8_t bytesRead[2];
  readBytes(addr, reg, bytesRead,2);
  return from16BEToHost(bytesRead);
}

uint32_t I2CPort::read32LE(int addr, uint8_t reg) {
  uint8_t bytesRead[4];
  readBytes(addr, reg, bytesRead,4);
  return from32LEToHost(bytesRead);
}

uint32_t I2CPort::read32BE(int addr, uint8_t reg) {
  uint8_t bytesRead[4];
  readBytes(addr,reg,bytesRead,4);
  return from32BEToHost(bytesRead);
}

//----------------------------------------------------------------------------

void I2CPort::writeBytes(int addr, uint8_t reg, uint8_t *buf, int count) {
  Wire.beginTransmission((uint8_t)addr);
  Wire.write((uint8_t)reg);
  for (int idx = 0; idx < count; idx++) {
    Wire.write(buf[idx]);
  }
  Wire.endTransmission();
}

//----------------------------------------------------------------------------

void I2CPort::write8(int addr, uint8_t reg, uint8_t value) {
  uint8_t bytesToWrite[1];
  bytesToWrite[0] = value;
  writeBytes(addr, reg, bytesToWrite, 1);
}

void I2CPort::write8LE(int addr, uint8_t reg, uint8_t value) {
  write8(addr,reg,value);
}

void I2CPort::write8BE(int addr, uint8_t reg, uint8_t value) {
  write8(addr,reg,value);
}

void I2CPort::write16LE(int addr, uint8_t reg, uint16_t value) {
  uint8_t bytesToWrite[2];
  fromHostTo16LE(value, bytesToWrite);
  writeBytes(addr, reg, bytesToWrite, 2);
}

void I2CPort::write16BE(int addr, uint8_t reg, uint16_t value) {
  uint8_t bytesToWrite[2];
  fromHostTo16BE(value, bytesToWrite);
  writeBytes(addr, reg, bytesToWrite, 4);
}

void I2CPort::write32LE(int addr, uint8_t reg, uint32_t value) {
  uint8_t bytesToWrite[4];
  fromHostTo32LE(value, bytesToWrite);
  writeBytes(addr, reg, bytesToWrite, 4);
}

void I2CPort::write32BE(int addr, uint8_t reg, uint32_t value) {
  uint8_t bytesToWrite[4];
  fromHostTo32BE(value, bytesToWrite);
  writeBytes(addr, reg, bytesToWrite, 4);
}
