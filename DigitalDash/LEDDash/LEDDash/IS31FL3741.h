#ifndef IS31FL3741_h
#define IS31FL3741_h

#include "Arduino.h"

void writeByte(uint8_t Dev_Add, uint8_t Reg_Add, uint8_t Reg_Dat);

class IS41
{
  public:
    IS41(int Address);
    void begin();
  private:
    int _Address;
};

#endif