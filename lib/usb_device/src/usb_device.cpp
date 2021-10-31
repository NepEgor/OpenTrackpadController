#include "usb_device.h"

#include "usbd_hid_custom_if.h"

void USB_Device::begin()
{
    HID_Custom_Init();

    report.buttons = 0;
    report.hat = 15;
    report.x = usb_joystick_x;
    report.y = usb_joystick_y;
    report.rx = usb_joystick_x;
    report.ry = usb_joystick_y;
    report.trigger_left = 0;
    report.trigger_right = 0;
}

void USB_Device::end()
{
    HID_Custom_DeInit();
}

void USB_Device::button(uint8_t button, bool val)
{
    if (val)
    {
        report.buttons |= (1u << button);
    }
    else
    {
        report.buttons &= ~(1u << button);
    }
}

void USB_Device::dpad(uint8_t dir)
{
    report.hat = dir;
}

void USB_Device::joystick_left(uint16_t x, uint16_t y)
{
    report.x = x & 0x3FF;
    report.y = y & 0x3FF;
}

void USB_Device::joystick_right(uint16_t x, uint16_t y)
{
    report.rx = x & 0x3FF;
    report.ry = y & 0x3FF;
}

void USB_Device::trigger_left(uint16_t val)
{
    report.trigger_left = val & 0x3FF;;
}

void USB_Device::trigger_right(uint16_t val)
{
    report.trigger_right = val & 0x3FF;;
}

void USB_Device::sendReport()
{
    HID_Custom_sendReport((uint8_t*)(&report), sizeof(report));
}
