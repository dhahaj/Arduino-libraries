/**
  @example Port-Manipulation-Benchmark.ino
  @file Port-Manipulation-Benchmark.ino
*/

void setup() {
  DDRB |= B10000000;  // Set Pin 13 on Arduino Mega to output mode
}

void loop() {
  while(true) {
    PORTB |= B10000000;  // Set Pin 13 on Arduino Mega to output HIGH
    PORTB &= B01111111;  // Set Pin 13 on Arduino Mega to output LOW
  }
}
