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

    this->invert_x = 1;
    this->invert_y = 1;
}

void TouchDpad::setDeadZoneInner(int32_t dead_zone_inner)
{
    this->dead_zone_inner = dead_zone_inner;
    this->dead_zone_inner2 = dead_zone_inner * dead_zone_inner;
}

void TouchDpad::setInvertX(bool invert_x)
{
    this->invert_x = invert_x ? -1 : 1;
}

void TouchDpad::setInvertY(bool invert_y)
{
    this->invert_y = invert_y ? -1 : 1;
}

int8_t TouchDpad::touch(int32_t tx, int32_t ty)
{
    int8_t ret = 2;

    tx -= pos_x;
    ty -= pos_y;

    button = NOT_PRESSED;

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
        button = 0;
        
        switch (dpad_type)
        {
            case DPAD_TYPE_SECTOR4:
                button |= (invert_y * ty > invert_x * -tx);
                button |= (invert_y * ty > invert_x *  tx) << 1;

                switch (button)
                {
                    case 0b00: button = 0; break;
                    case 0b01: button = 2; break;
                    case 0b11: button = 4; break;
                    case 0b10: button = 6; break;
                    
                    default: button = NOT_PRESSED; break;
                }

                break;

            case DPAD_TYPE_SECTOR8:
                button |= (invert_y * ty > invert_x * -tx * k2);
                button |= (invert_y * ty > invert_x * -tx * k1) << 1;
                button |= (invert_y * ty > invert_x *  tx * k1) << 2;
                button |= (invert_y * ty > invert_x *  tx * k2) << 3;

                switch (button)
                {
                    case 0:  button = 0; break;
                    case 1:  button = 1; break;
                    case 3:  button = 2; break;
                    case 7:  button = 3; break;
                    case 15: button = 4; break;
                    case 14: button = 5; break;
                    case 12: button = 6; break;
                    case 8:  button = 7; break;
                    
                    default: button = NOT_PRESSED; break;
                }

                break;

            default:
                break;
        }
    }

    return ret;
}