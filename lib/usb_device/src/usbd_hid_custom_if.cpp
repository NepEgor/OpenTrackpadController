#include "usbd_desc.h"
#include "usbd_hid_custom_if.h"
#include "usbd_hid_custom.h"

#include "usbd_descriptors.h"

USBD_HandleTypeDef hUSBD_Device_HID;

static bool HID_custom_initialized = false;

uint8_t* USBD_Custom_Class_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t* length)
{
    UNUSED(speed);
    *length = USB_HID_CUSTOM_DEVICE_DESC_SIZ;
    return (uint8_t*)USBD_Custom_Class_DeviceDesc;
}

void HID_Custom_Init()
{
    USBD_Desc.GetDeviceDescriptor = USBD_Custom_Class_DeviceDescriptor; // reassign device descriptor to a custom one

    if (USBD_Init(&hUSBD_Device_HID, &USBD_Desc, 0) == USBD_OK)
    {
        if (USBD_RegisterClass(&hUSBD_Device_HID, USBD_CUSTOM_HID_CLASS) == USBD_OK)
        {
            USBD_Start(&hUSBD_Device_HID);
            HID_custom_initialized = true;
        }
    }
}

void HID_Custom_DeInit()
{
    if (HID_custom_initialized)
    {
        USBD_Stop(&hUSBD_Device_HID);
        USBD_DeInit(&hUSBD_Device_HID);

        HID_custom_initialized = false;
    }
}

void HID_Custom_sendReport(uint8_t* report, uint16_t len)
{
    USBD_HID_CUSTOM_SendReport(&hUSBD_Device_HID, report, len);
}
