/*
  This is something, I'm going to put some information here
*/
#include <Arduino.h>
#include <Wire.h>
#include "IS31FL3741.h"
#include "Globals.h"
#include "LEDdisplay.h"


#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
  // Required for Serial on Zero based boards
  #define Serial SERIAL_PORT_USBVIRTUAL
#endif

Display display;

// the setup function runs once when you press reset or power the board
void setup() {
  Wire.begin();

  display.begin();

  Serial.begin(115200);
  while(!Serial);
  Serial.println("\n\nBegin LED Dash");  
}

// the loop function runs over and over again forever
void loop() {
    display.DspFrame(checkerboard1);
    delay(500);
    display.DspFrame(checkerboard2);
    delay(500);
  
}
