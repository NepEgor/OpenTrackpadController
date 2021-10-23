#include "touch_dpad.h"

#include <arm_math.h>

const float k1 = tanf(PI / 8.f); // tan of 22.5 deg for 8 sector dpad
const float k2 = 1 / k1;

TouchDpad::TouchDpad(int32_t pos_x, int32_t pos_y, int32_t pos_r, TouchDpadType type)
{
    init(pos_x, pos_y, pos_r, type);
}

void TouchDpad::init(int32_t pos_x, int32_t pos_y, int32_t pos_r, TouchDpadType type)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->pos_r = pos_r;
    this->pos_r2 = pos_r * pos_r;
    this->type = type;
}

uint8_t TouchDpad::touch(int32_t tx, int32_t ty)
{
    tx -= pos_x;
    ty -= pos_y;

    button = 0;

    if (tx * tx + ty * ty <= pos_r2)
    {
        switch (type)
        {
            case Sector4:
                button |= (ty > tx);
                button |= (ty > -tx) << 1;

                if (button == 0b11) button = 0b10;
                else if (button == 0b10) button = 0b11;

                ++button;

                break;

            case Sector8:
                button |= (ty > tx * k2);
                button |= (ty > tx * k1) << 1;
                button |= (ty > -tx * k1) << 2;
                button |= (ty > -tx * k2) << 3;

                // TODO swaps?

                ++button;

                break;

            default:
                break;
        }
    }

    return button;
}