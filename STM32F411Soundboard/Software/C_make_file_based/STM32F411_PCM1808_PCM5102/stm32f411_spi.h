//----------------------------------------------------------------------------------------------------------------------------------

#ifndef __STM32F411_SPI_H_
#define __STM32F411_SPI_H_

//----------------------------------------------------------------------------------------------------------------------------------

#include "stm32_types.h"

//----------------------------------------------------------------------------------------------------------------------------------
//Structure definition(s)
//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  __IO uint32 CR1;        //SPI control register 1 (not used in I2S mode)
  __IO uint32 CR2;        //SPI control register 2
  __IO uint32 SR;         //SPI status register
  __IO uint32 DR;         //SPI data register
  __IO uint32 CRCPR;      //SPI CRC polynomial register (not used in I2S mode)
  __IO uint32 RXCRCR;     //SPI RX CRC register (not used in I2S mode)
  __IO uint32 TXCRCR;     //SPI TX CRC register (not used in I2S mode)
  __IO uint32 I2SCFGR;    //SPI_I2S configuration register
  __IO uint32 I2SPR;      //SPI_I2S prescaler register
} SPI_TypeDef;

//----------------------------------------------------------------------------------------------------------------------------------
//Base address definition(s)
//----------------------------------------------------------------------------------------------------------------------------------

#define SPI1                        ((SPI_TypeDef *) 0x40013000)
#define SPI2                        ((SPI_TypeDef *) 0x40003800)
#define SPI3                        ((SPI_TypeDef *) 0x40003C00)
#define SPI4                        ((SPI_TypeDef *) 0x40013400)
#define SPI5                        ((SPI_TypeDef *) 0x40015000)

#define I2S2                        ((SPI_TypeDef *) 0x40003800)
#define I2S2ext                     ((SPI_TypeDef *) 0x40003400)
#define I2S3                        ((SPI_TypeDef *) 0x40003C00)
#define I2S3ext                     ((SPI_TypeDef *) 0x40004000)

//----------------------------------------------------------------------------------------------------------------------------------
//Interrupt number definition(s)
//----------------------------------------------------------------------------------------------------------------------------------

#define SPI1_IRQn                   35                //SPI1 global Interrupt
#define SPI2_IRQn                   36                //SPI2 global Interrupt
#define SPI3_IRQn                   51                //SPI3 global Interrupt
#define SPI4_IRQn                   84                //SPI4 global Interrupt
#define SPI5_IRQn                   85                //SPI5 global Interrupt

//----------------------------------------------------------------------------------------------------------------------------------
//SPI bit definitions
//----------------------------------------------------------------------------------------------------------------------------------

#define SPI_CR2_RXNEIE               0x00000040                           //RX buffer Not Empty Interrupt Enable
#define SPI_CR2_TXEIE                0x00000080                           //Tx buffer Empty Interrupt Enable

#define SPI_I2SCFGR_CHLEN            0x00000001                           //Channel length (number of bits per audio channel) 0: 16 bit, 1: 32 bit.

#define SPI_I2SCFGR_16_BIT_DATA      0x00000000                           //16 bits per audio sample
#define SPI_I2SCFGR_24_BIT_DATA      0x00000002                           //24 bits per audio sample
#define SPI_I2SCFGR_32_BIT_DATA      0x00000004                           //32 bits per audio sample

#define SPI_I2SCFGR_CKPOL            0x00000008                           //Steady state clock polarity. 0: low, 1: high.

#define SPI_I2SCFGR_MASTER_TRANSMIT  0x00000200                           //Master transmit mode
#define SPI_I2SCFGR_MASTER_RECEIVE   0x00000300                           //Master receive mode

#define SPI_I2SCFGR_I2SE             0x00000400                           //I2S Enable
#define SPI_I2SCFGR_I2SMOD           0x00000800                           //I2S mode selection

#define SPI_I2SPR_MCKOE              0x00000200                           //Master Clock Output Enable

//----------------------------------------------------------------------------------------------------------------------------------
//Bit definition(s) for SPI_CR1 register
//----------------------------------------------------------------------------------------------------------------------------------

#define SPI_CR1_CPHA                0x00000001        //Clock Phase
#define SPI_CR1_CPOL                0x00000002        //Clock Polarity
#define SPI_CR1_MSTR                0x00000004        //Master Selection
#define SPI_CR1_BR                  0x00000038        //BR[2:0] bits (Baud Rate Control)
#define SPI_CR1_BR_0                0x00000008
#define SPI_CR1_BR_1                0x00000010
#define SPI_CR1_BR_2                0x00000020
#define SPI_CR1_SPE                 0x00000040        //SPI Enable
#define SPI_CR1_LSBFIRST            0x00000080        //Frame Format
#define SPI_CR1_SSI                 0x00000100        //Internal slave select
#define SPI_CR1_SSM                 0x00000200        //Software slave management
#define SPI_CR1_RXONLY              0x00000400        //Receive only
#define SPI_CR1_DFF                 0x00000800        //Data Frame Format
#define SPI_CR1_CRCNEXT             0x00001000        //Transmit CRC next
#define SPI_CR1_CRCEN               0x00002000        //Hardware CRC calculation enable
#define SPI_CR1_BIDIOE              0x00004000        //Output enable in bidirectional mode
#define SPI_CR1_BIDIMODE            0x00008000        //Bidirectional data mode enable

