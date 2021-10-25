#include "usbd_device.h"

#include "usbd_hid_custom_if.h"

const int16_t usb_x = 512;
const int16_t usb_y = 512;
const int16_t usb_r = 512;

USBD_Device::USBD_Device(void)
{
    
}

void USBD_Device::begin(void)
{
    HID_Custom_Init();
}

void USBD_Device::end(void)
{
    HID_Custom_DeInit();
}
