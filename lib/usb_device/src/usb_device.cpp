#include "usb_device.h"

#include "usbd_hid_custom_if.h"

void USB_Device::begin()
{
    HID_Custom_Init();

    xinput_report.msg_type = 0x00;
    xinput_report.msg_len = 0x14;

    xinput_report.buttons = 0;

    xinput_report.lx = usb_joystick_x;
    xinput_report.ly = usb_joystick_y;

    xinput_report.rx = usb_joystick_x;
    xinput_report.ry = usb_joystick_y;

    xinput_report.trigger_left = 0;
    xinput_report.trigger_right = 0;
}

void USB_Device::end()
{
    HID_Custom_DeInit();
}

void USB_Device::buttons(uint32_t buttons)
{
    xinput_report.buttons = buttons;
}

void USB_Device::button(uint8_t button, bool val)
{
    if (val)
    {
        xinput_report.buttons |= (1u << button);
    }
    else
    {
        xinput_report.buttons &= ~(1u << button);
    }
}

void USB_Device::dpad(uint8_t dir)
{
    xinput_report.buttons = dir & 0b1111;
}

void USB_Device::joystick_left(int16_t x, int16_t y)
{
    xinput_report.lx = x;
    xinput_report.ly = y;
}

void USB_Device::joystick_right(int16_t x, int16_t y)
{
    xinput_report.rx = x;
    xinput_report.ry = y;
}

void USB_Device::trigger_left(uint8_t val)
{
    xinput_report.trigger_left = val & 0xFF;
}

void USB_Device::trigger_right(uint8_t val)
{
    xinput_report.trigger_right = val & 0xFF;
}

void USB_Device::sendReport()
{
    HID_Custom_sendReport((uint8_t*)(&xinput_report), sizeof(xinput_report));
}
