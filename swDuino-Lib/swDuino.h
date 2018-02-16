/*
 * swDuino.h
 *
 * swDuino - A swDuino 2.0 library for Arduino.
 * Author: naveed@swduino.net
 * Website: http://www.swduino.net/
 * Copyright (c) 2015 swDuino
 *
 */

#ifndef SWDUINO_H
#define SWDUINO_H
  
#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
  #else
  #include <WProgram.h>
#endif
  
typedef void (*swDuino_callback)(String VARIABLE, String VALUE);

class swDuino {
  public:
    swDuino();
    void begin(int baudrate);
    void write(String VARIABLE, String VALUE);
    void read(swDuino_callback f);
  private:
    String swDuinoInputString = "";
    boolean swDuinoStringComplete = false;
};
  
#endif