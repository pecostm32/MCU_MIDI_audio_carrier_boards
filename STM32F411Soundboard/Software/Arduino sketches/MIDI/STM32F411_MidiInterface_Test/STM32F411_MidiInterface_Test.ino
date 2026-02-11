#include <HardwareSerial.h>


#define MIDI_RX  PB7
#define MIDI_TX  PB6

HardwareSerial mySerial1(MIDI_RX, MIDI_TX);


void setup()
{
  Serial.begin(115200);
  while (!Serial && millis() < 10000UL);

  mySerial1.begin(31250);

  Serial.println("Test van UART data in naar uit");
  Serial.print("RX pin: ");
  Serial.println(MIDI_RX);
  Serial.print("TX pin: ");
  Serial.println(MIDI_TX);
}

void loop()
{
  if(mySerial1.available())
  {
    Serial.write(mySerial1.read());
  }

  if(Serial.available())
  {
    mySerial1.write(Serial.read());
  }
}
