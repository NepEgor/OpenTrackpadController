#include "touch_mouse_joystick.h"

#include <math.h>

void TouchMouseJoystick::init(int32_t pos_x, int32_t pos_y, int32_t pos_r, int16_t usb_x, int16_t usb_y, int16_t usb_r)
{
    TouchJoystick::init(pos_x, pos_y, pos_r, usb_x, usb_y, usb_r);

    this->control_type = CT_MOUSE_JOYSTICK;

    this->sensitivity = this->pos2usb;

    this->trackball_friction = 0;
    this->trackball_vel_x = 0;
    this->trackball_vel_y = 0;

    this->usb_r2 = usb_r * usb_r;

    this->min_delta = 0;
    this->min_delta2 = 0;

    this->time0 = 0;
}

void TouchMouseJoystick::reset()
{
    TouchJoystick::reset();
    this->trackball_vel_x = 0;
    this->trackball_vel_y = 0;
    this->dx = 0;
    this->dy = 0;
}

void TouchMouseJoystick::setSensitivity(float sensitivity)
{
    this->sensitivity = this->pos2usb * sensitivity;
}

void TouchMouseJoystick::setTrackballFriction(float trackball_friction)
{
    this->trackball_friction = trackball_friction;
}

void TouchMouseJoystick::setMinDelta(int16_t min_delta)
{
    this->min_delta = min_delta;
    this->min_delta2 = min_delta * min_delta;
}

TouchMouseJoystick::TouchState TouchMouseJoystick::touch(int8_t fid, int32_t tx, int32_t ty, int32_t tdx, int32_t tdy, uint32_t time)
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
    else // inside the range
    {
        finger_id = fid;

        if (t2 <= dead_zone_outer2)
        {
            touching = TS_RANGE;

            dx = sensitivity * -tdx;
            dy = sensitivity * -tdy;

            float d2 = dx * dx + dy * dy;

            if (d2 < min_delta2)
            {
                float factor = min_delta / sqrt(d2);

                dx = dx * factor;
                dy = dy * factor;
            }
            else
            if (d2 > usb_r2)
            {
                float factor = usb_r / sqrt(d2);

                dx = dx * factor;
                dy = dy * factor;
            }

            float dt = time - time0;
            time0 = time;

            trackball_vel_x = dx / (dt * 1000.f);
            trackball_vel_y = dy / (dt * 1000.f);
            
            x = dx + usb_x;
            y = dy + usb_y;
        }
        else // in bounds outside of outer dead zone - edge spin
        {
            touching = TS_EDGE_SPIN;
            
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

void TouchMouseJoystick::updateTrackball(uint32_t time)
{
    // todo change to circular ranges
    if (trackball_friction > 0 && !touching)
    {
        if (trackball_vel_x != 0)
        {
            int8_t dir = (dx > 0) ? 1 : -1;

            float dt = time - time0;
            float dt2 = dt * dt;

            float x1 = dx + trackball_vel_x * dt - trackball_friction * dt2 * dir;

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
                dx = 0;
                trackball_vel_x = 0;
            }
        }

        if (trackball_vel_y != 0)
        {
            int8_t dir = (dy > 0) ? 1 : -1;

            float dt = time - time0;
            float dt2 = dt * dt;

            float y1 = dy + trackball_vel_y * dt - trackball_friction * dt2 * dir;

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
                dy = 0;
                trackball_vel_y = 0;
            }
        }
    }
}
