#include "ByteOrder.h"

// define lowByte and highByte so that we don't have to include Arduino.h

#ifndef lowByte
#define lowByte(w) ((uint8_t) ((w) & 0xff))
#endif

#ifndef highByte
#define highByte(w) ((uint8_t) ((w) >> 8))
#endif

void ByteOrder::x1LE(uint8_t src, uint8_t *dst) {
  dst[0] = lowByte(src);
}

void ByteOrder::x1BE(uint8_t src, uint8_t *dst) {
  dst[0] = lowByte(src);
}

void ByteOrder::x2LE(uint16_t src, uint8_t *dst) {
  dst[0] = lowByte(src);
  dst[1] = highByte(src);
}

void ByteOrder::x2BE(uint16_t src, uint8_t *dst) {
  dst[0] = highByte(src);
  dst[1] = lowByte(src);
}

void ByteOrder::x4LE(uint32_t src, uint8_t *dst) {
  dst[0] = (uint8_t)((src >> 0)  & 0xFFuL);
  dst[1] = (uint8_t)((src >> 8)  & 0xFFuL);
  dst[2] = (uint8_t)((src >> 16) & 0xFFuL);
  dst[3] = (uint8_t)((src >> 24) & 0xFFuL);
}

void ByteOrder::x4BE(uint32_t src, uint8_t *dst) {
  dst[0] = (uint8_t)((src >> 24) & 0xFFuL);
  dst[1] = (uint8_t)((src >> 16) & 0xFFuL);
  dst[2] = (uint8_t)((src >> 8)  & 0xFFuL);
  dst[3] = (uint8_t)((src >> 0)  & 0xFFuL);
}

int8_t ByteOrder::p1LE(uint8_t *src) {
  return (int8_t)(((uint16_t)(src[0])) & ((uint16_t)0x00FFu));
}

int8_t ByteOrder::p1BE(uint8_t *src) {
  return (int8_t)(((uint16_t)(src[0])) & ((uint16_t)0x00FFu));
}

int16_t ByteOrder::p2LE(uint8_t *src) {
  return (int16_t)(((src[1] & 0xFFuL) << 8) | (src[0] & 0xFFuL));
}

int16_t ByteOrder::p2BE(uint8_t *src) {
  return (int16_t)(((src[0] & 0xFFuL) << 8) | (src[1] & 0xFFuL));
}

int32_t ByteOrder::p4LE(uint8_t *src) {
  return (int32_t)(
    ((src[3] & 0xFFuL) << 24) |
    ((src[2] & 0xFFuL) << 16) |
    ((src[1] & 0xFFuL) << 8) |
    ((src[0] & 0xFFuL) << 0));
}

int32_t ByteOrder::p4BE(uint8_t *src) {
  return (int32_t)(
    ((src[0] & 0xFFuL) << 24) |
    ((src[1] & 0xFFuL) << 16) |
    ((src[2] & 0xFFuL) << 8) |
    ((src[3] & 0xFFuL) << 0));
}
