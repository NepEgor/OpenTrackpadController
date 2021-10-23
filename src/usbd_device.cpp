#include "usbd_device.h"

#include "usbd_hid_custom_if.h"

USBD_Device::USBD_Device(void)
{
    _buttons = 0;
}

void USBD_Device::begin(void)
{
    HID_Custom_Init();
}

void USBD_Device::end(void)
{
    HID_Custom_DeInit();
}

void USBD_Device::click(uint8_t b)
{
    _buttons = b;
    move(0, 0, 0);
    _buttons = 0;
    move(0, 0, 0);
}

void USBD_Device::move(signed char x, signed char y, signed char wheel)
{
    uint8_t m[4];
    m[0] = _buttons;
    m[1] = x;
    m[2] = y;
    m[3] = wheel;

    HID_Custom_sendReport(m, 4);
}

void USBD_Device::buttons(uint8_t b)
{
    if (b != _buttons)
    {
        _buttons = b;
        move(0, 0, 0);
    }
}

void USBD_Device::press(uint8_t b)
{
    buttons(_buttons | b);
}

void USBD_Device::release(uint8_t b)
{
    buttons(_buttons & ~b);
}

bool USBD_Device::isPressed(uint8_t b)
{
    return (b & _buttons) > 0;
}
