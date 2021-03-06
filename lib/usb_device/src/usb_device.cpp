#include "usb_device.h"

#include "usbd_hid_composite_if.h"
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

void USB_Device::button(uint16_t button, uint16_t value)
{
    xinput_report.buttons = ((xinput_report.buttons |  button) &  value) |
                            ((xinput_report.buttons & ~button) & ~value);
}

uint16_t USB_Device::isButtonPressed(uint16_t button)
{
    return xinput_report.buttons & button;
}

void USB_Device::joystick(uint8_t id, int16_t x, int16_t y)
{
    if (id == 0)
    {
        xinput_report.lx = x;
        xinput_report.ly = y;
    }
    else{
        xinput_report.rx = x;
        xinput_report.ry = y;
    }
}

void USB_Device::triggers(uint8_t values[2])
{
    xinput_report.trigger_left  = values[0] & 0xFF;
    xinput_report.trigger_right = values[1] & 0xFF;
}

void USB_Device::sendReport()
{
    HID_Custom_sendReport((uint8_t*)(&xinput_report), sizeof(xinput_report));
}
