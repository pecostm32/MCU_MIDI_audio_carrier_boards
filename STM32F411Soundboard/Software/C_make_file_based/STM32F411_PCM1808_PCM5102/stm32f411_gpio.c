//----------------------------------------------------------------------------------------------------------------------------------
// IO functionality for STM32F411 MCU
//----------------------------------------------------------------------------------------------------------------------------------

#include "stm32f411_gpio.h"

//----------------------------------------------------------------------------------------------------------------------------------

//Simple function for setup of an IO pin
void InitIOPin(GPIO_TypeDef *port, uint32 pin, uint32 setting, uint32 alternatefunction)
{
  //Each pin uses two bits in the mode register for four modes (MODER)
  // 00 input
  // 01 general purpose output
  // 10 alternate function
  // 11 analog
  
  //For an output there are two types (OTYPER)
  // 0 Pull up / down
  // 1 Open drain
  
  //There are three output speed settings (OSPEEDR)
  // x0 Low speed
  // 01 Medium speed
  // 11 High speed
  
  //There are three pull up and pull down possibilities (PUPDR)
  // 00 No pull up or pull down
  // 01 Pull up
  // 10 Pull down

  //Create a base pointer for either the lower or the higher alternate function register
  __IO uint32 *reg;
  
  //2 bit settings need to be shifted twice the distance
  uint32 shifter = pin * 2;

  //Set the requested configuration
  port->MODER |= (setting & GPIO_MODE_MASK) << shifter;
  port->OTYPER |= ((setting & GPIO_TYPE_MASK)  >> 4) << pin;
  port->OSPEEDR |= ((setting & GPIO_SPEED_MASK) >> 8) << shifter;
  port->PUPDR |= ((setting & GPIO_PUPD_MASK) >> 12) << shifter;

  //See if the lower alternate function register or the higher alternate function register needs to be used
  if(pin < 8)
  {
    //Low control register used for first 8 pins
    reg = &port->AFR[0];
  }
  else
  {
    //Force pin into 8 pins per register range
    pin -= 8;

    //High control register used for upper 8 pins
    reg = &port->AFR[1];
  }

  //4 control bits used per pin
  pin *= 4;

  //Reset bits first and set new mode and configuration.
  *reg &= ~(0x0F << pin);
  *reg |=  ((alternatefunction & 0x0F) << pin);
}

//----------------------------------------------------------------------------------------------------------------------------------

uint32 readIOPin(GPIO_TypeDef *port, uint32 pin)
{
  //Convert pin number to a bit mask
  register uint32 mask = (1 << pin);
  
  //Get the masked status of the pin and match it with the mask to return either 0 or 1
  return((port->IDR & mask) == mask);
}

//----------------------------------------------------------------------------------------------------------------------------------

void setIOPin(GPIO_TypeDef *port, uint32 pin)
{
  //Convert pin number to a set bit mask and set the output
  port->ODR |= (1 << pin);
}

//----------------------------------------------------------------------------------------------------------------------------------

void clearIOPin(GPIO_TypeDef *port, uint32 pin)
{
  //Convert pin number to a clear bit mask and clear the output
  port->ODR &= ~(1 << pin);
}

//----------------------------------------------------------------------------------------------------------------------------------

void toggleIOPin(GPIO_TypeDef *port, uint32 pin)
{
  port->ODR ^= (1 << pin);
}

//----------------------------------------------------------------------------------------------------------------------------------
