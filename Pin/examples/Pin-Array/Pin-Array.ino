/**
  @example Pin-Array.ino
  @file Pin-Array.ino
*/

#include <Pin.h>  // Include Pin Library

// Create array of Pin objects for digital pins labelled 2-9 on any of the supported boards
Pin myPins[] = {
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9
}; 

// Store the length of the array of Pins
unsigned int myPinsSize = (sizeof(myPins) / sizeof(Pin)); 

void setup() {
  for (int i = 0; i < myPinsSize; i++)  // Iterate over array of Pins
    myPins[i].setOutput();  // Set Pin to output
}

void loop() {
  int i;
  for (i = 0; i < myPinsSize; i++)  // Iterate over array of Pins
    myPins[i].setLow();  // Set Pin to low

  delay(200);  // Wait 200 milliseconds

  for (i = 0; i < myPinsSize; i++)  // Iterate over array of Pins
    myPins[i].setHigh();  // Set Pin to high

  delay(200);  // Wait 200 milliseconds

}

