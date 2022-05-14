#ifndef INPUT_MAPPER_H
#define INPUT_MAPPER_H

#include "stdint.h"

namespace InputMapper
{
    void begin();

    void mapTrackpad(uint8_t id, uint8_t fid, int32_t x, int32_t y, int32_t dx, int32_t dy, uint32_t time);

    bool gyroEnabled();
    void gyroUpdate();

    void update(uint32_t time);

    void mapTriggers(uint32_t value[2]);

    enum HardwareButtons: uint8_t
    {
        START,
        SELECT,
        BUMPER_LEFT,
        BUMPER_RIGHT,
        HOME,
        GRIP_A,
        GRIP_B,
        GRIP_X,
        GRIP_Y,
        TRACKPAD_LEFT,
        TRACKPAD_RIGHT,
    };
    
    extern uint16_t button_map[];

    bool mapButton(HardwareButtons button, bool value);

    void sendReport();
}

#endif