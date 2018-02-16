/****************************************************************/
/*   SoftReset.h: A library for access to soft reset macros     */
/****************************************************************/

#include "SoftReset.h"

// You may define an alternative time
// #define TIMEOUT WDTO_1S

void setup(void)
{
  Serial.begin(115200);
  Serial.println("*************************************\n**" \
                 "Software Reset Example Program  **\n" \
                 "*************************************\n");
}

void loop(void)
{
  delay(300);
  if (Serial.available() > 0) {
    Serial.println("Reseting sketch now...\n\n");
    soft_reset();
  }
}