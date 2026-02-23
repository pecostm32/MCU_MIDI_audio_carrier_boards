#include <I2S.h>

// I2S pins for ADC and DAC
#define I2S_MCLK    20    // 11
#define I2S_BCLK    18    // 12
#define I2S_WS      19    // 13 this will always be 1 pin above BCLK - can't change it
#define I2S_DATA    16    // 14 Out of Pico to DAC
#define I2S_DATAIN  17    // 15 into Pico from ADC



I2S i2s(INPUT_PULLUP); // both input and output

void setup()
{ 
  Serial.begin(115200);
  while (!Serial && millis() < 10000UL);
  
  Serial.println("starting setup");  

// set up I2S for 32 bits in and out
// PCM1808 is 24 bit only but I could not get 24 bit I2S working. 32 bits is little if any extra overhead
  i2s.setDOUT(I2S_DATA);
  i2s.setDIN(I2S_DATAIN);
  i2s.setBCLK(I2S_BCLK); // Note: LRCLK = BCLK + 1
  i2s.setMCLK(I2S_MCLK);
  i2s.setMCLKmult(256);
  i2s.setBitsPerSample(32);
  i2s.setFrequency(96000);
  i2s.begin();

  Serial.println("finished setup");  
}


void loop()
{
// process audio samples
  int32_t left,right;

  //these calls will stall if no data is available
  left  = i2s.read();
  right = i2s.read();

  //these calls will stall if buffer is full
	i2s.write(left);
	i2s.write(right);
}
