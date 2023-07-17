#ifndef LEDDISPLAY_H
#define LEDDISPLAY_H

#include "Arduino.h"

class Display {
  public:
    void printTestPattern();
    void DspFrame(uint8_t buffer[18][39]);
    void begin();
    void setBrightness(uint8_t brightness);
    void clearScreen();
    void printSpeed(uint8_t speed);
    void introGraphic();
};

#endif