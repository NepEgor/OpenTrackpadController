#include "touch_joystick.h"

TouchJoystick::TouchJoystick(int32_t pos_x, int32_t pos_y, int32_t pos_r, int16_t max_x, int16_t max_y)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->pos_r = pos_r;
    this->pos_r2 = pos_r * pos_r;

    this->max_x = max_x;
    this->max_y = max_y;

    this->pos2usb_x = (float)max_x / pos_r;
    this->pos2usb_y = (float)max_y / pos_r;
}

uint8_t TouchJoystick::touch(int32_t tx, int32_t ty, int16_t* rx, int16_t* ry)
{
    tx -= pos_x;
    ty -= pos_y;

    // if out of joystick bounds return error
    if ((tx * tx) + (ty * ty) > pos_r2)
    {
        x = 0;
        y = 0;

        return 1;
    }

    x = tx * pos2usb_x;
    y = ty * pos2usb_y;

    if (rx != NULL && ry != NULL)
    {
        *rx = x;
        *ry = y;
    }

    return 0;
}