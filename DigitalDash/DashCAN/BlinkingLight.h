#ifndef BLINKING_LIGHT_H
#define BLINKING_LIGHT_H

#include <Arduino.h>
#include <mcp_can.h>

struct BlinkingLight {
    uint32_t canId;  // CAN ID for the light
    bool state;      // Current state of the light

    BlinkingLight(uint32_t id) : canId(id), state(false) {}

    void update(MCP_CAN& CAN0) {
        state = !state; // Toggle the state
        byte data[1] = {state ? 0xFF : 0x00};
        CAN0.sendMsgBuf(canId, 1, 1, data);
    }
};

#endif // BLINKING_LIGHT_H
