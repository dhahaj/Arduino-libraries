/**
 *  @file	PString.h - Lightweight printable string class
 *  @revision:	A
 */
 
#ifndef PString_h
#define PString_h

#include "Print.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define PSTRING_LIBRARY_VERSION 3

class PString : public Print
{
private:
  char *_buf, *_cur;
  size_t _size;

public:
#if defined(ARDUINO) && ARDUINO >= 100
	virtual size_t write(uint8_t);
#else
	virtual void write(uint8_t);
#endif

public:

	/**
   *  @brief constructor
   *  
   *  @param [char] buf  pointer to a preallocated buffer
   *  @param [size_t] size Parameter_Description
   *  @return Return_Description
   *  
   *  @details Details
   */
  PString(char *buf, size_t size) : _buf(buf), _size(size)
  {
		begin();
	}

	/**
   *  @brief templated constructors
   *  
   *  @param [char] buf  pointer to a preallocated buffer.
   *  @param [size_t] size Buffer size.
   *  @param [T] arg  Modifier
   *  @return Return_Description
   *  
   *  @details allows inline renderings of this type: PString(buf, size, myfloat[, modifier]);
   */
  template<class T> PString(char *buf, size_t size, T arg) : _buf(buf), _size(size) 
  { begin(); print(arg); }
  
  template<class T> PString(char *buf, size_t size, T arg, int modifier) : _buf(buf), _size(size) 
  { begin(); print(arg, modifier); }

	/**
   *  @brief length
   *  
   *  @return the length of the current string
   *  
   *  @details returns the length of the current string, not counting the 0 terminator
   */
  inline const size_t length(void) 
  { return _cur - _buf; }

  	/**
   *  @brief capacity
   *  
   *  @return string capacity
   *  
   *  @details returns the capacity of the string
   */
  inline const size_t capacity(void) 
  {
		return _size;
	}

  // gives access to the internal string
  inline operator const char *() 
  { return _buf; }

  // compare to another string
	bool operator==(const char *str) 
  { 
		return _size > 0 && !strcmp(_buf, str);
	}

	  /**
	 *  @brief begin
	 *  
	 *  @return void
	 *  
	 *  @details call this to re-use an existing string
	 */
	void begin();

  // This function allows assignment to an arbitrary scalar value like str = myfloat;
	template<class T> inline PString &operator =(T arg) 
  { begin(); print(arg); return *this; }

  // Concatenation str += myfloat;
  template<class T> inline PString &operator +=(T arg) 
  { print(arg); return *this; }

  // Safe access to sprintf-like formatting, e.g. str.format("Hi, my name is %s and I'm %d years old", name, age);
  int format(char *str, ...);
};

#endif