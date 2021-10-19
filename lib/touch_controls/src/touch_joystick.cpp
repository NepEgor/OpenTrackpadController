#include "touch_joystick.h"

TouchJoystick::TouchJoystick(int32_t pos_x, int32_t pos_y, int32_t pos_r, int16_t min_x, int16_t min_y, int16_t max_x, int16_t max_y)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->pos_r = pos_r;
    this->pos_r2 = pos_r * pos_r;

    this->min_x = min_x;
    this->min_y = min_y;
    this->max_x = max_x;
    this->max_y = max_y;

    this->cen_x = (max_x - min_x) / 2;
    this->cen_y = (max_y - min_y) / 2;

    this->pos2usb_x = (float)(max_x - min_x) / pos_r;
    this->pos2usb_y = (float)(max_y - min_y) / pos_r;

    this->dead_zone_inner = 0;
    this->dead_zone_inner2 = 0;
    this->dead_zone_outer = pos_r;
    this->dead_zone_outer2 = pos_r2;
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

    pos2usb_x = (float)(max_x - min_x) * pos_r / this->dead_zone_outer;
    pos2usb_y = (float)(max_y - min_y) * pos_r / this->dead_zone_outer;
}

uint8_t TouchJoystick::touch(int32_t tx, int32_t ty, int16_t* rx, int16_t* ry)
{   
    uint8_t ret = 0;

    tx -= pos_x;
    ty -= pos_y;

    int32_t tx2 = tx * tx;
    int32_t ty2 = ty * ty;
    
    // if inside inner dead_zone or outside the range
    if (tx2 + ty2 < dead_zone_inner2 || tx2 + ty2 > pos_r2)
    {
        x = cen_x;
        y = cen_y;

        ret = -1;
    }
    else // between dead zones
    if (tx2 + ty2 <= dead_zone_outer2)
    {
        x = tx * pos2usb_x + min_x;
        y = ty * pos2usb_y + min_y;
    }
    else // in bounds outside of outer dead zone
    {
        x = tx * pos2usb_x + min_x; // TODO dead zone
        y = ty * pos2usb_y + min_y;
    }

    if (rx != NULL && ry != NULL)
    {
        *rx = x;
        *ry = y;
    }

    return ret;
}