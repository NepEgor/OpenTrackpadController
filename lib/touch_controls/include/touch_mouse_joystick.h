#ifndef TOUCH_MOUSE_JOYSTICK_H
#define TOUCH_MOUSE_JOYSTICK_H

#include "touch_joystick.h"

class TouchMouseJoustick : public TouchJoystick
{
    protected:

    float sensitivity;
    float trackball_friction;

    public:

    void init(int32_t pos_x, int32_t pos_y, int32_t pos_r, int16_t usb_x, int16_t usb_y, int16_t usb_r);
    
    void setSensitivity(float sensitivity);

    void setTrackballFriction(float trackball_friction);

    int8_t touch(int8_t fid, int32_t tx, int32_t ty, int32_t tdx, int32_t tdy);
};

#endif