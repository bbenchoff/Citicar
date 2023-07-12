#ifndef IS31FL3741_h
#define IS31FL3741_h

#include "Arduino.h"

void writeByte(uint8_t Dev_Add, uint8_t Reg_Add, uint8_t Reg_Dat);

class MyIS41 {
  private:
    uint8_t chipAddress;

  public:
    MyIS41(uint8_t address);
    void begin();
    void printFramebuffer(uint8_t buffer[18][39]);
    void sendData(uint8_t data);
    void printTestPattern();
    void clearDisplay();
    void setGlobalCurrent(uint8_t brightness);

};

#endif