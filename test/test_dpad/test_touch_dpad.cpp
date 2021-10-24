#include "touch_dpad.h"

#include <stdio.h>

int main()
{
    int32_t pos_x = 0;
    int32_t pos_y = 0;
    int32_t pos_r = 10;

    TouchDpad tdpad(pos_x, pos_y, pos_r, TouchDpad::Sector8);
    tdpad.setDeadZoneInner(2);

    int32_t tx, ty;

    tx = 0; ty = 0;
    printf("0  (%i, %i): %u\n", tx, ty, tdpad.touch(tx, ty));

    tx = 0; ty = 5;
    printf("1  (%i, %i): %u\n", tx, ty, tdpad.touch(tx, ty));

    tx = 5; ty = 5;
    printf("12 (%i, %i): %u\n", tx, ty, tdpad.touch(tx, ty));

    tx = 5; ty = 0;
    printf("2 (%i, %i): %u\n", tx, ty, tdpad.touch(tx, ty));

    tx = 5; ty = -5;
    printf("23 (%i, %i): %u\n", tx, ty, tdpad.touch(tx, ty));

    tx = 0; ty = -5;
    printf("3 (%i, %i): %u\n", tx, ty, tdpad.touch(tx, ty));

    tx = -5; ty = -5;
    printf("34 (%i, %i): %u\n", tx, ty, tdpad.touch(tx, ty));

    tx = -5; ty = 0;
    printf("4 (%i, %i): %u\n", tx, ty, tdpad.touch(tx, ty));

    tx = -5; ty = 5;
    printf("41 (%i, %i): %u\n", tx, ty, tdpad.touch(tx, ty));

    return 0;
}