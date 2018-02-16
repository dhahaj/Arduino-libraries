/**
 *
 *  @file	PString.cpp
 *  @revision:	A
 *  
 */

#include "PString.h"

/**
 *  @brief begin
 *  
 *  @return void
 *  
 *  @details Details
 */
void PString::begin(void)
{
  _cur = _buf;
  if (_size > 0) 
		_buf[0] = '\0';
}

/**
 *  @brief write
 *  
 *  @param [uint8_t] b 8-bit unsigned integer.
 *  @return size_t or void
 *  
 *  @details Details
 */
#if defined(ARDUINO) && ARDUINO >= 100
size_t PString::write(uint8_t b)
#else
void PString::write(uint8_t b)
#endif
{
  if (_cur + 1 < _buf + _size)
  {
    *_cur++ = (char)b;
    *_cur = '\0';
#if defined(ARDUINO) && ARDUINO >= 100
	return 1;
#endif
  }

#if defined(ARDUINO) && ARDUINO >= 100
	return 0;
#endif
}

/**
 *  @brief Brief
 *  
 *  @param [char *] str Pointer to a string or char array.
 *  @param [in] ... Parameter_Description
 *  @return Return_Description
 *  
 *  @details Details
 */
int PString::format(char *str, ...)
{ 
  va_list argptr;
  va_start(argptr, str);
  int ret = vsnprintf(_cur, _size - (_cur - _buf), str, argptr);
  if (_size)
    while (*_cur)
			++_cur;
  return ret;
}