//----------------------------------------------------------------------------------------------------------------------------------
//Bit definition(s) for SPI_CR2 register
//----------------------------------------------------------------------------------------------------------------------------------

#define SPI_CR2_RXDMAEN             0x00000001        //Rx Buffer DMA Enable
#define SPI_CR2_TXDMAEN             0x00000002        //Tx Buffer DMA Enable
#define SPI_CR2_SSOE                0x00000004        //SS Output Enable
#define SPI_CR2_FRF                 0x00000010        //Frame Format
#define SPI_CR2_ERRIE               0x00000020        //Error Interrupt Enable
#define SPI_CR2_RXNEIE              0x00000040        //RX buffer Not Empty Interrupt Enable
#define SPI_CR2_TXEIE               0x00000080        //Tx buffer Empty Interrupt Enable

//----------------------------------------------------------------------------------------------------------------------------------
//Bit definition(s) for SPI_SR register
//----------------------------------------------------------------------------------------------------------------------------------

#define SPI_SR_RXNE                 0x00000001        //Receive buffer Not Empty
#define SPI_SR_TXE                  0x00000002        //Transmit buffer Empty
#define SPI_SR_CHSIDE               0x00000004        //Channel side
#define SPI_SR_UDR                  0x00000008        //Underrun flag
#define SPI_SR_CRCERR               0x00000010        //CRC Error flag
#define SPI_SR_MODF                 0x00000020        //Mode fault
#define SPI_SR_OVR                  0x00000040        //Overrun flag
#define SPI_SR_BSY                  0x00000080        //Busy flag
#define SPI_SR_FRE                  0x00000100        //Frame format error flag

//----------------------------------------------------------------------------------------------------------------------------------
//Bit definition(s) for SPI_DR register
//----------------------------------------------------------------------------------------------------------------------------------

#define SPI_DR_DR                   0x0000FFFF        //Data Register

//----------------------------------------------------------------------------------------------------------------------------------
//Bit definition(s) for SPI_CRCPR register
//----------------------------------------------------------------------------------------------------------------------------------

#define SPI_CRCPR_CRCPOLY           0x0000FFFF        //CRC polynomial register

//----------------------------------------------------------------------------------------------------------------------------------
//Bit definition(s) for SPI_RXCRCR register
//----------------------------------------------------------------------------------------------------------------------------------

#define SPI_RXCRCR_RXCRC            0x0000FFFF        //Rx CRC Register

//----------------------------------------------------------------------------------------------------------------------------------
//Bit definition(s) for SPI_TXCRCR register
//----------------------------------------------------------------------------------------------------------------------------------

#define SPI_TXCRCR_TXCRC            0x0000FFFF        //Tx CRC Register

//----------------------------------------------------------------------------------------------------------------------------------
//Bit definition(s) for SPI_I2SCFGR register
//----------------------------------------------------------------------------------------------------------------------------------

#define SPI_I2SCFGR_CHLEN           0x00000001        //Channel length (number of bits per audio channel)
#define SPI_I2SCFGR_DATLEN          0x00000006        //DATLEN[1:0] bits (Data length to be transferred)
#define SPI_I2SCFGR_DATLEN_0        0x00000002
#define SPI_I2SCFGR_DATLEN_1        0x00000004
#define SPI_I2SCFGR_CKPOL           0x00000008        //steady state clock polarity
#define SPI_I2SCFGR_I2SSTD          0x00000030        //I2SSTD[1:0] bits (I2S standard selection)
#define SPI_I2SCFGR_I2SSTD_0        0x00000010
#define SPI_I2SCFGR_I2SSTD_1        0x00000020
#define SPI_I2SCFGR_PCMSYNC         0x00000080        //PCM frame synchronization
#define SPI_I2SCFGR_I2SCFG          0x00000300        //I2SCFG[1:0] bits (I2S configuration mode)
#define SPI_I2SCFGR_I2SCFG_0        0x00000100
#define SPI_I2SCFGR_I2SCFG_1        0x00000200
#define SPI_I2SCFGR_I2SE            0x00000400        //I2S Enable
#define SPI_I2SCFGR_I2SMOD          0x00000800        //I2S mode selection

//----------------------------------------------------------------------------------------------------------------------------------
//Bit definition(s) for SPI_I2SPR register
//----------------------------------------------------------------------------------------------------------------------------------

#define SPI_I2SPR_I2SDIV            0x000000FF        //I2S Linear prescaler
#define SPI_I2SPR_ODD               0x00000100        //Odd factor for the prescaler
#define SPI_I2SPR_MCKOE             0x00000200        //Master Clock Output Enable

//----------------------------------------------------------------------------------------------------------------------------------

#endif //__STM32F411_SPI_H_

//----------------------------------------------------------------------------------------------------------------------------------
