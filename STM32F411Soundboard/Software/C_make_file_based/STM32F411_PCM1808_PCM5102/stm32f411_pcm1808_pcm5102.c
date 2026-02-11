//----------------------------------------------------------------------------------------------------------------------------------
//Run openocd for debugging
//openocd -f STM32F411CEU6.cfg
//Start debugging by connecting to dbg on available port
//gdbserver is needed for this. Install with apt-get

//----------------------------------------------------------------------------------------------------------------------------------

#include "stm32f411_main.h"

//----------------------------------------------------------------------------------------------------------------------------------

//STM3F411 has:
//  a different clock configuration and other AHB and ABP bus setup
//  enabling of peripherals is done in the same way, but differ in what is connected to which bus
//  a different GPIO setup
//  a different way of moving alternate functions for the pins. AFIO is SYSCFG and is used to remap functions not pins
//  the ADC's are different in configuration and usage
//  the xE device has 128KB of standard RAM


//Simple embedded systems can do without a separate heap.
//This means not using standard libraries
//Memory is statically declared and used.
//To allow for a proper working leave memory for the stack to grow so do not use more then RAM size - 1024 bytes

//Programming the STM32 in C starting from the reset vector needs the following steps in given order
// 1) Setup the interrupt and exception vector table
// 2) Configure C variables (resetHandler)
// 3) Configure the clock system and enable the needed peripheral clocks
// 4) Configure the input / output pins
// 5) Configure the peripherals
// 6) Enable the interrupts
// 7) Loop through the main code

//----------------------------------------------------------------------------------------------------------------------------------

