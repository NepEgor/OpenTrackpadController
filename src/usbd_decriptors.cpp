#include "usbd_descriptors.h"

#include "usbd_def.h"

#include "hid_def.h"

// USB HID device FS Configuration Descriptor
__ALIGN_BEGIN uint8_t USBD_HID_CUSTOM_CfgFSDesc[USB_HID_CUSTOM_CONFIG_DESC_SIZ]  __ALIGN_END = {
    0x09, // bLength: Configuration Descriptor size 
    USB_DESC_TYPE_CONFIGURATION, // bDescriptorType: Configuration 
    LOBYTE(USB_HID_CUSTOM_CONFIG_DESC_SIZ),    // wTotalLength: Bytes returned 
    HIBYTE(USB_HID_CUSTOM_CONFIG_DESC_SIZ),
    0x01,         //bNumInterfaces: 2 interface
    0x01,         //bConfigurationValue: Configuration value
    0x00,         //iConfiguration: Index of string descriptor describing the configuration
    0xC0,         //bmAttributes: bus powered and no Support Remote Wake-up 
    0x32,         //MaxPower 100 mA: this current is used for detecting Vbus

    //************* Descriptor of  interface ***************
    // 09 
    0x09,         //bLength: Interface Descriptor size
    USB_DESC_TYPE_INTERFACE,//bDescriptorType: Interface descriptor type
    HID_CUSTOM_INTERFACE,         //bInterfaceNumber: Number of Interface
    0x00,         //bAlternateSetting: Alternate setting
    0x01,         //bNumEndpoints
    0x03,         //bInterfaceClass: HID
    0x00,         //bInterfaceSubClass : 1=BOOT, 0=no boot
    0x00,         //nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse
    0x00,         //iInterface: Index of string descriptor
    //******************* Descriptor of Joystick Mouse HID *******************
    // 18 
    0x09,         //bLength: HID Descriptor size
    HID_DESCRIPTOR_TYPE, //bDescriptorType: HID
    0x11,         //bcdHID: HID Class Spec release number
    0x01,
    0x00,         //bCountryCode: Hardware target country
    0x01,         //bNumDescriptors: Number of HID class descriptors to follow
    0x22,         //bDescriptorType
    HID_CUSTOM_REPORT_DESC_SIZE,//wItemLength: Total length of Report descriptor
    0x00,
    //******************* Descriptor of Mouse endpoint *******************
    // 27 
    0x07,          //bLength: Endpoint Descriptor size
    USB_DESC_TYPE_ENDPOINT, //bDescriptorType:

    HID_CUSTOM_EPIN_ADDR,     //bEndpointAddress: Endpoint Address (IN)
    0x03,          //bmAttributes: Interrupt endpoint
    HID_CUSTOM_EPIN_SIZE, //wMaxPacketSize: 4 Byte max 
    0x00,
    HID_FS_BINTERVAL,          //bInterval: Polling Interval
};

// USB HID device HS Configuration Descriptor 
__ALIGN_BEGIN uint8_t USBD_HID_CUSTOM_CfgHSDesc[USB_HID_CUSTOM_CONFIG_DESC_SIZ]  __ALIGN_END = {
    0x09, // bLength: Configuration Descriptor size 
    USB_DESC_TYPE_CONFIGURATION, // bDescriptorType: Configuration 
    LOBYTE(USB_HID_CUSTOM_CONFIG_DESC_SIZ),    // wTotalLength: Bytes returned 
    HIBYTE(USB_HID_CUSTOM_CONFIG_DESC_SIZ),
    0x01,         //bNumInterfaces: 2 interface
    0x01,         //bConfigurationValue: Configuration value
    0x00,         //iConfiguration: Index of string descriptor describing the configuration
    0xC0,         //bmAttributes: bus powered and no Support Remote Wake-up 
    0x32,         //MaxPower 100 mA: this current is used for detecting Vbus

    //************* Descriptor of  interface ***************
    // 09 
    0x09,         //bLength: Interface Descriptor size
    USB_DESC_TYPE_INTERFACE,//bDescriptorType: Interface descriptor type
    HID_CUSTOM_INTERFACE,         //bInterfaceNumber: Number of Interface
    0x00,         //bAlternateSetting: Alternate setting
    0x01,         //bNumEndpoints
    0x03,         //bInterfaceClass: HID
    0x00,         //bInterfaceSubClass : 1=BOOT, 0=no boot
    0x00,         //nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse
    0x00,         //iInterface: Index of string descriptor
    //******************* Descriptor of Joystick Mouse HID *******************
    // 18 
    0x09,         //bLength: HID Descriptor size
    HID_DESCRIPTOR_TYPE, //bDescriptorType: HID
    0x11,         //bcdHID: HID Class Spec release number
    0x01,
    0x00,         //bCountryCode: Hardware target country
    0x01,         //bNumDescriptors: Number of HID class descriptors to follow
    0x22,         //bDescriptorType
    HID_CUSTOM_REPORT_DESC_SIZE,//wItemLength: Total length of Report descriptor
    0x00,
    //******************* Descriptor of Mouse endpoint *******************
    // 27 
    0x07,          //bLength: Endpoint Descriptor size
    USB_DESC_TYPE_ENDPOINT, //bDescriptorType:

    HID_CUSTOM_EPIN_ADDR,     //bEndpointAddress: Endpoint Address (IN)
    0x03,          //bmAttributes: Interrupt endpoint
    HID_CUSTOM_EPIN_SIZE, //wMaxPacketSize: 4 Byte max 
    0x00,
    HID_HS_BINTERVAL,          //bInterval: Polling Interval
};

