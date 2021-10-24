#ifndef TOUCH_DPAD_H
#define TOUCH_DPAD_H

#include <stdint.h>
#include <stddef.h>

class TouchDpad
{
    public:
    enum TouchDpadType
    {
        Sector4,
        Sector8
    };

    private:

    // position of dpad on trackpad
    int32_t pos_x;
    int32_t pos_y;
    int32_t pos_r;
    int32_t pos_r2; // pos_r ^ 2

    int32_t dead_zone_inner;
    int32_t dead_zone_inner2; // ^ 2

    TouchDpadType type;

    uint8_t button;

    public:

    TouchDpad() {}
    TouchDpad(int32_t pos_x, int32_t pos_y, int32_t pos_r, TouchDpadType type = Sector4);

    void init(int32_t pos_x, int32_t pos_y, int32_t pos_r, TouchDpadType type = Sector4);
    
    void setDeadZoneInner(int32_t dead_zone_inner);

    void setType(TouchDpadType type) {this->type = type;}

    uint8_t touch(int32_t tx, int32_t ty);

    uint8_t getButton() {return button;}
};

#endif