#include "touch_controls_all.h"

#include <stdio.h>

int main()
{
    printf("\n");

    int32_t t_points[] =
    {
           0,    0,    
           0,  500,
         500,  500,
         500,    0,
         500, -500,
           0, -500,
        -500, -500,
        -500,    0,
        -500,  500,

        3000, 3000,

        3000,    0,
        2000,    0,
        4000,    0,
        3000, 1000,
        3000,-1000,
    };

    int num_points = sizeof(t_points) / sizeof(int32_t);

    TouchJoystick tjoystick(3000, 0, 1000, 512, 512, 512);

    TouchDpad tdpad(0, 0, 1000, TouchDpad::DPAD_TYPE_SECTOR8);
    tdpad.setDeadZoneInner(100);

    TouchControl* tcontrols[] = 
    {
        &tjoystick,
        &tdpad,
    };

    int num_controls = sizeof(tcontrols) / sizeof(TouchControl*);

    for (int j = 0; j < num_points; j += 2)
    {
        for (int i = 0; i < num_controls; ++i)
        {
            printf("Touch %i at (%i, %i)  ", i, t_points[j], t_points[j + 1]);
            int8_t res = tcontrols[i]->touch(t_points[j], t_points[j + 1]);
            if (res > 0)
            {
                switch(tcontrols[i]->getControlType())
                {
                    case TouchControl::CT_NONE:
                        printf("CT_NONE\n");
                        break;

                    case TouchControl::CT_JOYSTICK:
                        printf("CT_JOYSTICK (%i, %i)\n",
                            ((TouchJoystick*)tcontrols[i])->getX(),
                            ((TouchJoystick*)tcontrols[i])->getY()
                        );
                        break;

                    case TouchControl::CT_DPAD:
                        printf("CT_DPAD %u\n", ((TouchDpad*)tcontrols[i])->getButton());
                        break;
                }

                break;
            }
            else
            if (res < 0)
            {
                printf("Impossible Error\n");
            }
            else
            {
                printf("not touched\n", i);
            }
        }
    }

    printf("\nTest end\n");

    return 0;
}