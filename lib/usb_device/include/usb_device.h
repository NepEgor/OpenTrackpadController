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

        uint16_t buttons:16;        // bytes 2 and 3
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

    USB_Device() {}

    void begin();
    void end();

    void buttons(uint32_t buttons);
    void button(uint8_t button, bool val);
	void dpad(uint8_t dir);

	void joystick_left(int16_t x, int16_t y);
	void joystick_right(int16_t x, int16_t y);

	void trigger_left(uint8_t val);
	void trigger_right(uint8_t val);

    void sendReport();
};

#endif