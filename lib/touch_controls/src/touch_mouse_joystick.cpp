#include "touch_mouse_joystick.h"

#include <math.h>

void TouchMouseJoustick::init(int32_t pos_x, int32_t pos_y, int32_t pos_r, int16_t usb_x, int16_t usb_y, int16_t usb_r)
{
    TouchJoystick::init(pos_x, pos_y, pos_r, usb_x, usb_y, usb_r);

    this->control_type = CT_MOUSE_JOYSTICK;

    this->delta2usb = this->pos2usb * 30;
}

void TouchMouseJoustick::setTrackballFriction(float trackball_friction)
{
    this->trackball_friction = trackball_friction;
}

int8_t TouchMouseJoustick::touch(int8_t fid, int32_t tx, int32_t ty, int32_t tdx, int32_t tdy)
{
    if (finger_id != -1 && finger_id != fid)
    {
        return 0;
    }

    int8_t ret = 2;

    tx -= pos_x;
    ty -= pos_y;

    x = usb_x;
    y = usb_y;

    int32_t t2 = tx * tx + ty * ty;
    
    // outside the range
    if (t2 > pos_r2)
    {
        finger_id = -1;
        return 0;
    }
    else // inside the range
    {
        finger_id = fid;

        if (t2 <= dead_zone_outer2)
        {
            int32_t x32 = -tdx * delta2usb + usb_x;
            int32_t y32 = -tdy * delta2usb + usb_y;

            x = x32 > usb_r? usb_r : (x32 < -usb_r? -usb_r : x32);
            y = y32 > usb_r? usb_r : (y32 < -usb_r? -usb_r : y32);
        }
        else // in bounds outside of outer dead zone - edge spin
        {
            float len = sqrt(t2);

            x = (tx * dead_zone_outer / len) * pos2usb + usb_x;
            y = (ty * dead_zone_outer / len) * pos2usb + usb_y;
        }

        if (invert_x) x = 2 * usb_x - x;
        if (invert_y) y = 2 * usb_y - y;
    }
    
    return ret;
}
