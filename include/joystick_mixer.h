#ifndef JOYSTICK_MIXER_H
#define JOYSTICK_MIXER_H

#include <stdint.h>

class JoystickMixer
{
    private:

    float x, y;
    float dx, dy;

    uint32_t count;

    int32_t usb_x;
    int32_t usb_y;
    int32_t usb_r;

    public:

    JoystickMixer() {}
    JoystickMixer(int32_t usb_x, int32_t usb_y, int32_t usb_r);

    void init(int32_t usb_x, int32_t usb_y, int32_t usb_r);

    void mix(float x, float y);

    void mix_delta(float dx, float dy);

    void getXY(int32_t &x, int32_t &y);
};

#endif