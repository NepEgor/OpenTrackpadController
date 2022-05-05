#include "touch_joystick.h"

#include <math.h>

TouchJoystick::TouchJoystick(int32_t pos_x, int32_t pos_y, int32_t pos_r, int16_t usb_x, int16_t usb_y, int16_t usb_r)
{
    init(pos_x, pos_y, pos_r, usb_x, usb_y, usb_r);
}

void TouchJoystick::init(int32_t pos_x, int32_t pos_y, int32_t pos_r, int16_t usb_x, int16_t usb_y, int16_t usb_r)
{
    TouchControl::init(pos_x, pos_y, pos_r);

    this->control_type = CT_JOYSTICK;

    this->usb_x = usb_x;
    this->usb_y = usb_y;
    this->usb_r = usb_r;

    this->pos2usb = (float)usb_r / pos_r;

    this->dead_zone_inner = 0;
    this->dead_zone_inner2 = 0;
    this->dead_zone_outer = pos_r;
    this->dead_zone_outer2 = pos_r2;

    this->invert_x = false;
    this->invert_y = false;

    this->x = usb_x;
    this->y = usb_y;
}

void TouchJoystick::setDeadZoneInner(int32_t dead_zone_inner)
{
    this->dead_zone_inner = dead_zone_inner;
    this->dead_zone_inner2 = dead_zone_inner * dead_zone_inner;
}

void TouchJoystick::setDeadZoneOuter(int32_t dead_zone_outer)
{
    this->dead_zone_outer = pos_r - dead_zone_outer; // argument is from the outer edge, atribute is from the center
    this->dead_zone_outer2 = this->dead_zone_outer * this->dead_zone_outer;

    pos2usb = (float)usb_r / this->dead_zone_outer;
}

void TouchJoystick::setInvertX(bool invert_x)
{
    this->invert_x = invert_x;
}

void TouchJoystick::setInvertY(bool invert_y)
{
    this->invert_y = invert_y;
}

void TouchJoystick::setMappedId(uint8_t mapped_id)
{
    this->mapped_id = mapped_id;
}

TouchJoystick::TouchState TouchJoystick::touch(int8_t fid, int32_t tx, int32_t ty)
{
    if (finger_id != -1 && finger_id != fid)
    {
        touching = TS_NONE;
        return touching;
    }

    tx -= pos_x;
    ty -= pos_y;

    x = usb_x;
    y = usb_y;

    int32_t t2 = tx * tx + ty * ty;
    
    // outside the range
    if (t2 > pos_r2)
    {
        finger_id = -1;
        touching = TS_NONE;
        return touching;
    }
    else // inside inner dead_zone
    {
        finger_id = fid;

        if (t2 < dead_zone_inner2)
        {
            touching = TS_INNER_DZ;
        }
        else // between dead zones
        {
            touching = TS_RANGE;

            if (t2 <= dead_zone_outer2)
            {
                x = tx * pos2usb + usb_x;
                y = ty * pos2usb + usb_y;
            }
            else // in bounds outside of outer dead zone
            {
                float len = sqrt(t2);

                x = (tx * dead_zone_outer / len) * pos2usb + usb_x;
                y = (ty * dead_zone_outer / len) * pos2usb + usb_y;
            }

            if (invert_x) x = 2 * usb_x - x;
            if (invert_y) y = 2 * usb_y - y;
        }
    }
    
    return touching;
}