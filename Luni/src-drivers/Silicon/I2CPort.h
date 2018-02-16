#ifndef I2CPort_h
#define I2CPort_h

#include "Port.h"
#include <Wire.h>

#define I2C_MIN_7BIT_ADDRESS 0x8
#define I2C_MAX_7BIT_ADDRESS 0x77

class I2CPort : public Port {

public:

  I2CPort();
  ~I2CPort();

  void write8(int addr, uint8_t reg, uint8_t value);
  void write8LE(int addr, uint8_t reg, uint8_t value);
  void write8BE(int addr, uint8_t reg, uint8_t value);
  void write16LE(int addr, uint8_t reg, uint16_t value);
  void write16BE(int addr, uint8_t reg, uint16_t value);
  void write32LE(int addr, uint8_t reg, uint32_t value);
  void write32BE(int addr, uint8_t reg, uint32_t value);

  uint8_t read8(int addr, uint8_t reg);
  uint8_t read8LE(int addr, uint8_t reg);
  uint8_t read8BE(int addr, uint8_t reg);
  uint16_t read16LE(int addr, uint8_t reg);
  uint16_t read16BE(int addr, uint8_t reg);
  uint32_t read32LE(int addr, uint8_t reg);
  uint32_t read32BE(int addr, uint8_t reg);

private:
  void writeBytes(int addr, uint8_t reg, uint8_t *bytesWrite, int count);
  void readBytes(int addr, uint8_t reg, uint8_t *bytesRead, int count);
};

#endif
