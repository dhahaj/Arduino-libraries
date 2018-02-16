#include <LuniLib.h>

// Device Drivers

#include <DDHello/DDHello.h>
// #include <DDMCP9808/DDMCP9808.h>
// #include <DDMeta/DDMeta.h>
// #include <DDServo/DDServo.h>

DeviceDriver *selectedDevices[] = {
  new DDHello("Hello",1),
//  new DDMCP9808("MCP9808",1,0x18),
//  new DDMeta("Meta",1),
//  new DDServo("Servo",2),
  0};
