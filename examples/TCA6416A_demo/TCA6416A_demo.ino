//
//    FILE: TCA6416A_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TCA6416A_RT


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

  //  Set P0–P7 as inputs, P8–P15 as outputs
  tca.setPinMode16(0x00FF);

  //  Invert INPUT polarity so pressing button == 1
  tca.setPolarity16(0x00FF);


  //  Initialize outputs to OFF
  tca.digitalWrite16(0x00FF);

  Serial.print(millis());
  Serial.println(": config done..");
}


void loop(void)
{
  tca.digitalWrite8(0x0080);
  delay(500);
  tca.digitalWrite8(0x0000);
  delay(500);

  tca.digitalWrite8(0x0040);
  delay(500);
  tca.digitalWrite8(0x0000);
  delay(500);

  tca.digitalWrite8(0x0020);
  delay(500);
  tca.digitalWrite8(0x0000);
  delay(500);

  tca.digitalWrite8(0x0010);
  delay(500);
  tca.digitalWrite8(0x0000);
  delay(500);
}


//  -- END OF FILE --
