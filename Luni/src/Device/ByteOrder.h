#ifndef ByteOrder_h
#define ByteOrder_h

#include <stdint.h>

/**
 * Extract and pack integer values using consecutive source address pointers.
 *
 * The buffer addresses addressOfBytesToPack and addressOfExtractedBytes are
 * both type uint8_t*.
 *
 * The host values that result from packing bytes are returned as signed ints
 * of the specified length NN (ie, int8_t, int16_t, or int32_t).  If these
 * values are assigned to a wider signed integer type by the caller, they will
 * be sign extended.
 *
 * If you don't want sign extension, cast the macro result to uintNN before
 * assigning it to the wider variable.
 *
 * For example:
 *
 * With  buf[0] = 0;
 *       buf[1] = 0x80;
 *
 * // from16LE to long, no explicit cast of macro result
 * long value = from16LEToHost(buf);                  => -32768  (0xFFFF8000)
 *
 * // from16LE to long, macro result cast to uint16_t
 * long value = (uint16_t)from16LEToHost(buf);        => 32768   (0x00008000)
 */

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

// The byte order on the host is Little Endian (LE).

// The byte order in the byte array is Little Endian (LE).

#define from8LEToHost(addressOfBytesToPack) ByteOrder::p1LE((addressOfBytesToPack))
#define from16LEToHost(addressOfBytesToPack) ByteOrder::p2LE((addressOfBytesToPack))
#define from32LEToHost(addressOfBytesToPack) ByteOrder::p4LE((addressOfBytesToPack))

#define fromHostTo8LE(value,addressOfExtractedBytes) ByteOrder::x1LE((value),(addressOfExtractedBytes))
#define fromHostTo16LE(value,addressOfExtractedBytes) ByteOrder::x2LE((value),(addressOfExtractedBytes))
#define fromHostTo32LE(value,addressOfExtractedBytes) ByteOrder::x4LE((value),(addressOfExtractedBytes))

// The byte order in the byte array is Big Endian (BE).

#define from8BEToHost(addressOfBytesToPack) ByteOrder::p1BE((addressOfBytesToPack))
#define from16BEToHost(addressOfBytesToPack) ByteOrder::p2BE((addressOfBytesToPack))
#define from32BEToHost(addressOfBytesToPack) ByteOrder::p4BE((addressOfBytesToPack))

#define fromHostTo8BE(value,addressOfExtractedBytes) ByteOrder::x1BE((value),(addressOfExtractedBytes))
#define fromHostTo16BE(value,addressOfExtractedBytes) ByteOrder::x2BE((value),(addressOfExtractedBytes))
#define fromHostTo32BE(value,addressOfExtractedBytes) ByteOrder::x4BE((value),(addressOfExtractedBytes))

#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

#error "ByteOrder is not implemented for BigEndian hosts yet."

# else
# error "Unrecognized __BYTE_ORDER__ value."
# endif

// These methods perform the extract, swap, and pack operations

class ByteOrder {
public:
  static void x1LE(uint8_t src, uint8_t *dst);
  static void x2LE(uint16_t src, uint8_t *dst);
  static void x4LE(uint32_t src, uint8_t *dst);

  static int8_t p1LE(uint8_t *src);
  static int16_t p2LE(uint8_t *src);
  static int32_t p4LE(uint8_t *src);

  static void x1BE(uint8_t src, uint8_t *dst);
  static void x2BE(uint16_t src, uint8_t *dst);
  static void x4BE(uint32_t src, uint8_t *dst);

  static int8_t p1BE(uint8_t *src);
  static int16_t p2BE(uint8_t *src);
  static int32_t p4BE(uint8_t *src);

};

#endif
