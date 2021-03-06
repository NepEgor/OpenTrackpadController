#ifndef USBD_DESCRIPTORS_H
#define USBD_DESCRIPTORS_H

#include <stdint.h>

#define USB_HID_CUSTOM_CONFIG_DESC_SIZ 153U
#define USB_HID_CUSTOM_DEVICE_DESC_SIZ 18U

#ifndef HID_HS_BINTERVAL
#define HID_HS_BINTERVAL 0x07U
#endif

#ifndef HID_FS_BINTERVAL
#define HID_FS_BINTERVAL 0x0AU
#endif

#define HID_CUSTOM_INTERFACE 0x00U
#define HID_CUSTOM_EPIN_ADDR 0x81U
#define HID_CUSTOM_EPIN_SIZE 0x10U

// USB HID device descriptor
extern uint8_t USBD_Custom_Class_DeviceDesc[USB_HID_CUSTOM_DEVICE_DESC_SIZ];

// USB HID device FS Configuration Descriptor
extern uint8_t USBD_HID_CUSTOM_CfgFSDesc[USB_HID_CUSTOM_CONFIG_DESC_SIZ];

#endif