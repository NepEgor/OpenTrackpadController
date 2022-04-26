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

    this->button = 0;
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

#define XINPUT_DPAD_UP    0b0001
#define XINPUT_DPAD_DOWN  0b0010
#define XINPUT_DPAD_LEFT  0b0100
#define XINPUT_DPAD_RIGHT 0b1000

int8_t TouchDpad::touch(int8_t fid, int32_t tx, int32_t ty)
{
    if (finger_id != -1 && finger_id != fid)
    {
        touching = 0;
        return 0;
    }

    tx -= pos_x;
    ty -= pos_y;

    button = 0;

    int32_t t2 = tx * tx + ty * ty;

    // outside the range
    if (t2 > pos_r2)
    {
        finger_id = -1;
        touching = 0;
        return 0;
    }
    else // inside inner dead_zone
    {
        finger_id = fid;

        if (t2 < dead_zone_inner2)
        {
            touching = 1;
        }
        else // in bounds
        {
            touching = 2;

            switch (dpad_type)
            {
                case DPAD_TYPE_SECTOR_4:
                    button |= (invert_y * ty > invert_x * -tx);
                    button |= (invert_y * ty > invert_x *  tx) << 1;

                    switch (button)
                    {
                        case 0b00: button = XINPUT_DPAD_DOWN;  break;
                        case 0b01: button = XINPUT_DPAD_RIGHT; break;
                        case 0b11: button = XINPUT_DPAD_UP;    break;
                        case 0b10: button = XINPUT_DPAD_LEFT;  break;
                        
                        default: button = 0; break;
                    }

                    break;

                case DPAD_TYPE_SECTOR_8:
                    button |= (invert_y * ty > invert_x * -tx * k2);
                    button |= (invert_y * ty > invert_x * -tx * k1) << 1;
                    button |= (invert_y * ty > invert_x *  tx * k1) << 2;
                    button |= (invert_y * ty > invert_x *  tx * k2) << 3;

                    switch (button)
                    {
                        case 0:  button = XINPUT_DPAD_DOWN;                       break;
                        case 1:  button = XINPUT_DPAD_DOWN   | XINPUT_DPAD_RIGHT; break;
                        case 3:  button = XINPUT_DPAD_RIGHT;                      break;
                        case 7:  button = XINPUT_DPAD_UP     | XINPUT_DPAD_RIGHT; break;
                        case 15: button = XINPUT_DPAD_UP;                         break;
                        case 14: button = XINPUT_DPAD_UP     | XINPUT_DPAD_LEFT;  break;
                        case 12: button = XINPUT_DPAD_LEFT;                       break;
                        case 8:  button = XINPUT_DPAD_DOWN   | XINPUT_DPAD_LEFT;  break;
                        
                        default: button = 0; break;
                    }

                    break;

                default:
                    break;
            }
        }
    }
    
    return touching;
}