

#define MIDI_RX  5
#define MIDI_TX  4

void setup()
{
  Serial.begin(115200);
  while (!Serial && millis() < 10000UL);

  Serial1.setTX(0);
  Serial1.setRX(1);
  Serial1.begin(31250);

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
