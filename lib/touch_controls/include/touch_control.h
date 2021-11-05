#ifndef TOUCH_CONTROL_H
#define TOUCH_CONTROL_H

#include <stdint.h>

class TouchControl
{
    public:

    enum ControlType: uint8_t{
        CT_NONE,
        CT_JOYSTICK,
        CT_DPAD,
    };

    protected:

    int32_t pos_x;
    int32_t pos_y;
    int32_t pos_r;
    int32_t pos_r2;

    ControlType control_type;

    int8_t finger_id;

    public:

    TouchControl() {}
    TouchControl(int32_t pos_x, int32_t pos_y, int32_t pos_r);

    virtual void init(int32_t pos_x, int32_t pos_y, int32_t pos_r);

    virtual int8_t touch(int8_t fid, int32_t tx, int32_t ty) = 0;

    ControlType getControlType() {return control_type;}
};

#endif