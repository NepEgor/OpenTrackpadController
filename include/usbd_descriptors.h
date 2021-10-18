#ifndef USBD_DESCRIPTORS_H
#define USBD_DESCRIPTORS_H

#include <stdint.h>

#define USB_HID_CUSTOM_CONFIG_DESC_SIZ 34U
#define USB_HID_CUSTOM_DESC_SIZ              9U
#define USB_LEN_DEV_QUALIFIER_DESC    0x0AU
#define HID_CUSTOM_REPORT_DESC_SIZE          30U

//#define HID_KEYBOARD_REPORT_DESC_SIZE 45U

#define HID_DESCRIPTOR_TYPE           0x21

#ifndef HID_HS_BINTERVAL
#define HID_HS_BINTERVAL              0x07U
#endif

#ifndef HID_FS_BINTERVAL
#define HID_FS_BINTERVAL            0x0AU
#endif

#define HID_CUSTOM_INTERFACE           0x00U
#define HID_CUSTOM_EPIN_ADDR           0x81U
#define HID_CUSTOM_EPIN_SIZE           0x08U

//#define HID_KEYBOARD_INTERFACE        0x01U
//#define HID_KEYBOARD_EPIN_ADDR        0x82U
//#define HID_KEYBOARD_EPIN_SIZE        0x08U

// USB HID device FS Configuration Descriptor
extern uint8_t USBD_HID_CUSTOM_CfgFSDesc[USB_HID_CUSTOM_CONFIG_DESC_SIZ];

// USB HID device HS Configuration Descriptor
extern uint8_t USBD_HID_CUSTOM_CfgHSDesc[USB_HID_CUSTOM_CONFIG_DESC_SIZ];

// USB HID device Other Speed Configuration Descriptor
extern uint8_t USBD_HID_CUSTOM_OtherSpeedCfgDesc[USB_HID_CUSTOM_CONFIG_DESC_SIZ];

// USB HID device Configuration Descriptor
extern uint8_t USBD_HID_CUSTOM_Desc[USB_HID_CUSTOM_DESC_SIZ];

// USB HID device Configuration Descriptor
//extern uint8_t USBD_KEYBOARD_HID_Desc[USB_HID_DESC_SIZ];

// USB Standard Device Descriptor
extern uint8_t USBD_HID_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC];

// USB Custom Report Descriptor
extern uint8_t HID_CUSTOM_ReportDesc[HID_CUSTOM_REPORT_DESC_SIZE];

#endif