#include "touch_joystick.h"

#include <stdio.h>

int main()
{
    printf("\n");

    int32_t pos_x = 150;
    int32_t pos_y = 350;
    int32_t pos_r = 2000;

    int16_t usb_x = 512;
    int16_t usb_y = 512;
    int16_t usb_r = 512;

    TouchJoystick tjoystick(pos_x, pos_y, pos_r, usb_x, usb_y, usb_r);

    int32_t touch_x = 150 + 2000;
    int32_t touch_y = 350 + 0;

    int16_t x;
    int16_t y;

    TouchControl::TouchControlReturn touch_return;
    TouchControl* tcontrol = &tjoystick;

    int8_t res = tcontrol->touch(touch_x, touch_y, &touch_return);
    if (res > 0)
    {
        switch(touch_return.return_type)
        {
            case TouchControl::TouchControlReturn::RT_NONE:
                printf("RT_NONE\n");
                break;

            case TouchControl::TouchControlReturn::RT_JOYSTICK:
                x = ((TouchJoystick::TouchJoystickReturn*)&touch_return)->x;
                y = ((TouchJoystick::TouchJoystickReturn*)&touch_return)->y;
                printf("RT_JOYSTICK (%i, %i)\n", x, y);
                break;
        }
    }
    else
    if (res < 0)
    {
        printf("Pointer Error\n");
    }
    else
    {
        printf("Touch out of bounds\n");
    }
    

    printf("\n");

    return 0;
}