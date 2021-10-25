#ifndef USBD_DEVICE_H
#define USBD_DEVICE_H

#include <Arduino.h>

#include "touch_controls_all.h"

class USBD_Device
{
    private:
        // 0 - right bumper
        // 1 - left bumper
        // 2 - right trigger full
        // 3 - left trigger full
        // 4 - right trackpad
        // 5 - left trackpad
        // 6 - right front grip
        // 7 - right rear grip
        // 8 - left front grip
        // 9 - left rear grip
        uint16_t button_map[10];

        // Trackpads
        // 0 - right, 1 - left
        TouchJoystick* tjoystick[2];
        TouchDpad* tdpad[2];
        
        // TODO triggers

    public:
        USBD_Device();

        void begin();
        void end();

        void addTouchJoystick(TouchJoystick* tjoystick);
        void addTouchDpad(TouchDpad* tdpad);

};

#endif