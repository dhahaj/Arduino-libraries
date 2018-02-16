/*
  * swDuino.h
  *
  * swDuino - A swDuino 2.0 library for Arduino
  * Author: naveed@swduino.net
  * Website: http://www.swduino.net/
  * Copyright (c) 2015 swDuino
*/

#include "swDuino.h"

swDuino::swDuino() {}

void swDuino::begin(int baudrate) {
  this->swDuinoInputString = "";
  this->swDuinoStringComplete = false;
  Serial.begin(baudrate);
}

void swDuino::write(String VARIABLE, String VALUE) {
  Serial.println ("{"+VARIABLE+"="+VALUE+"}");
}

void swDuino::read(swDuino_callback f) {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      this->swDuinoStringComplete = true;
      int equalsign = swDuinoInputString.indexOf('=');
      String variable = swDuinoInputString.substring(0, equalsign);
      String value  = swDuinoInputString.substring(equalsign + 1);
      f(variable, value);
      this->swDuinoInputString = "";
      this->swDuinoStringComplete = false;
      } else {
      this->swDuinoInputString += inChar;
    }
  }
}