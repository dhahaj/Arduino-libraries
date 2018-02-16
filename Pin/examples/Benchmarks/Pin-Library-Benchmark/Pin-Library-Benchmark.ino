/**
  @example Pin-Library-Benchmark.ino
  @file Pin-Library-Benchmark.ino
*/

#include <Pin.h>  // Include Pin Library

Pin myPin = Pin(13);  // Create Pin object for digital pin labelled 13 on any of the supported boards

void setup() {
  myPin.setOutput();  // Set Pin to output
}

void loop() {
  while(true) {
    myPin.setHigh();  // Set Pin to output HIGH
    myPin.setLow();  // Set Pin to output LOW
  }
}
