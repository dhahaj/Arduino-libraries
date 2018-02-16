/**
 * This program is an example of standalone use of an Arduino device driver
 * from the Luni library.  Compiled and loaded onto an Arduino, it initializes,
 * then briefly demonstrates some of the typical device driver calls.
 */

#include <LuniLib.h>
#include <TestFrame/DeviceDriverTest.h>

// Device Driver selection

#include <DDHello/DDHello.h>
#include <DDMeta/DDMeta.h>

DeviceDriver *selectedDevices[] = {
  new DDHello("HW",1),
  new DDMeta("Meta",1),
  0};

// Test selection

#include <TestBody/TestHello.h>
#include <TestBody/TestCommon.h>

DeviceDriverTest *selectedTests[] {
  new TestCommon("HW:0"),
  new TestHello("HW:0"),
  0
};

TestManager *tst = new TestManager(__FILE__);

// --------------------------------------------------------

void setup() {
  Serial.begin(115200);
  tst->countDown(5);
  tst->runSelected();
}

void loop() {
    tst->dispatchTimers();
}
