#include "IS31FL3741.h"
#include "Globals.h"
#include "LEDdisplay.h"

MyIS41 is41_1(0x30);
MyIS41 is41_2(0x33);

void Display::begin()
{
  is41_1.begin();
  is41_2.begin();
}

void Display::DspFrame(uint8_t buffer[18][39])
{ 
  //create a local buffer object
  //and fill with buffer
  uint8_t localFramebuffer[18][39];
    //create a local buffer object
  for (int i = 0; i < 18; i++) {
    for (int j = 0; j < 39; j++) {
      localFramebuffer[i][j] = buffer[i][j];
    }
  }
  is41_1.printFramebuffer(localFramebuffer);
  is41_2.printFramebuffer(localFramebuffer);
  
}


void Display::setBrightness(uint8_t brightness)
{
  is41_1.setGlobalCurrent(brightness);
  is41_2.setGlobalCurrent(brightness);
}

void Display::printTestPattern()
{
  is41_1.printTestPattern();
  is41_2.printTestPattern();
}