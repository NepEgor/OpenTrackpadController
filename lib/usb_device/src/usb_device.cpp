#include "usb_device.h"

#include "usbd_hid_custom_if.h"

USB_Device::USB_Device(void)
{
    
}

void USB_Device::begin(void)
{
    HID_Custom_Init();
}

void USB_Device::end(void)
{
    HID_Custom_DeInit();
}
