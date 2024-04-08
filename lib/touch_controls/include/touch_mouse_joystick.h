#ifndef TOUCH_MOUSE_JOYSTICK_H
#define TOUCH_MOUSE_JOYSTICK_H

#include "touch_joystick.h"

class TouchMouseJoystick : public TouchJoystick
{
    protected:

    float sensitivity;
    float trackball_friction;

    float trackball_vel_x;
    float trackball_vel_y;

    float dx;
    float dy;

    int16_t min_delta;
    int32_t min_delta2;

    float time0;

    public:

    void init(int32_t pos_x, int32_t pos_y, int32_t pos_r);

    void reset();
    
    void setSensitivity(float sensitivity);

    void setTrackballFriction(float trackball_friction);

    void setMinDelta(int16_t min_delta);

    TouchState touch(int8_t fid, int32_t tx, int32_t ty, int32_t tdx, int32_t tdy, uint32_t time);

    void updateTrackball(uint32_t time);
};

#endif