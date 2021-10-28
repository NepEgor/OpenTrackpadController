#include "usbd_desc.h"
#include "usbd_hid_custom_if.h"
#include "usbd_hid_custom.h"

USBD_HandleTypeDef hUSBD_Device_HID;

static bool HID_custom_initialized = false;

void HID_Custom_Init()
{
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
