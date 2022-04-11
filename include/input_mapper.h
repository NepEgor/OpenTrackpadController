#ifndef INPUT_MAPPER_H
#define INPUT_MAPPER_H

#include "stdint.h"

namespace InputMapper
{
    void begin();

    void mapTrackpad(uint8_t id, uint8_t fid, int32_t x, int32_t y);

    void mapTriggers(uint32_t value[2]);

    enum HardwareButtons: uint8_t
    {
        START,
        SELECT,
        TRACKPAD_LEFT,
        TRACKPAD_RIGHT,
        BUMPER_LEFT,
        BUMPER_RIGHT,
        HOME,
        GRIP_A,
        GRIP_B,
        GRIP_X,
        GRIP_Y,
    };
    
    extern uint16_t button_map[];

    void mapButton(HardwareButtons button, bool value);

    // void mapGyro();

    void sendReport();
}

#endif