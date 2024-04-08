#include "touch_joystick.h"

#include <math.h>

TouchJoystick::TouchJoystick(int32_t pos_x, int32_t pos_y, int32_t pos_r)
{
    init(pos_x, pos_y, pos_r);
}

void TouchJoystick::init(int32_t pos_x, int32_t pos_y, int32_t pos_r)
{
    TouchControl::init(pos_x, pos_y, pos_r);

    this->control_type = CT_JOYSTICK;

    this->pos2unit = 1.f / pos_r;

    this->dead_zone_inner = 0;
    this->dead_zone_inner2 = 0;
    this->dead_zone_outer = pos_r;
    this->dead_zone_outer2 = pos_r2;

    this->invert_x = false;
    this->invert_y = false;

    this->x = 0;
    this->y = 0;
}

void TouchJoystick::reset()
{
    TouchControl::reset();
    this->x = 0;
    this->y = 0;
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

    this->pos2unit = 1.f / this->dead_zone_outer;
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

    x = 0;
    y = 0;

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
                x = tx * pos2unit;
                y = ty * pos2unit;
            }
            else // in bounds outside of outer dead zone
            {
                float factor = dead_zone_outer / sqrt(t2) * pos2unit;

                x = tx * factor;
                y = ty * factor;
            }

            if (invert_x) x = -x;
            if (invert_y) y = -y;
        }
    }
    
    return touching;
}