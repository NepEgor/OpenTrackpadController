#ifndef TOUCH_JOYSTICK_H
#define TOUCH_JOYSTICK_H

#include "touch_control.h"

class TouchJoystick : public TouchControl
{
    public:

    protected:

    int32_t dead_zone_inner;
    int32_t dead_zone_inner2; // ^ 2
    int32_t dead_zone_outer;
    int32_t dead_zone_outer2; // ^ 2

    int16_t x;
    int16_t y;

    int16_t usb_x;
    int16_t usb_y;
    int16_t usb_r;

    float pos2usb;

    bool invert_x;
    bool invert_y;

    uint8_t mapped_id;

    public:

    TouchJoystick() {}
    TouchJoystick(int32_t pos_x, int32_t pos_y, int32_t pos_r, int16_t usb_x, int16_t usb_y, int16_t usb_r);

    void init(int32_t pos_x, int32_t pos_y, int32_t pos_r, int16_t usb_x, int16_t usb_y, int16_t usb_r);

    void setDeadZoneInner(int32_t dead_zone_inner);
    void setDeadZoneOuter(int32_t dead_zone_outer);

    void setInvertX(bool invert_x = true);
    void setInvertY(bool invert_y = true);

    void setMappedId(uint8_t mapped_id);
    uint8_t getMappedId() {return mapped_id;}

    TouchState touch(int8_t fid, int32_t tx, int32_t ty);

    int16_t getX() {return x;}
    int16_t getY() {return y;}
};

#endif