#ifndef TOUCH_CONTROL_H
#define TOUCH_CONTROL_H

#include <stdint.h>
#include <stddef.h>

class TouchControl
{
    public:

    class TouchControlReturn
    {
        public:
        
        enum ReturnType: uint8_t{
            RT_NONE,
            RT_JOYSTICK,
            RT_DPAD,
        };

        ReturnType return_type = RT_NONE;
    };
    
    protected:

    int32_t pos_x;
    int32_t pos_y;
    int32_t pos_r;
    int32_t pos_r2;

    public:

    TouchControl() {}
    TouchControl(int32_t pos_x, int32_t pos_y, int32_t pos_r);

    virtual void init(int32_t pos_x, int32_t pos_y, int32_t pos_r);

    virtual int8_t touch(int32_t tx, int32_t ty, TouchControlReturn* touch_return) = 0;

};

#endif