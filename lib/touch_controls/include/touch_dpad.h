#ifndef TOUCH_DPAD_H
#define TOUCH_DPAD_H

#include "touch_control.h"

class TouchDpad : public TouchControl
{
    public:

    enum DpadType
    {
        DPAD_TYPE_SECTOR4,
        DPAD_TYPE_SECTOR8
    };

    static const uint8_t NOT_PRESSED = 15;

    private:

    int32_t dead_zone_inner;
    int32_t dead_zone_inner2; // ^ 2

    DpadType dpad_type;

    uint8_t button;

    int8_t invert_x;
    int8_t invert_y;

    public:

    TouchDpad() {}
    TouchDpad(int32_t pos_x, int32_t pos_y, int32_t pos_r, DpadType dpad_type = DPAD_TYPE_SECTOR4);

    void init(int32_t pos_x, int32_t pos_y, int32_t pos_r, DpadType dpad_type = DPAD_TYPE_SECTOR4);
    
    void setDeadZoneInner(int32_t dead_zone_inner);

    void setType(DpadType dpad_type) {this->dpad_type = dpad_type;}

    void setInvertX(bool invert_x = true);
    void setInvertY(bool invert_y = true);

    int8_t touch(int32_t tx, int32_t ty);

    uint8_t getButton() {return button;}
};

#endif