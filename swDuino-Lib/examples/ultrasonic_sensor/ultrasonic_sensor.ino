/*For more information, please visit: 
  http://www.swduino.com/?tab=examples&doc=ultrasonicsensor
  Version: 2.0
*/

#include <swDuino.h>

swDuino objswDuino;

const int echoPin = 11;
const int trigPin = 12;

void setup() {
  // put your setup code here, to run once:
  objswDuino.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:

  long duration, cm;

  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  cm = duration / 29 / 2;

  objswDuino.write("S", String(cm));
  
  delay(500);
}
