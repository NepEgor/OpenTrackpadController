#include "touch_dpad.h"

#include <stdio.h>

int main()
{
    printf("\n");

    int32_t pos_x = 0;
    int32_t pos_y = 0;
    int32_t pos_r = 10;

    TouchDpad tdpad(pos_x, pos_y, pos_r, TouchDpad::DPAD_TYPE_SECTOR4);
    tdpad.setDeadZoneInner(2);

    //printf("0  (%i, %i): %u\n", tx, ty, tdpad.touch(tx, ty));

    int32_t t_points[] =
    {
         0,  0,    
         0,  5,
         5,  5,
         5,  0,
         5, -5,
         0, -5,
        -5, -5,
        -5,  0,
        -5,  5,
        11, 11,
    };

    uint8_t button;

    TouchControl* tcontrol = &tdpad;

    int N = sizeof(t_points) / sizeof(int32_t);
    for (int i = 0; i < N; i += 2)
    {
        int8_t res = tcontrol->touch(t_points[i], t_points[i + 1]);

        if (res > 0)
        {
            switch(tcontrol->getControlType())
            {
                case TouchControl::CT_NONE:
                    printf("CT_NONE\n");
                    break;

                case TouchControl::CT_DPAD:

                    button = ((TouchDpad*)tcontrol)->getButton();

                    printf("CT_DPAD %i (%i, %i): %u\n", i / 2, t_points[i], t_points[i + 1], button);

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
    }

    printf("\n");

    return 0;
}