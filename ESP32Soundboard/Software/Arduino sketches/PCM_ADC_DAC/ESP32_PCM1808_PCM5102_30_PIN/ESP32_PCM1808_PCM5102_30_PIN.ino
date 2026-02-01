/*
 */

#include <ESP_I2S.h>

const uint8_t I2S_MCLK = 1;
const uint8_t I2S_BCLK = 22;
const uint8_t I2S_WS   = 23;
const uint8_t I2S_DIN  = 5;   //(From PCM1808)
const uint8_t I2S_DOUT = 18;  //(To   PCM5102)

//PCM1808 MD0 low, MD1 low, FMT low
//PCM5102 XMT high (3V3), FMT low, FLT low, DMP low
//PCM5102 module only requires 5V. The 3V3 pin is an output

const int sampleRate = 96000;  // sample rate in Hz (44100)

i2s_data_bit_width_t bps  = I2S_DATA_BIT_WIDTH_32BIT;
i2s_mode_t           mode = I2S_MODE_STD;
i2s_slot_mode_t      slot = I2S_SLOT_MODE_STEREO;

I2SClass i2s;

void setup()
{
  Serial.begin(115200);
  Serial.println("I2S ADC in DAC out test");

  i2s.setPins(I2S_BCLK, I2S_WS, I2S_DOUT, I2S_DIN, I2S_MCLK);

  // start I2S at the sample rate with 32-bits per sample
  if (!i2s.begin(mode, sampleRate, bps, slot))
  {
    Serial.println("Failed to initialize I2S!");

    while (1);  // do nothing
  }
}

#define I2S_BUF_SIZE 32

uint8_t i2s_buffer[I2S_BUF_SIZE];

void loop()
{
  size_t i2s_bytes;

  i2s_bytes = i2s.readBytes((char *)i2s_buffer, I2S_BUF_SIZE);

  i2s.write((const uint8_t *)i2s_buffer, i2s_bytes);
}
