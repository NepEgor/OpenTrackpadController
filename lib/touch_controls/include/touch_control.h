#ifndef TOUCH_CONTROL_H
#define TOUCH_CONTROL_H

#include <stdint.h>

class TouchControl
{
    public:

    enum ControlType: uint8_t
    {
        CT_NONE,
        CT_JOYSTICK,
        CT_MOUSE_JOYSTICK,
        CT_DPAD,
    };

    enum TouchState: uint8_t
    {
        TS_NONE,
        TS_INNER_DZ,
        TS_RANGE,
        TS_EDGE_SPIN,
    };

    protected:

    int32_t pos_x;
    int32_t pos_y;
    int32_t pos_r;
    int32_t pos_r2;

    ControlType control_type;

    int8_t finger_id;

    TouchState touching;

    public:

    TouchControl() {}
    TouchControl(int32_t pos_x, int32_t pos_y, int32_t pos_r);

    virtual void init(int32_t pos_x, int32_t pos_y, int32_t pos_r);

    virtual void reset();

    virtual TouchState touch(int8_t fid, int32_t tx, int32_t ty) = 0;

    int8_t getTouching() {return touching;}

    ControlType getControlType() {return control_type;}
};

#endif