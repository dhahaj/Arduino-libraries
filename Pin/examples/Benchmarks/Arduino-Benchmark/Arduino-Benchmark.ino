/**
  @example Arduino-Benchmark.ino
  @file Arduino-Benchmark.ino
*/

#define PIN 13  // Define PIN for digital pin labelled 13 on any of the supported boards

void setup() {
  pinMode(PIN, OUTPUT);  // Set PIN to output mode
}

void loop() {
  while(true) {
    digitalWrite(PIN, HIGH);  // Set PIN to output HIGH
    digitalWrite(PIN, LOW);  // Set PIN to output LOW
  }
}
