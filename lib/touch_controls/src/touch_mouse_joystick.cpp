#include "touch_mouse_joystick.h"

#include <math.h>

void TouchMouseJoustick::init(int32_t pos_x, int32_t pos_y, int32_t pos_r, int16_t usb_x, int16_t usb_y, int16_t usb_r)
{
    TouchJoystick::init(pos_x, pos_y, pos_r, usb_x, usb_y, usb_r);

    this->control_type = CT_MOUSE_JOYSTICK;

    this->sensitivity = this->pos2usb;

    this->trackball_friction = 0;
    this->trackball_vel_x = 0;
    this->trackball_vel_y = 0;

    this->time0 = 0;
}

void TouchMouseJoustick::setSensitivity(float sensitivity)
{
    this->sensitivity = this->pos2usb * sensitivity;
}

void TouchMouseJoustick::setTrackballFriction(float trackball_friction)
{
    this->trackball_friction = trackball_friction;
}

int8_t TouchMouseJoustick::touch(int8_t fid, int32_t tx, int32_t ty, int32_t tdx, int32_t tdy, uint32_t time)
{
    if (finger_id != -1 && finger_id != fid)
    {
        touching = 0;
        return 0;
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
        touching = 0;
        return 0;
    }
    else // inside the range
    {
        finger_id = fid;

        if (t2 <= dead_zone_outer2)
        {
            touching = 2;

            xf = sensitivity * -tdx;
            yf = sensitivity * -tdy;

            xf = xf > usb_r? usb_r : (xf < -usb_r? -usb_r : xf);
            yf = yf > usb_r? usb_r : (yf < -usb_r? -usb_r : yf);

            float dt = time - time0;
            time0 = time;

            trackball_vel_x = xf / (dt * 1000.f);
            trackball_vel_y = yf / (dt * 1000.f);
            
            x = xf + usb_x;
            y = yf + usb_y;
        }
        else // in bounds outside of outer dead zone - edge spin
        {
            touching = 3;
            
            float len = sqrt(t2);

            x = (tx * dead_zone_outer / len) * pos2usb + usb_x;
            y = (ty * dead_zone_outer / len) * pos2usb + usb_y;

            trackball_vel_x = 0;
            trackball_vel_y = 0;
        }

        if (invert_x) x = 2 * usb_x - x;
        if (invert_y) y = 2 * usb_y - y;
    }
    
    return touching;
}

void TouchMouseJoustick::updateTrackball(uint32_t time)
{
    if (trackball_friction > 0 && !touching)
    {
        if (trackball_vel_x != 0)
        {
            int8_t dir = (xf > 0) ? 1 : -1;

            float dt = time - time0;
            float dt2 = dt * dt;

            float x1 = xf + trackball_vel_x * dt - trackball_friction * dt2 * dir;

            if ((dir * x1) > usb_r)
            {
                x1 = dir * usb_r;
            }

            if ((dir * x1) > 0)
            {
                x = x1 + usb_x;
            }
            else
            {
                x = usb_x;
                xf = 0;
                trackball_vel_x = 0;
            }
        }

        if (trackball_vel_y != 0)
        {
            int8_t dir = (yf > 0) ? 1 : -1;

            float dt = time - time0;
            float dt2 = dt * dt;

            float y1 = yf + trackball_vel_y * dt - trackball_friction * dt2 * dir;

            if ((dir * y1) > usb_r)
            {
                y1 = dir * usb_r;
            }

            if ((dir * y1) > 0)
            {
                y = y1 + usb_y;
            }
            else
            {
                y = usb_y;
                yf = 0;
                trackball_vel_y = 0;
            }
        }
    }
}
