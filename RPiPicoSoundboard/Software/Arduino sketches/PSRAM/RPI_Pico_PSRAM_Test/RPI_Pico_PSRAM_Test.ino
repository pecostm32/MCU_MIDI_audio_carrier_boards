//Board: Raspberry Pi Pico or Raspberry Pi Pico 2

#include <SPI.h>

#define PSRAM_CS     5
#define PSRAM_SCK    2
#define PSRAM_MOSI   3
#define PSRAM_MISO   4

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial && millis() < 10000UL);

  Serial.println("Test van PSRAM");

  //Make sure the output is high when switching from default input to output.
  digitalWrite(PSRAM_CS, LOW);
  pinMode(PSRAM_CS, OUTPUT);

  //Configure the SPI pins to be used
  SPI.setSCK(PSRAM_SCK);
  SPI.setMISO(PSRAM_MISO);
  SPI.setMOSI(PSRAM_MOSI);

  //Initialize SPI interface
  SPI.begin();

  //Try to read the ID of the PSRAM chip
  if(psram_read_id() == 0)
  {
    //Working chip then perform a read write test
    //Test 8MB chip (8 * 1024 * 1024)
    psram_write_read_test(8388608);
  }

  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
}

#define JEDEC_ID_LEN 12

#define PSRAM_READ_CMD     0x03
#define PSRAM_WRITE_CMD    0x02
#define PSRAM_ID_CMD       0x9F

int psram_read_id(void)
{
  uint8_t buffer[JEDEC_ID_LEN], *ptr, cap;

  Serial.println("PSRAM read id");

  ptr = buffer;

  *ptr++ = PSRAM_ID_CMD;

  for(int i = 0; i < JEDEC_ID_LEN - 1; ++i)
  {
    *ptr++ = 0x00;
  }

  psram_spi_stream(buffer, JEDEC_ID_LEN);

  Serial.println("Return from stream");

  if(buffer[4] == 0x0D)
  {
    Serial.printf("Manufacturer ID:   0x%02X\n", buffer[4]);
    Serial.printf("Memory Test Check: 0x%02X\n", buffer[5]);
    Serial.printf("Extended ID: 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X\n", buffer[6], buffer[7], buffer[8], buffer[9], buffer[10], buffer[11]);

    if(buffer[5] == 0x5D)
    {
      Serial.println("Good chip");
    }
    else
    {
      Serial.println("Bad chip");
    }
  }
  else
  {
    Serial.println("Chip not found, check connection.");
    return -1;
  }
  
  return(0);
}

#define PSRAM_BLOCK_SIZE    1024
#define PSRAM_BUFFER_SIZE   PSRAM_BLOCK_SIZE + 4

void psram_write_read_test(uint32_t size)
{
  uint8_t  buffer[PSRAM_BUFFER_SIZE];
  uint16_t pattern = 0x33;
  uint32_t address = 0;
  int      n;
  int      ledstate = LOW;
  int      fault = 0;

  Serial.println("Starting write read test.");

  while(pattern < 0x100)
  {
    Serial.printf("Pattern: 0x%02X\n", (uint8_t)pattern);

    address = 0;

    while(address < size)
    {
      digitalWrite(LED_BUILTIN, ledstate);
      ledstate ^= HIGH;

      //Setup for writing the pattern
      memset(&buffer[4], pattern, PSRAM_BLOCK_SIZE);

      buffer[0] = PSRAM_WRITE_CMD;
      buffer[1] = address >> 16;
      buffer[2] = address >>  8;
      buffer[3] = address;

      psram_spi_stream(buffer, PSRAM_BLOCK_SIZE);

      //Setup for reading the data back
      buffer[0] = PSRAM_READ_CMD;
      buffer[1] = address >> 16;
      buffer[2] = address >>  8;
      buffer[3] = address;

      psram_spi_stream(buffer, PSRAM_BLOCK_SIZE);

      //Check if the data is valid
      for(n=4;n<PSRAM_BLOCK_SIZE;n++)
      {
        if(buffer[n] != (uint8_t)pattern)
        {
          Serial.printf("Memory compare failed. Address: 0x%08X  Data: 0x%02X\n", (address + (n - 4)), buffer[n]);
          fault = 1;
          break;
        }
      }

      //Select next memory block to check
      address += PSRAM_BLOCK_SIZE;
    }

      //Select the next pattern
      pattern += 0x33;
  }

  if(fault)
  {
    Serial.println("Memory has errors");
  }
  else
  {
    Serial.println("Memory is good");
  }
}


void psram_spi_stream(uint8_t *buf, uint32_t len)
{
  //Serial.println("Start communication");

  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));

  digitalWrite(PSRAM_CS, LOW);

  SPI.transfer(buf, len);

  digitalWrite(PSRAM_CS, HIGH);

  SPI.endTransaction();

  //Serial.println("End communication");
}
