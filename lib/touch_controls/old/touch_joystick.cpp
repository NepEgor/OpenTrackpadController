#include "touch_joystick.h"

#include <math.h>

TouchJoystick::TouchJoystick(int32_t pos_x, int32_t pos_y, int32_t pos_r, int16_t usb_x, int16_t usb_y, int16_t usb_r)
{
    init(pos_x, pos_y, pos_r, usb_x, usb_y, usb_r);
}

void TouchJoystick::init(int32_t pos_x, int32_t pos_y, int32_t pos_r, int16_t usb_x, int16_t usb_y, int16_t usb_r)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->pos_r = pos_r;
    this->pos_r2 = pos_r * pos_r;

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

int8_t TouchJoystick::touch(int32_t tx, int32_t ty, int16_t* rx, int16_t* ry)
{   
    int8_t ret = 2;

    tx -= pos_x;
    ty -= pos_y;

    int32_t t2 = tx * tx + ty * ty;
    
    x = usb_x;
    y = usb_y;

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
    else // between dead zones
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

    if (invert_x) x = usb_x + usb_r - x;
    if (invert_y) y = usb_y + usb_r - y;

    if (rx != NULL && ry != NULL)
    {
        *rx = x;
        *ry = y;
    }

    return ret;
}