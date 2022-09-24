#include "touch_control.h"

TouchControl::TouchControl(int32_t pos_x, int32_t pos_y, int32_t pos_r)
{
    init(pos_x, pos_y, pos_r);
}

void TouchControl::init(int32_t pos_x, int32_t pos_y, int32_t pos_r)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->pos_r = pos_r;
    this->pos_r2 = pos_r * pos_r;

    this->control_type = CT_NONE;

    this->finger_id = -1;

    this->touching = TS_NONE;
}

void TouchControl::reset()
{
    this->finger_id = -1;
    this->touching = TS_NONE;
}
