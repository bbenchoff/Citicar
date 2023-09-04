#ifndef Globals_h
#define Globals_h

#include <stdint.h>

extern bool gearDrive;
extern bool gearNeutral;
extern bool gearReverse;

extern uint32_t timestamp;

extern uint8_t testPattern[18][39];
extern uint8_t checkerboard1[18][39];
extern uint8_t checkerboard2[18][39];
extern uint8_t framebuffer[18][39];
extern uint8_t scrollPattern[18][224];

#endif