//Main program part
int main(void)
{
  //Setup flash to work with 100MHz clock
  //Enable the Prefetch Buffer and Set to 2 wait states
  FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_2WS;

  //Setup the main PLL for the highest usable core clock and 48MHz for USB
  //Default setting with 16MHz HSI clock is 96MHz SYSCLK and 48MHz USB and SDIO
  //For the HSE an external crystal of 25MHz is used
  //N = 200, M = 13, P = 4, Q = 8
  //Top 4 bits have to be set to reset value.
//  RCC->PLLCFGR = 0x20000000 | (8 << 24) | (1 << 16) | (200 << 6) | 13;
  
  //Need 80MHz for the core to have the SPI run on 20MHz
  //N = 256, M = 20, P = 4, Q = 7
  //There is a good change USB won't work on this setting (Check the separate channel for USB clock)
  RCC->PLLCFGR = 0x20000000 | (7 << 24) | (1 << 16) | (256 << 6) | 20;
  
  //Configure system clock
  //SYSCLK: 80MHz
  //AHB:  SYSCLK/1 = 80MHz
  //APB1: AHB/2    = 40MHz
  //APB2: AHB/1    = 80MHz
  //RTC: No clock
  RCC->CFGR = RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_HPRE_DIV1;

  //Enable external oscillator
  RCC->CR |= RCC_CR_HSEON;

  //Wait for the clock to become stable
  while((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY);
  
  //Set HSE as source for the main PLL
  RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;
  
  //Enable the PLL
  RCC->CR |= RCC_CR_PLLON;

  //Wait for the PLL to become stable
  while((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY);

  //Switch to the PLL clock as system clock source. Since on reset these bits are set to 0 no need to clear first.
  RCC->CFGR |= RCC_CFGR_SW_PLL;

  //Wait for the PLL to become the clock source
  while((RCC->CFGR & RCC_CFGR_SWS_PLL) != RCC_CFGR_SWS_PLL);
  
  //Disable the internal high speed oscillator to reduce power consumption
  RCC->CR &= ~RCC_CR_HSION;

  //////////////////////////////////
  //From this point on it is not possible to change the clock configuration without switching back to HSI
  //////////////////////////////////

  //Enable the used peripherals. PORTA, PORTB, PORTC and DMA2
  RCC->AHB1ENR |=  RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN  | RCC_AHB1ENR_DMA2EN;
  
  //Enable TIM1, SPI1
  //RCC->APB2ENR |= RCC_APB2ENR_TIM1EN | RCC_APB2ENR_SPI1EN;
  
  //Enable SPI2 and SPI3 for I2S
  RCC->APB1ENR |= RCC_APB1ENR_SPI2EN | RCC_APB1ENR_SPI3EN;
  
  //Enable the system timer for delay function
  //In default setting with 72MHz AHB clock this timer runs on 9MHz, so 111ns per tick. Takes 9 ticks for a microsecond
//  STK->LOAD = 0x00FFFFFF;
//  STK->CTRL = STK_CTRL_ENABLE;
  
  //!!!!!!!!!!!!!!!
  //Make sure to disable JTAG and or SWD to make use of some of the peripherals on the pins and use for the mentioned interfaces
  //!!!!!!!!!!!!!!!
  
#if 0
  Wat nodig is voor de ADC en DAC is het configureren van de twee I2S interfaces
  Interrupt moet op de receive I2S ingesteld worden
          
  PB6   MIDI_TX  USART1
  PB7   MIDI_RX  USART1
  
  PA3   I2S2_SCK
  PB13  I2S2_BCK
  PB12  I2S2_LRCK
  PB15  I2S2_SD

  PB10  I2S3_SCK
  PB3   I2S3_BCK
  PA4   I2S3_LRCK
  PB5   I2S3_SD
  
  PA0   PSRAM_CE
  PA1   FLASH_CE
  PA5   SPI1_SCK
  PA6   SPI1_MISO
  PA7   SPI1_MOSI
  
  PB8   GPIO2  I2C1_SCL
  PB9   GPIO1  I2C1_SDA
#endif  

  //IO pins need to be configured first
  //Pin with LED to show activity
  InitIOPin(GPIOC, 13, GPIO_OUTPUT_PP_LOW_SPEED, 0);
  
  //Timer 1 channel 1 output for vertical sync
//  InitIOPin(GPIOA, 8, GPIO_AF_PP_HIGH_SPEED, 1);

  //Timer 2 channel 1 output for horizontal sync
 // InitIOPin(GPIOA, 0, GPIO_AF_PP_HIGH_SPEED, 1);
  
  //Timer 3 channel 1 output for 20MHz clock
//  InitIOPin(GPIOB, 4, GPIO_AF_PP_HIGH_SPEED, 2);
  
  //ADC
  InitIOPin(GPIOA,  3, GPIO_AF_PP_HIGH_SPEED, 5);        //I2S2_SCK
  InitIOPin(GPIOB, 13, GPIO_AF_PP_HIGH_SPEED, 5);        //I2S2_BCK
  InitIOPin(GPIOB, 12, GPIO_AF_PP_HIGH_SPEED, 5);        //I2S2_LRCK
  InitIOPin(GPIOB, 15, GPIO_AF_INPUT,         5);        //I2S2_SD
 
  //DAC
  InitIOPin(GPIOB, 10, GPIO_AF_PP_HIGH_SPEED, 6);        //I2S3_SCK
  InitIOPin(GPIOB,  3, GPIO_AF_PP_HIGH_SPEED, 6);        //I2S3_BCK
  InitIOPin(GPIOA,  4, GPIO_AF_PP_HIGH_SPEED, 6);        //I2S3_LRCK
  InitIOPin(GPIOB,  5, GPIO_AF_PP_HIGH_SPEED, 6);        //I2S3_SD

  //I2S bit rate for stereo 32 bit wide channel length and 96kHz sampling rate is 6144000bps
  //Master clock 256 * 96kHz is 24576000Hz
  //Fs = mclk / (64 * ((2 * div) + odd) * 4)
  //Settings for div = 2 and odd = 0
  //Setup I2S PLL. Target frequency is 98304000Hz. PLL source is 25MHz
  //R >= 2. I2Sclk = PLLclk / R.
  //PLLclk = Fmain * (N / M).
  //50 <= N <= 432   (173)
  //2  <= M <= 63    (22)
  //196608000 / 25000000 = 7.86432
  //25000000 * (173 / 22) ==> ~95992Hz sample rate
  
  //R = 2, N = 173, M = 22
  RCC->PLLI2SCFGR = (2 << 28) | (173 << 6) | 22;
  
  //Enable the PLL
  RCC->CR |= RCC_CR_PLLI2SON;

  //Wait for the PLL to become stable
  while((RCC->CR & RCC_CR_PLLI2SRDY) != RCC_CR_PLLI2SRDY);
  
  //Setup ADC I2S  (I2S2)
  //I2S standard based master receiver, Clock high inactive, 24 bit data length and 32 bit channel length
  I2S2->I2SCFGR = SPI_I2SCFGR_I2SMOD | SPI_I2SCFGR_MASTER_RECEIVE | SPI_I2SCFGR_CKPOL | SPI_I2SCFGR_24_BIT_DATA | SPI_I2SCFGR_CHLEN;
  
  //Master clock on the MCK pin. Main clock divided by 4.
  I2S2->I2SPR = SPI_I2SPR_MCKOE | 2;
  
  //Need to setup interrupt bits in CR2 (Maybe also DMA)
  //Enable the interrupt for receiving
  I2S2->CR2 |= SPI_CR2_RXNEIE;

  //Setup DAC I2S  (I2S3)
  //I2S standard based master transmitter, Clock high inactive, 24 bit data length and 32 bit channel length
  I2S3->I2SCFGR = SPI_I2SCFGR_I2SMOD | SPI_I2SCFGR_MASTER_TRANSMIT | SPI_I2SCFGR_CKPOL | SPI_I2SCFGR_24_BIT_DATA | SPI_I2SCFGR_CHLEN;
  
  //Master clock on the MCK pin Main clock divided by 4.
  I2S3->I2SPR = SPI_I2SPR_MCKOE | 2;
  
  //Priority setting
  set_interrupt_priority(SPI2_IRQn, 0x40);  //(0100b) Group priority 1, sub priority 0
  
  //Interrupt enable
  enable_interrupt(SPI2_IRQn);
  
  
  //Enable the ADC I2S receiving
  I2S2->I2SCFGR |= SPI_I2SCFGR_I2SE;
  
  //Enable the DAC I2S transmitting
  I2S3->I2SCFGR |= SPI_I2SCFGR_I2SE;
  
  
  uint32 delay;
  uint32 count;
  
  while(1)
  {
    
    //Toggle C13 to blink the LED
    GPIOC->ODR ^= (1 << 13);
    
    for(delay=3000000;delay>0;delay--)
    {
      count++;
    }
  }
}


volatile int leftchannel[2]  = { 0, 0 };
volatile int rightchannel[2] = { 0, 0 };

volatile unsigned int rxstate = 0;

volatile int rxindex = 0;
volatile int txindex = 1;

void spi2IrqHandler(void)
{
  //Set pin for time measurement
  GPIOA->ODR |= 0x0002;
  
  //Handle the current state to load the needed part of the data  
  switch(rxstate & 0x03)
  {
    case 0:
      leftchannel[rxindex] = SPI2->DR << 16;
      SPI3->DR = leftchannel[txindex] >> 16;
      break;
      
    case 1:
      leftchannel[rxindex] |= SPI2->DR;
      SPI3->DR = leftchannel[txindex];
      break;
      
    case 2:
      rightchannel[rxindex] = SPI2->DR << 16;
      SPI3->DR = rightchannel[txindex] >> 16;
      break;
      
    case 3:
      rightchannel[rxindex] |= SPI2->DR;
      SPI3->DR = rightchannel[txindex];
      
      rxindex ^= 1;
      txindex ^= 1;
      break;
  }
  
  //Select the next state
  rxstate++;
  
  //Clear pin for time measurement
  GPIOA->ODR &= 0xFFFD;
}
