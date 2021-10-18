#include "touch_joystick.h"

#include <stdio.h>

int main()
{
    printf("\n");

    int32_t pos_x = 150;
    int32_t pos_y = 350;
    int32_t pos_r = 2000;

    int16_t max_x = 1023;
    int16_t max_y = 1023;

    TouchJoystick tjoystick(pos_x, pos_y, pos_r, max_x, max_y);

    int32_t touch_x = 10000;
    int32_t touch_y = 200;

    int16_t x;
    int16_t y;

    if (!tjoystick.touch(touch_x, touch_y, &x, &y))
    {
        printf("USB coords: (%i, %i)\n", x, y);
    }
    else
    {
        printf("Touch out of bounds\n");
    }
    

    printf("\n");

    return 0;
}