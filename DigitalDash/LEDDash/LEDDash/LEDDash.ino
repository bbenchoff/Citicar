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
  //pause for serial to init
  //can't do while(!serial.begin()) because
  //it won't be attached to a computer in the car
  delay(500);

  Serial.println("\n\nBegin LED Dash");  
}

// the loop function runs over and over again forever
void loop() {
  //display.clearScreen();
  //display.LFSRfade();
  display.clearScreen();
  display.introGraphic();

  for(int i = 0; i < 3 ; i++)
  {
    display.DspFrame(checkerboard1);
    delay(500);
    display.DspFrame(checkerboard2);
    delay(500);
  }
  display.clearScreen();
  delay(1000);
  for(int i = 0; i < 100 ; i++)
  {
    display.printSpeed(i);
    delay(20);
  }
  delay(100);
  
}
