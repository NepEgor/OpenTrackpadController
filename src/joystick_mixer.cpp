#include "joystick_mixer.h"

#include <math.h>

JoystickMixer::JoystickMixer(int32_t usb_x, int32_t usb_y, int32_t usb_r)
{
    init(usb_x, usb_y, usb_r);
}

void JoystickMixer::init(int32_t usb_x, int32_t usb_y, int32_t usb_r)
{
    this->usb_x = usb_x;
    this->usb_y = usb_y;
    this->usb_r = usb_r;

    this->x = 0;
    this->y = 0;
    this->dx = 0;
    this->dy = 0;

    this->count = 0;
}

void JoystickMixer::mix(float x, float y)
{
    this->x += x;
    this->y += y;

    ++count;
}

void JoystickMixer::mix_delta(float dx, float dy)
{
    this->dx += dx;
    this->dy += dy;
}

void JoystickMixer::getXY(int32_t &X, int32_t &Y)
{
    if (count > 0)
    {
        x = x / count + dx;
        y = y / count + dy;
    }
    else
    {
        x = dx;
        y = dy;
    }

    float len2 = x * x + y * y;
    if (len2 > 1)
    {
        float len = sqrt(len2);

        x /= len;
        y /= len;
    }

    X = usb_x + x * usb_r;
    Y = usb_y + y * usb_r;
}