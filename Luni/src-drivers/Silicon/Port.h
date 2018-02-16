#ifndef Port_h
#define Port_h

#include <inttypes.h>
#include <Device/ByteOrder.h>

/**
 * This abstract class defines some basic methods available for
 * reading and writing using various board level interfaces.  It
 * is intended as a very simple wrapper around the various
 * libraries available so that the underlying libraries can
 * change and simple applications won't be affected.
 *
 * Direct use of calls to the underlying library are always available
 * too if needed for more esoteric applications.
 *
 * The LE (LittleEndian) and BE (BigEndian) suffixes refer to the order in
 * which the bytes of a multi-byte quantity go to or from the attached device.
 * It's very possible, for example, to have devices that expect BE byte order
 * attached to LE hosts, and so these methods allow the user to easily match
 * the device's needs.  The byte order of the host is determined at compile
 * time and the code is adjusted to select the order in which the bytes are
 * addressed locally.
 */
class Port {

public:

  Port();
  ~Port();

  virtual void write8LE(int addr, uint8_t reg, uint8_t value) = 0;
  virtual void write8BE(int addr, uint8_t reg, uint8_t value) = 0;
  virtual void write16LE(int addr, uint8_t reg, uint16_t value) = 0;
  virtual void write16BE(int addr, uint8_t reg, uint16_t value) = 0;
  virtual void write32LE(int addr, uint8_t reg, uint32_t value) = 0;
  virtual void write32BE(int addr, uint8_t reg, uint32_t value) = 0;

  virtual uint8_t read8LE(int addr, uint8_t reg) = 0;
  virtual uint8_t read8BE(int addr, uint8_t reg) = 0;
  virtual uint16_t read16LE(int addr, uint8_t reg) = 0;
  virtual uint16_t read16BE(int addr, uint8_t reg) = 0;
  virtual uint32_t read32LE(int addr, uint8_t reg) = 0;
  virtual uint32_t read32BE(int addr, uint8_t reg) = 0;

  virtual void enable();
  virtual void disable();
  virtual bool isEnabled();
};

#endif
