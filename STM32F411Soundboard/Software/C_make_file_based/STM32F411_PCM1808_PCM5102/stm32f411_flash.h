//----------------------------------------------------------------------------------------------------------------------------------

#ifndef __STM32F411_FLASH_H_
#define __STM32F411_FLASH_H_

//----------------------------------------------------------------------------------------------------------------------------------

#include "stm32_types.h"

//----------------------------------------------------------------------------------------------------------------------------------
//Structure definition(s)
//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  __IO uint32 ACR;      //FLASH access control register
  __IO uint32 KEYR;     //FLASH key register
  __IO uint32 OPTKEYR;  //FLASH option key register
  __IO uint32 SR;       //FLASH status register
  __IO uint32 CR;       //FLASH control register
  __IO uint32 OPTCR;    //FLASH option control register 
  __IO uint32 OPTCR1;   //FLASH option control register 1
} FLASH_TypeDef;

//----------------------------------------------------------------------------------------------------------------------------------
//Base address definition(s)
//----------------------------------------------------------------------------------------------------------------------------------

#define FLASH                          ((FLASH_TypeDef *) 0x40023C00)

//----------------------------------------------------------------------------------------------------------------------------------
//Interrupt number definition(s)
//----------------------------------------------------------------------------------------------------------------------------------

#define FLASH_IRQn                     4                 //FLASH global Interrupt

//----------------------------------------------------------------------------------------------------------------------------------
//Bit definition(s) for FLASH_ACR register
//----------------------------------------------------------------------------------------------------------------------------------

#define FLASH_ACR_LATENCY              0x0000000F
#define FLASH_ACR_LATENCY_0WS          0x00000000
#define FLASH_ACR_LATENCY_1WS          0x00000001
#define FLASH_ACR_LATENCY_2WS          0x00000002
#define FLASH_ACR_LATENCY_3WS          0x00000003
#define FLASH_ACR_LATENCY_4WS          0x00000004
#define FLASH_ACR_LATENCY_5WS          0x00000005
#define FLASH_ACR_LATENCY_6WS          0x00000006
#define FLASH_ACR_LATENCY_7WS          0x00000007
#define FLASH_ACR_PRFTEN               0x00000100
#define FLASH_ACR_ICEN                 0x00000200
#define FLASH_ACR_DCEN                 0x00000400
#define FLASH_ACR_ICRST                0x00000800
#define FLASH_ACR_DCRST                0x00001000
#define FLASH_ACR_BYTE0_ADDRESS        0x40023C00
#define FLASH_ACR_BYTE2_ADDRESS        0x40023C03

//----------------------------------------------------------------------------------------------------------------------------------
//Bit definition(s) for FLASH_SR register
//----------------------------------------------------------------------------------------------------------------------------------

#define FLASH_SR_EOP                   0x00000001
#define FLASH_SR_SOP                   0x00000002
#define FLASH_SR_WRPERR                0x00000010
#define FLASH_SR_PGAERR                0x00000020
#define FLASH_SR_PGPERR                0x00000040
#define FLASH_SR_PGSERR                0x00000080
#define FLASH_SR_RDERR                 0x00000100
#define FLASH_SR_BSY                   0x00010000

//----------------------------------------------------------------------------------------------------------------------------------
//Bit definition(s) for FLASH_CR register
//----------------------------------------------------------------------------------------------------------------------------------

#define FLASH_CR_PG                    0x00000001
#define FLASH_CR_SER                   0x00000002
#define FLASH_CR_MER                   0x00000004
#define FLASH_CR_SNB                   0x000000F8
#define FLASH_CR_SNB_0                 0x00000008
#define FLASH_CR_SNB_1                 0x00000010
#define FLASH_CR_SNB_2                 0x00000020
#define FLASH_CR_SNB_3                 0x00000040
#define FLASH_CR_SNB_4                 0x00000080
#define FLASH_CR_PSIZE                 0x00000300
#define FLASH_CR_PSIZE_0               0x00000100
#define FLASH_CR_PSIZE_1               0x00000200
#define FLASH_CR_STRT                  0x00010000
#define FLASH_CR_EOPIE                 0x01000000
#define FLASH_CR_LOCK                  0x80000000

//----------------------------------------------------------------------------------------------------------------------------------
//Bit definition(s) for FLASH_OPTCR register
//----------------------------------------------------------------------------------------------------------------------------------

#define FLASH_OPTCR_OPTLOCK            0x00000001
#define FLASH_OPTCR_OPTSTRT            0x00000002
#define FLASH_OPTCR_BOR_LEV_0          0x00000004
#define FLASH_OPTCR_BOR_LEV_1          0x00000008
#define FLASH_OPTCR_BOR_LEV            0x0000000C
#define FLASH_OPTCR_WDG_SW             0x00000020
#define FLASH_OPTCR_nRST_STOP          0x00000040
#define FLASH_OPTCR_nRST_STDBY         0x00000080
#define FLASH_OPTCR_RDP                0x0000FF00
#define FLASH_OPTCR_RDP_0              0x00000100
#define FLASH_OPTCR_RDP_1              0x00000200
#define FLASH_OPTCR_RDP_2              0x00000400
#define FLASH_OPTCR_RDP_3              0x00000800
#define FLASH_OPTCR_RDP_4              0x00001000
#define FLASH_OPTCR_RDP_5              0x00002000
#define FLASH_OPTCR_RDP_6              0x00004000
#define FLASH_OPTCR_RDP_7              0x00008000
#define FLASH_OPTCR_nWRP               0x0FFF0000
#define FLASH_OPTCR_nWRP_0             0x00010000
#define FLASH_OPTCR_nWRP_1             0x00020000
#define FLASH_OPTCR_nWRP_2             0x00040000
#define FLASH_OPTCR_nWRP_3             0x00080000
#define FLASH_OPTCR_nWRP_4             0x00100000
#define FLASH_OPTCR_nWRP_5             0x00200000
#define FLASH_OPTCR_nWRP_6             0x00400000
#define FLASH_OPTCR_nWRP_7             0x00800000
#define FLASH_OPTCR_nWRP_8             0x01000000
#define FLASH_OPTCR_nWRP_9             0x02000000
#define FLASH_OPTCR_nWRP_10            0x04000000
#define FLASH_OPTCR_nWRP_11            0x08000000

//----------------------------------------------------------------------------------------------------------------------------------
//Bit definition(s) for FLASH_OPTCR1 register
//----------------------------------------------------------------------------------------------------------------------------------

#define FLASH_OPTCR1_nWRP              0x0FFF0000
#define FLASH_OPTCR1_nWRP_0            0x00010000
#define FLASH_OPTCR1_nWRP_1            0x00020000
#define FLASH_OPTCR1_nWRP_2            0x00040000
#define FLASH_OPTCR1_nWRP_3            0x00080000
#define FLASH_OPTCR1_nWRP_4            0x00100000
#define FLASH_OPTCR1_nWRP_5            0x00200000
#define FLASH_OPTCR1_nWRP_6            0x00400000
#define FLASH_OPTCR1_nWRP_7            0x00800000
#define FLASH_OPTCR1_nWRP_8            0x01000000
#define FLASH_OPTCR1_nWRP_9            0x02000000
#define FLASH_OPTCR1_nWRP_10           0x04000000
#define FLASH_OPTCR1_nWRP_11           0x08000000

//----------------------------------------------------------------------------------------------------------------------------------

#endif //__STM32F411_FLASH_H_

//----------------------------------------------------------------------------------------------------------------------------------
