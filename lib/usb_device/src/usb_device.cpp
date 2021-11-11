#include "usb_device.h"

#include "usbd_hid_custom_if.h"

void USB_Device::begin()
{
    HID_Custom_Init();

    report.msg_type = 0x00;
    report.msg_len = 0x14;
    report.buttons = 0;
    //report.hat = 15;
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

void USB_Device::buttons(uint32_t buttons)
{
    report.buttons = buttons;
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
    //report.hat = dir;
}

void USB_Device::joystick_left(int16_t x, int16_t y)
{
    report.x = x;
    report.y = y;
}

void USB_Device::joystick_right(int16_t x, int16_t y)
{
    report.rx = x;
    report.ry = y;
}

void USB_Device::trigger_left(uint8_t val)
{
    report.trigger_left = val & 0xFF;
}

void USB_Device::trigger_right(uint8_t val)
{
    report.trigger_right = val & 0xFF;
}

void USB_Device::sendReport()
{
    HID_Custom_sendReport((uint8_t*)(&report), sizeof(report));
}
