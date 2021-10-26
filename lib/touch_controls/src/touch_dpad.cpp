#include "touch_dpad.h"

#include <math.h>

#ifndef PI
#define PI 3.14159265358979f
#endif

const float k1 = tanf(PI / 8.f); // tan of 22.5 deg for 8 sector dpad
const float k2 = 1 / k1;

TouchDpad::TouchDpad(int32_t pos_x, int32_t pos_y, int32_t pos_r, DpadType dpad_type)
{
    init(pos_x, pos_y, pos_r, dpad_type);
}

void TouchDpad::init(int32_t pos_x, int32_t pos_y, int32_t pos_r, DpadType dpad_type)
{
    TouchControl::init(pos_x, pos_y, pos_r);

    this->control_type = CT_DPAD;
    
    this->dead_zone_inner = 0;
    this->dead_zone_inner2 = 0;

    this->dpad_type = dpad_type;
}

void TouchDpad::setDeadZoneInner(int32_t dead_zone_inner)
{
    this->dead_zone_inner = dead_zone_inner;
    this->dead_zone_inner2 = dead_zone_inner * dead_zone_inner;
}

int8_t TouchDpad::touch(int32_t tx, int32_t ty)
{
    int8_t ret = 2;

    tx -= pos_x;
    ty -= pos_y;

    button = 0;

    int32_t t2 = tx * tx + ty * ty;

    // outside the range
    if (t2 > pos_r2)
    {
        ret = 0;
    }
    else // inside inner dead_zone
    if (t2 < dead_zone_inner2)
    {
        ret = 1;
    }
    else // in bounds
    {
        switch (dpad_type)
        {
            case DPAD_TYPE_SECTOR4:
                button |= (ty < tx);
                button |= (ty < -tx) << 1;

                if (button == 0b11) button = 0b10;
                else if (button == 0b10) button = 0b11;

                ++button;

                break;

            case DPAD_TYPE_SECTOR8:
                button |= (ty < tx * k2);
                button |= (ty < tx * k1) << 1;
                button |= (ty < -tx * k1) << 2;
                button |= (ty < -tx * k2) << 3;

                switch (button)
                {
                    case 0:  button = 1; break;
                    case 1:  button = 5; break; // 1 & 2
                    case 3:  button = 2; break;
                    case 7:  button = 6; break; // 2 & 3
                    case 15: button = 3; break;
                    case 14: button = 7; break; // 3 & 4
                    case 12: button = 4; break;
                    case 8:  button = 8; break; // 4 & 1
                    default: button = 9; break; // error
                }

                break;

            default:
                break;
        }
    }

    return ret;
}