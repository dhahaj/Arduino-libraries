/*For more information, please visit: 
  http://www.swduino.com/?tab=examples&doc=monitor_and_control
  Version: 2.0
*/

#include <swDuino.h>

swDuino objswDuino;

int led=13;

void setup() {
  // put your setup code here, to run once:
  objswDuino.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  objswDuino.write("P", String(analogRead(A0)));
  objswDuino.read(trigger);
  delay(500);
}

void trigger(String VARIABLE, String VALUE) {
  if (VARIABLE == "led")
  {
    if (VALUE == "1")
    {
      digitalWrite(led, HIGH);
    }
    else if (VALUE == "0")
    {
      digitalWrite(led, LOW);
    }
  }
}
