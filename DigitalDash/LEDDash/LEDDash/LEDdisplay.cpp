
#include "IS31FL3741.h"
#include "Globals.h"
#include "LEDdisplay.h"
#include "Fonts.h"
#include <CANSAME5x.h>

extern CANSAME5x CAN;

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

void Display::clearScreen()
{
  for (int i = 0; i < 18; i++) {
    for (int j = 0; j < 39; j++) {
      framebuffer[i][j] = 0x00;
    }
  }
  is41_1.printFramebuffer(framebuffer);
  is41_2.printFramebuffer(framebuffer);
}

void Display::printGears()   ///do this better
{
  for(int i = 0 ; i < 6 ; i++)
  {
    for(int j = 0 ; j < 6 ; j++)
    {
      if(gearDrive == false)
      {
        framebuffer[i][j+1] = gearSelect[0][i][j];
      }
      else
      {
        framebuffer[i][j+1] = gearSelect[0][i][j] ^ 0xFF; 
      }
      
      if(gearNeutral == false)
      {
        framebuffer[i+6][j+1] = gearSelect[1][i][j];
      }
      else
      {
        framebuffer[i+6][j+1] = gearSelect[1][i][j] ^ 0xFF; 
      }

      if(gearReverse == false)
      {
        framebuffer[i+12][j+1] = gearSelect[2][i][j];
      }
      else
      {
        framebuffer[i+12][j+1] = gearSelect[2][i][j] ^ 0xFF; 
      }
    }
  }
}

void Display::printSpeed(uint8_t speed)
{
  uint8_t tensDigit;
  uint8_t onesDigit;
  uint8_t padding;

  tensDigit = speed / 10;
  onesDigit = speed % 10;



  //clear the framebuffer in previous speed
  for(int i = 0 ; i < 10; i++)
  {
    for(int j = 0 ; j < 12 ; j++)
    {
        framebuffer[i+6][j+21] = 0x00;
    }
  }

  //the Tens Digit
  if(tensDigit != 0)
  {
    for(int i = 0 ; i < 10; i++)
    {
      for(int j = 0 ; j < 7 ; j++)
      {
        framebuffer[i+7][((j-heavyNumbersWidth[tensDigit])-2) - (heavyNumbersWidth[onesDigit]+2) ] = heavyNumbers[tensDigit][i][j];
      }
    }
  }

  //the Ones Digit
  for(int i = 0 ; i < 10; i++)
  {
    for(int j = 0 ; j < 7 ; j++)
    {
      framebuffer[i+7][(j-heavyNumbersWidth[onesDigit])-2] = heavyNumbers[onesDigit][i][j]; 
    }
  }
  is41_1.printFramebuffer(framebuffer);
  is41_2.printFramebuffer(framebuffer);

}

void Display::introGraphic()
{
  for(int i = 0 ; i < 185 ; i++ )
  {   //iterate over all of the intro graphic
    for(int framebufferRow = 0 ; framebufferRow < 18 ; framebufferRow++)
    {
      for(int framebufferColumn = 0 ; framebufferColumn < 39 ; framebufferColumn++)
      {
        framebuffer[framebufferRow][framebufferColumn] = scrollPattern[framebufferRow][framebufferColumn + i];
      }
    }

    if(i == 0)
    {
      CAN.beginExtendedPacket(0x420011);
      CAN.write('C');
      CAN.endPacket();
    }


    is41_1.printFramebuffer(framebuffer);
    is41_2.printFramebuffer(framebuffer);
    delay(10);
  }
}