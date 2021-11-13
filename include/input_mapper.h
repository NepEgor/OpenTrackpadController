#ifndef INPUT_MAPPER_H
#define INPUT_MAPPER_H

#include "stdint.h"

namespace InputMapper
{
    void begin();

    void mapTrackpad(uint8_t id, uint8_t fid, int32_t x, int32_t y);

    void mapTriggers(uint32_t values[2]);

    // 0, 1       - triggers        dunno if triggers will be dual stage
    // 4, 5       - start, select = xinput
    // 6, 7       - trackpads     = xinput L3 & R3
    // 0, 1  << 8 - bumpers       = xinput
    // 2     << 8 - home          = xinput
    // 4 - 7 << 8 - grips         = xinput ABXY
    void mapButtons(uint16_t buttons);

    // void mapGyro();

    void sendReport();
}

#endif