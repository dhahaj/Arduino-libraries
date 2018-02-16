/*For more information, please visit: 
  http://www.swduino.com/?tab=examples&doc=monitor
  or
  http://www.swduino.com/?tab=examples&doc=monitor_stream
  Version: 2.0
*/

#include <swDuino.h>

swDuino objswDuino;

void setup() {
  // put your setup code here, to run once:
  objswDuino.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  objswDuino.write("P", String(analogRead(A0)));
  delay(500);
}
