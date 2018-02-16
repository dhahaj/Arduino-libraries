##LuniLib

###An Arduino library to enable the creation and use of device driver modules with local and remote access.

####Summary

Implements a framework for device drivers for use on the Arduino.

####Release v0.8, May 2016

First release for beta testing.  

This library is part of several concurrent v0.8 releases:

- This Arduino library LuniLib
- Update to Configurable Firmata (Arduino Firmata host connection to remote clients)
- LuniJS (Javascript NodeJS client package)
- LuniFive (Javascript Johnny-Five client controller examples)

There are initially three ways to use this library.

1.  Standalone LuniLib.  All code is on the Arduino and there is no external control of the various device drivers.  There are examples included in the library. Only the LuniLib itself is needed for this configuration.
2.  NodeJS and LuniLib.  The device driver library (and a device driver or two), along with an updated Configurable Firmata are on the Arduino, and NodeJS is running on a client.  Required packages are Arduino LuniLib, updated Configurable Firmata, and lunijs, an addon to firmata.js.
3.  Johnny-Five and LuniLib.The device driver library (and a device driver or two), along with an updated Configurable Firmata are on the Arduino, and Johnny-Five is running on a client.  All four packages listed above are needed in this configuration.
