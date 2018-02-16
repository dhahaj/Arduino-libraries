/**
  @example Pin-Toggle.ino
  @file Pin-Toggle.ino
  @brief Quickly toggling a Pins output
*/

#include <Pin.h>  // Include Pin Library

Pin myPin = Pin(13);  // Create Pin object for digital pin labelled 13 on any of the supported boards

void setup() {
  myPin.setOutput();  // Set Pin to output mode
  myPin.setHigh();  // Set Pin to output high
}

void loop() {
  myPin.toggleState();  // Set Pin to output the opposite of the previous output (HIGH -> LOW, LOW -> HIGH)
  delay(200);  // Wait 200 milliseconds
}