// USB HID device Other Speed Configuration Descriptor 
__ALIGN_BEGIN uint8_t USBD_HID_CUSTOM_OtherSpeedCfgDesc[USB_HID_CUSTOM_CONFIG_DESC_SIZ] __ALIGN_END = {
    0x09, // bLength: Configuration Descriptor size 
    USB_DESC_TYPE_CONFIGURATION, // bDescriptorType: Configuration 
    LOBYTE(USB_HID_CUSTOM_CONFIG_DESC_SIZ),    // wTotalLength: Bytes returned 
    HIBYTE(USB_HID_CUSTOM_CONFIG_DESC_SIZ),
    0x01,         //bNumInterfaces: 2 interface
    0x01,         //bConfigurationValue: Configuration value
    0x00,         //iConfiguration: Index of string descriptor describing the configuration
    0xC0,         //bmAttributes: bus powered and no Support Remote Wake-up 
    0x32,         //MaxPower 100 mA: this current is used for detecting Vbus

    //************* Descriptor of  interface ***************
    // 09 
    0x09,         //bLength: Interface Descriptor size
    USB_DESC_TYPE_INTERFACE,//bDescriptorType: Interface descriptor type
    HID_CUSTOM_INTERFACE,         //bInterfaceNumber: Number of Interface
    0x00,         //bAlternateSetting: Alternate setting
    0x01,         //bNumEndpoints
    0x03,         //bInterfaceClass: HID
    0x00,         //bInterfaceSubClass : 1=BOOT, 0=no boot
    0x00,         //nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse
    0x00,         //iInterface: Index of string descriptor
    //******************* Descriptor of Joystick Mouse HID *******************
    // 18 
    0x09,         //bLength: HID Descriptor size
    HID_DESCRIPTOR_TYPE, //bDescriptorType: HID
    0x11,         //bcdHID: HID Class Spec release number
    0x01,
    0x00,         //bCountryCode: Hardware target country
    0x01,         //bNumDescriptors: Number of HID class descriptors to follow
    0x22,         //bDescriptorType
    HID_CUSTOM_REPORT_DESC_SIZE,//wItemLength: Total length of Report descriptor
    0x00,
    //******************* Descriptor of Mouse endpoint *******************
    // 27 
    0x07,          //bLength: Endpoint Descriptor size
    USB_DESC_TYPE_ENDPOINT, //bDescriptorType:

    HID_CUSTOM_EPIN_ADDR,     //bEndpointAddress: Endpoint Address (IN)
    0x03,          //bmAttributes: Interrupt endpoint
    HID_CUSTOM_EPIN_SIZE, //wMaxPacketSize: 4 Byte max 
    0x00,
    HID_FS_BINTERVAL,          //bInterval: Polling Interval
};

// USB HID device Configuration Descriptor 
__ALIGN_BEGIN uint8_t USBD_HID_CUSTOM_Desc[USB_HID_CUSTOM_DESC_SIZ]  __ALIGN_END  = {
    USB_HID_CUSTOM_DESC_SIZ,         //bLength: HID Descriptor size
    HID_DESCRIPTOR_TYPE, //bDescriptorType: HID
    0x11,         //bcdHID: HID Class Spec release number
    0x01,
    0x00,         //bCountryCode: Hardware target country
    0x01,         //bNumDescriptors: Number of HID class descriptors to follow
    0x22,         //bDescriptorType
    HID_CUSTOM_REPORT_DESC_SIZE,//wItemLength: Total length of Report descriptor
    0x00
};

// USB Standard Device Descriptor 
__ALIGN_BEGIN uint8_t USBD_HID_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC]  __ALIGN_END = {
    USB_LEN_DEV_QUALIFIER_DESC,
    USB_DESC_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    0x01,
    0x00,
};

__ALIGN_BEGIN uint8_t HID_CUSTOM_ReportDesc[HID_CUSTOM_REPORT_DESC_SIZE]  __ALIGN_END = {
	HID_USAGE_PAGE(GENERIC_DESKTOP),
		HID_USAGE(JOYSTICK),
		HID_COLLECTION(APPLICATION),
			HID_COLLECTION(PHYSICAL),
				HID_USAGE_PAGE(GENERIC_DESKTOP),
				HID_USAGE(X),
				HID_USAGE(Y),
				HID_USAGE(Z),
				HID_LOGICAL_MINIMUM(1, 0),
				HID_LOGICAL_MAXIMUM(2, 1024),
                HID_PHYSICAL_MINIMUM(1, 0),
				HID_PHYSICAL_MAXIMUM(2, 1024),
				HID_REPORT_SIZE(16),
				HID_REPORT_COUNT(3),
				HID_INPUT(DATA, VARIABLE, ABSOLUTE),
			HID_END_COLLECTION(PHYSICAL),
		HID_END_COLLECTION(APPLICATION)
};
