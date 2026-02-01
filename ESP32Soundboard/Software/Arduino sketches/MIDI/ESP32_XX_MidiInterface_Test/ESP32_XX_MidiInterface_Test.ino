#include "soc/efuse_reg.h"
#include "esp_efuse.h" // for programming eFuse.



#define BOARD_C3         1
#define BOARD_C6         2
#define BOARD_H2         3
#define BOARD_S2         4    //Does not work via this setup and needs USB MIDI to test
#define BOARD_S3         5    //Works for the S3 WROOM N16R8 board via USB serial port but not with the S3 super mini board.
#define BOARD_ESP32_30   6
#define BOARD_ESP32_38   7

#define BOARD_IN_USE   BOARD_C6

#if BOARD_IN_USE == BOARD_C3
#define MIDI_RX  1
#define MIDI_TX  0
#elif BOARD_IN_USE == BOARD_C6
#define MIDI_RX  15
#define MIDI_TX  14
#elif BOARD_IN_USE == BOARD_H2
#define MIDI_RX  11
#define MIDI_TX  10
#elif BOARD_IN_USE == BOARD_S2
#define MIDI_RX  7
#define MIDI_TX  5
#elif BOARD_IN_USE == BOARD_S3
#define MIDI_RX  10
#define MIDI_TX   9
#elif BOARD_IN_USE == BOARD_ESP32_30
#define MIDI_RX  12
#define MIDI_TX  14
#elif BOARD_IN_USE == BOARD_ESP32_38
#define MIDI_RX  12
#define MIDI_TX  14
#endif

void setup()
{
  Serial.begin(115200);

  Serial1.begin(31250, SERIAL_8N1, MIDI_RX, MIDI_TX);

  Serial.println("Test van UART data in naar uit");
  Serial.print("RX pin: ");
  Serial.println(MIDI_RX);
  Serial.print("TX pin: ");
  Serial.println(MIDI_TX);
}

void loop()
{
  if(Serial1.available())
  {
    Serial.write(Serial1.read());
  }

  if(Serial.available())
  {
    Serial1.write(Serial.read());
  }
}
