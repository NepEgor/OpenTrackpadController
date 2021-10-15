#ifndef USBD_DEVICE_H
#define USBD_DEVICE_H

#include <Arduino.h>

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 4
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE)

class USBD_Device
{
    private:
        uint8_t _buttons;

        void buttons(uint8_t b);

    public:
        USBD_Device(void);

        void begin(void);
        void end(void);

        void click(uint8_t b = MOUSE_LEFT);

        void move(signed char x, signed char y, signed char wheel = 0);
        
        void press(uint8_t b = MOUSE_LEFT);   // press LEFT by default
        void release(uint8_t b = MOUSE_LEFT); // release LEFT by default
        bool isPressed(uint8_t b = MOUSE_LEFT); // check LEFT by default
};

#endif