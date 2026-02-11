//----------------------------------------------------------------------------------------------------------------------------------

#include "stm32f411_main.h"

//----------------------------------------------------------------------------------------------------------------------------------
//Vector table is setup in flash at the ".vectors" location, which is defined in the linker script file stm32f411-512k.ld
//See ST manual PM0214 chapter 2.3.4
//List from RM0383 chapter 10.2
//----------------------------------------------------------------------------------------------------------------------------------

//Vectors for STM32F411xx devices.
const void * intVectors[102] __attribute__((section(".vectors"))) =
{                          //Address     (POS)  Acronym
    (void*) STACK_TOP,     //0x00000000
    resetHandler,          //0x00000004         Reset
    0,                     //0x00000008         NMI
    0,                     //0x0000000C         HardFault
    0,                     //0x00000010         MemManage
    0,                     //0x00000014         BusFault
    0,                     //0x00000018         UsageFault
    0,                     //0x0000001C         Reserved
    0,                     //0x00000020         Reserved
    0,                     //0x00000024         Reserved
    0,                     //0x00000028         Reserved
    0,                     //0x0000002C         SVCall
    0,                     //0x00000030         Debug Monitor
    0,                     //0x00000034         Reserved
    0,                     //0x00000038         PendSV
    0,                     //0x0000003C         SysTick
    0,                     //0x00000040  (  0)  WWDG
    0,                     //0x00000044  (  1)  EXTI16 / PVD
    0,                     //0x00000048  (  2)  EXTI21 / TAMP_STAMP
    0,                     //0x0000004C  (  3)  EXTI22 / RTC_WKUP
    0,                     //0x00000050  (  4)  Flash
    0,                     //0x00000054  (  5)  RCC
    0,                     //0x00000058  (  6)  EXTI0
    0,                     //0x0000005C  (  7)  EXTI1
    0,                     //0x00000060  (  8)  EXTI2
    0,                     //0x00000064  (  9)  EXTI3
    0,                     //0x00000068  ( 10)  EXTI4
    0,                     //0x0000006C  ( 11)  DMA1_Stream0
    0,                     //0x00000070  ( 12)  DMA1_Stream1
    0,                     //0x00000074  ( 13)  DMA1_Stream2
    0,                     //0x00000078  ( 14)  DMA1_Stream3
    0,                     //0x0000007C  ( 15)  DMA1_Stream4
    0,                     //0x00000080  ( 16)  DMA1_Stream5
    0,                     //0x00000084  ( 17)  DMA1_Stream6
    0,                     //0x00000088  ( 18)  ADC1
    0,                     //0x0000008C  ( 19)  Reserved
    0,                     //0x00000090  ( 20)  Reserved
    0,                     //0x00000094  ( 21)  Reserved
    0,                     //0x00000098  ( 22)  Reserved
    0,                     //0x0000009C  ( 23)  EXTI9_5
    0,                     //0x000000A0  ( 24)  TIM1_BRK / TIM9
    0,                     //0x000000A4  ( 25)  TIM1_UP / TIM10
    0,                     //0x000000A8  ( 26)  TIM1_TRG_COM / TIM11
    0,                     //0x000000AC  ( 27)  TIM1_CC
    0,                     //0x000000B0  ( 28)  TIM2
    0,                     //0x000000B4  ( 29)  TIM3
    0,                     //0x000000B8  ( 30)  TIM4
    0,                     //0x000000BC  ( 31)  I2C1_EV
    0,                     //0x000000C0  ( 32)  I2C1_ER
    0,                     //0x000000C4  ( 33)  I2C2_EV
    0,                     //0x000000C8  ( 34)  I2C2_ER
    0,                     //0x000000CC  ( 35)  SPI1
    spi2IrqHandler,        //0x000000D0  ( 36)  SPI2
    0,                     //0x000000D4  ( 37)  USART1
    0,                     //0x000000D8  ( 38)  USART2
    0,                     //0x000000DC  ( 39)  Reserved
    0,                     //0x000000E0  ( 40)  EXTI15_10
    0,                     //0x000000E4  ( 41)  EXTI17 / RTC_Alarm
    0,                     //0x000000E8  ( 42)  EXTI18 / OTG_FS_Wakeup
    0,                     //0x000000EC  ( 43)  Reserved
    0,                     //0x000000F0  ( 44)  Reserved
    0,                     //0x000000F4  ( 45)  Reserved
    0,                     //0x000000F8  ( 46)  Reserved
    0,                     //0x000000FC  ( 47)  DMA1_Stream7
    0,                     //0x00000100  ( 48)  Reserved
    0,                     //0x00000104  ( 49)  SDIO
    0,                     //0x00000108  ( 50)  TIM5
    0,                     //0x0000010C  ( 51)  SPI3
    0,                     //0x00000110  ( 52)  Reserved
    0,                     //0x00000114  ( 53)  Reserved
    0,                     //0x00000118  ( 54)  Reserved
    0,                     //0x0000011C  ( 55)  Reserved
    0,                     //0x00000120  ( 56)  DMA2_Stream0
    0,                     //0x00000124  ( 57)  DMA2_Stream1
    0,                     //0x00000128  ( 58)  DMA2_Stream2
    0,                     //0x0000012C  ( 59)  DMA2_Stream3
    0,                     //0x00000130  ( 60)  DMA2_Stream4
    0,                     //0x00000134  ( 61)  Reserved
    0,                     //0x00000138  ( 62)  Reserved
    0,                     //0x0000013C  ( 63)  Reserved
    0,                     //0x00000140  ( 64)  Reserved
    0,                     //0x00000144  ( 65)  Reserved
    0,                     //0x00000148  ( 66)  Reserved
    0,                     //0x0000014C  ( 67)  OTG_FS
    0,                     //0x00000150  ( 68)  DMA2_Stream5
    0,                     //0x00000154  ( 69)  DMA2_Stream6
    0,                     //0x00000158  ( 70)  DMA2_Stream7
    0,                     //0x0000015C  ( 71)  USART6
    0,                     //0x00000160  ( 72)  I2C3_EV
    0,                     //0x00000164  ( 73)  I2C3_ER
    0,                     //0x00000168  ( 74)  Reserved
    0,                     //0x0000016C  ( 75)  Reserved
    0,                     //0x00000170  ( 76)  Reserved
    0,                     //0x00000174  ( 77)  Reserved
    0,                     //0x00000178  ( 78)  Reserved
    0,                     //0x0000017C  ( 79)  Reserved
    0,                     //0x00000180  ( 80)  Reserved
    0,                     //0x00000184  ( 81)  FPU
    0,                     //0x00000188  ( 82)  Reserved
    0,                     //0x0000018C  ( 83)  Reserved
    0,                     //0x00000190  ( 84)  SPI4
    0,                     //0x00000194  ( 85)  SPI5
};

//----------------------------------------------------------------------------------------------------------------------------------

//On reset this handler is called to setup the initial memory state
void resetHandler(void)
{
  unsigned char volatile *src;
  unsigned char volatile *dst;
  unsigned len;

  //Setup pointers and counter for copying initial values from flash to normal memory
  //This concerns all variables that are declared globally with an initial value
  src= &INIT_DATA_VALUES;
  dst= &INIT_DATA_START;
  len= &INIT_DATA_END - &INIT_DATA_START;

  while(len--)
    *dst++ = *src++;

  //Setup pointer and counter for erasing all the other variables
  dst = &BSS_START;
  len = &BSS_END - &BSS_START;

  while(len--)
    *dst++=0;

  //Go and start the main process
  main();
}

//----------------------------------------------------------------------------------------------------------------------------------
