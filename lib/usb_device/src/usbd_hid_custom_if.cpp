#include "usbd_desc.h"
#include "usbd_hid_custom_if.h"
#include "usbd_hid_custom.h"

USBD_HandleTypeDef hUSBD_Device_HID;

static bool HID_custom_initialized = false;

__ALIGN_BEGIN uint8_t USBD_Custom_Class_DeviceDesc[] __ALIGN_END = {
    0x12,                       // bLength
    USB_DESC_TYPE_DEVICE,       // bDescriptorType
    0x00,                       // bcdUSB
    0x02,
    0xFF,                       // bDeviceClass
    0xFF,                       // bDeviceSubClass
    0xFF,                       // bDeviceProtocol
    USB_MAX_EP0_SIZE,           // bMaxPacketSize
    LOBYTE(USBD_VID),           // idVendor
    HIBYTE(USBD_VID),           // idVendor
    LOBYTE(USBD_PID),           // idProduct
    HIBYTE(USBD_PID),           // idProduct
    0x14,                       // bcdDevice rel. 0.00
    0x01,
    USBD_IDX_MFC_STR,           // Index of manufacturer string
    USBD_IDX_PRODUCT_STR,       // Index of product string
    USBD_IDX_SERIAL_STR,        // Index of serial number string
    USBD_MAX_NUM_CONFIGURATION  // bNumConfigurations
};

uint8_t *USBD_Custom_Class_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
    UNUSED(speed);
    *length = sizeof(USBD_Custom_Class_DeviceDesc);
    return (uint8_t *)USBD_Custom_Class_DeviceDesc;
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
