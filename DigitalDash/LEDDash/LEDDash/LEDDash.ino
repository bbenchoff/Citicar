/*
  This is something, I'm going to put some information here
*/
#include <Wire.h>
#include "IS31FL3741.h"

#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
  // Required for Serial on Zero based boards
  #define Serial SERIAL_PORT_USBVIRTUAL
#endif

IS41 is41_1(0x30);
IS41 is41_2(0x33);

// the setup function runs once when you press reset or power the board
void setup() {
  Wire.begin();

  is41_1.begin();
  is41_2.begin();

  Serial.begin(115200);

  while(!Serial);
  Serial.println("\n\nBegin LED Dash");
}

// the loop function runs over and over again forever
void loop() {
  // Your code logic here
}
