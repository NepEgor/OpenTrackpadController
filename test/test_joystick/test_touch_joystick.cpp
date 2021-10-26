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

    int32_t touch_x = 150 + 1000;
    int32_t touch_y = 350 + 20;

    int16_t x;
    int16_t y;

    TouchControl* tcontrol = &tjoystick;

    int8_t res = tcontrol->touch(touch_x, touch_y);
    if (res > 0)
    {
        switch(tcontrol->getControlType())
        {
            case TouchControl::CT_NONE:
                printf("CT_NONE\n");
                break;

            case TouchControl::CT_JOYSTICK:

                x = ((TouchJoystick*)tcontrol)->getX();
                y = ((TouchJoystick*)tcontrol)->getY();

                printf("CT_JOYSTICK (%i, %i)\n", x, y);
                break;
        }
    }
    else
    if (res < 0)
    {
        printf("Impossible Error\n");
    }
    else
    {
        printf("Touch out of bounds\n");
    }
    
    printf("\n");

    return 0;
}