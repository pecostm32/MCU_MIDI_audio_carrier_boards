//----------------------------------------------------------------------------------------------------------------------------------

#ifndef __STM32_TYPES_H_
#define __STM32_TYPES_H_

//----------------------------------------------------------------------------------------------------------------------------------

#define     __IO     volatile

#define     __IM     volatile const      //Defines 'read only' structure member permissions
#define     __OM     volatile            //Defines 'write only' structure member permissions
#define     __IOM    volatile            //Defines 'read / write' structure member permissions

//----------------------------------------------------------------------------------------------------------------------------------

typedef signed long long     int64;
typedef signed int           int32;
typedef signed short         int16;
typedef signed char          int8;

typedef unsigned long long   uint64;
typedef unsigned int         uint32;
typedef unsigned short       uint16;
typedef unsigned char        uint8;

//----------------------------------------------------------------------------------------------------------------------------------
//Union for easy access of bytes in a 16 bit word

typedef union
{
  uint16 word;
  struct BYTES
  {
    uint8 low;
    uint8 high;
  } bytes;
} wbcombi;

//----------------------------------------------------------------------------------------------------------------------------------

#endif //__STM32_TYPES_H_
