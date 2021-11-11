#ifndef USB_DEVICE_H
#define USB_DEVICE_H

#include <stdint.h>

#include "usbd_hid_composite_if.h"
#include "usbd_report.h"

class USB_Device
{
    private:
    USBD_HID_Joystick_Report report;

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