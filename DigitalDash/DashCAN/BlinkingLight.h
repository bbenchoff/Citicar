#ifndef BLINKING_LIGHT_H
#define BLINKING_LIGHT_H

#include <Arduino.h>
#include <mcp_can.h>
#include <mcp_can_dfs.h>

struct BlinkingLight {
    uint32_t canId;  // CAN ID for the light
    bool state;      // Current state of the light
    bool update = false;  // Initially set to false

    BlinkingLight(uint32_t id) : canId(id), state(false) {}

    void turnOn(MCP_CAN& CAN0) {
        if (!state) {
            state = true;
            update = true;
            send(CAN0);  // Send the message immediately
        }
    }

    void turnOff(MCP_CAN& CAN0) {
        if (state) {
            state = false;
            update = true;
            send(CAN0);  // Send the message immediately
        }
    }

    void send(MCP_CAN& CAN0) {
        if (update) {
            byte data[1] = {state ? 0xFF : 0x00};
            CAN0.sendMsgBuf(canId, 1, 1, data);
            update = false;  // Reset the update flag after sending
        }
    }

    void invertState(MCP_CAN& CAN0) {
        state = !state;
        update = true;
        send(CAN0);  // Optionally send immediately on invert
    }
};

#endif // BLINKING_LIGHT_H
