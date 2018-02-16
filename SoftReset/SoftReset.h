/**
  * SoftReset.h: A library for access to soft reset macros  
**/

#pragma once

#include <avr/wdt.h>

#ifdef TIMEOUT
#define soft_reset() do { wdt_enable(TIMEOUT); for(;;) { } } while(0)
#else
#define soft_reset() do { wdt_enable(WDTO_2S); for(;;) { } } while(0)
#endif

