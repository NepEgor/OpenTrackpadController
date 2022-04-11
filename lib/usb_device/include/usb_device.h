#ifndef USB_DEVICE_H
#define USB_DEVICE_H

#include <stdint.h>

#include "usbd_hid_composite_if.h"
#include "usbd_report.h"

class USB_Device
{
    private:

    struct __attribute__((packed)) XinputReport
    {
        uint8_t  msg_type:8;        // byte 0
        uint8_t  msg_len:8;         // byte 1

        uint16_t buttons:16;        // byte 2 and byte 3
        uint8_t  trigger_left:8;    // byte 4
        uint8_t  trigger_right:8;   // byte 5
        int16_t  lx:16;             // byte 6
        int16_t  ly:16;             // byte 7
        int16_t  rx:16;             // byte 8
        int16_t  ry:16;             // byte 9
        
        //uint32_t unused0:32; // not send due to endpoint size issue
        //uint16_t unused1:16; // not send due to endpoint size issue
    } xinput_report;

    public:

    static const int16_t usb_joystick_x = 0;
    static const int16_t usb_joystick_y = 0;
    static const int16_t usb_joystick_r = 0x7FFF;

    enum XinputButtons: uint16_t
    {   
        DPAD_UP = 0x0001,
        DPAD_DOWN = 0x0002,
        DPAD_LEFT = 0x0004,
        DPAD_RIGHT = 0x0008,

        START = 0x0010,
        SELECT = 0x0020,
        JOYSTICK_LEFT = 0x0040,
        JOYSTICK_RIGHT = 0x0080,

        BUMPER_LEFT = 0x0100,
        BUMPER_RIGHT = 0x0200,
        HOME = 0x0400,
        EMPTY = 0x0800,

        FACE_A = 0x1000,
        FACE_B = 0x2000,
        FACE_X = 0x4000,
        FACE_Y = 0x8000,
    };

    USB_Device() {}

    void begin();
    void end();

    void button(uint16_t button, uint16_t value);

	void joystick(uint8_t id, int16_t x, int16_t y);

	void triggers(uint8_t values[2]);

    void sendReport();
};

#endif