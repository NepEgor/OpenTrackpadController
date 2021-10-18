#ifndef TOUCH_JOYSTICK_H
#define TOUCH_JOYSTICK_H

#include <stdint.h>
#include <stddef.h>

class TouchJoystick
{
    private:

    // position of joystick on trackpad
    int32_t pos_x;
    int32_t pos_y;
    int32_t pos_r;
    int32_t pos_r2; // pos_r ^ 2

    // joystick values for usb report
    int16_t x;
    int16_t y;

    int16_t max_x;
    int16_t max_y;

    float pos2usb_x;
    float pos2usb_y;

    public:

    TouchJoystick(int32_t pos_x, int32_t pos_y, int32_t pos_r, int16_t max_x, int16_t max_y);

    uint8_t touch(int32_t tx, int32_t ty, int16_t* rx = NULL, int16_t* ry = NULL);

    int16_t getX() {return x;}
    int16_t getY() {return y;}

};

#endif