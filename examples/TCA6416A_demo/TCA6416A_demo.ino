//
//    FILE: TCA6416A_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TCA6416A


#include "TCA6416A.h"


TCA6416A tca(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TCA6416A_LIB_VERSION: ");
  Serial.println(TCA6416A_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(400000);

  if (tca.begin() == false)
  {
    Serial.println("No TCA found.");
    while (1);
  }

  //  Set P0–P3 as inputs, P4–P7 as outputs
  //  0x0F 00001111
  tca.setPinMode8(0x0F);

  //  Invert INPUT polarity so pressing button == 1
  //  0x0F 00001111
  tca.setPolarity8(0x0F);


  //  Initialize outputs to OFF
  //  0x0F 00001111
  tca.digitalWrite8(0x0F);

  Serial.print(millis());
  Serial.println(": config done..");
}


void loop(void)
{
  uint8_t data = tca.digitalRead8();

  tca.digitalWrite8(0xFF);
  delay(500);

  tca.digitalWrite8(0x00);
  delay(500);

  tca.digitalWrite8(data << 4);
  delay(500);

  //  Print input/output states
  Serial.print(" Inputs (P0–P3): ");
  for (uint8_t mask = 0x01; mask < 0x10; mask <<= 1)
  {
    Serial.print(data & mask);
  }
  Serial.println();

  delay(2000);
}


//  -- END OF FILE --
