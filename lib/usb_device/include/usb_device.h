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

    static const int16_t usb_joystick_x = 511;
    static const int16_t usb_joystick_y = 511;
    static const int16_t usb_joystick_r = 511;

    USB_Device() {}

    void begin();
    void end();

    void buttons(uint32_t buttons);
    void button(uint8_t button, bool val);
	void dpad(uint8_t dir);

	void joystick_left(uint16_t x, uint16_t y);
	void joystick_right(uint16_t x, uint16_t y);

	void trigger_left(uint16_t val);
	void trigger_right(uint16_t val);

    void sendReport();
};

#endif