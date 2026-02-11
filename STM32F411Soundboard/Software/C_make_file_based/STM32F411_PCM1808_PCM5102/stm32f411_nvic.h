//----------------------------------------------------------------------------------------------------------------------------------

#ifndef __STM32F411_NVIC_H_
#define __STM32F411_NVIC_H_

//----------------------------------------------------------------------------------------------------------------------------------

#include "stm32_types.h"

//----------------------------------------------------------------------------------------------------------------------------------
//Structure definition(s)
//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  __IOM uint32 ISER[8];               //Offset: 0x000 (R/W)  Interrupt Set Enable Register
        uint32 RESERVED0[24];
  __IOM uint32 ICER[8];               //Offset: 0x080 (R/W)  Interrupt Clear Enable Register
        uint32 RSERVED1[24];
  __IOM uint32 ISPR[8];               //Offset: 0x100 (R/W)  Interrupt Set Pending Register
        uint32 RESERVED2[24];
  __IOM uint32 ICPR[8];               //Offset: 0x180 (R/W)  Interrupt Clear Pending Register
        uint32 RESERVED3[24];
  __IOM uint32 IABR[8];               //Offset: 0x200 (R/W)  Interrupt Active bit Register
        uint32 RESERVED4[56];
  __IOM uint8  IP[240];               //Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide)
        uint32 RESERVED5[644];
  __OM  uint32 STIR;                   //Offset: 0xE00 ( /W)  Software Trigger Interrupt Register
}  NVIC_Type;

//----------------------------------------------------------------------------------------------------------------------------------
//Base address definition(s)
//----------------------------------------------------------------------------------------------------------------------------------

#define NVIC                ((NVIC_Type *) 0xE000E100)

//----------------------------------------------------------------------------------------------------------------------------------
//Macros to enable or disable an interrupt and set the priority
//----------------------------------------------------------------------------------------------------------------------------------

//The interrupt enable uses an array of 32 bit registers, which can only be used to enable an interrupt. To disable the ICER registers need to be used.
//Each register serves 32 interrupts, so to get the register for the interrupt, shift the IRQ number right 5 times (divide by 32) and to get
//the right interrupt enable bit, shift an unsigned 32 bit integer 1 the IRQ number anded with 31 (modulo 32) times to the right

#define enable_interrupt(int_id)                   NVIC->ISER[int_id >> 0x05] = (uint32)1 << (int_id & 0x1F)

#define disable_interrupt(int_id)                  NVIC->ICER[int_id >> 0x05] = (uint32)1 << (int_id & 0x1F)

//The priority is set in an array of 8 bit registers, of which only the upper 4 bits are used for the priority allowing for 16 levels
//By using grouping, this is separated to allow for having sub priorities within a single group.
//The higher the number the lower the priority

#define set_interrupt_priority(int_id, priority)   NVIC->IP[int_id] = priority

//----------------------------------------------------------------------------------------------------------------------------------

#endif //__STM32F411_NVIC_H_

//----------------------------------------------------------------------------------------------------------------------------------
