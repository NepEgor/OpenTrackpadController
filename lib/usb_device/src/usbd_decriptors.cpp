#include "usbd_descriptors.h"

#include "usbd_report.h"

#include "usbd_def.h"

// USB HID device descriptor
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

// USB HID device FS Configuration Descriptor
__ALIGN_BEGIN uint8_t USBD_HID_CUSTOM_CfgFSDesc[]  __ALIGN_END = {
    0x09, // bLength: Configuration Descriptor size 
    USB_DESC_TYPE_CONFIGURATION, // bDescriptorType: Configuration 
    LOBYTE(USB_HID_CUSTOM_CONFIG_DESC_SIZ),    // wTotalLength: Bytes returned 
    HIBYTE(USB_HID_CUSTOM_CONFIG_DESC_SIZ),
    0x04,         //bNumInterfaces: 4 interface
    0x01,         //bConfigurationValue: Configuration value
    0x00,         //iConfiguration: Index of string descriptor describing the configuration
    0xA0,         //bmAttributes: bus powered and no Support Remote Wake-up 
    0xFA,         //MaxPower 100 mA: this current is used for detecting Vbus

//Interface 0
	9,				//bLength (length of interface descriptor 9 bytes)
	4,				//bDescriptorType (4 is interface)
	0,				//bInterfaceNumber (This is interface 0)
	0,				//bAlternateSetting (used to select alternate setting.  notused)
	2,				//bNumEndpoints (this interface has 2 endpoints)
	0xFF,			//bInterfaceClass (Vendor Defined is 255)
	0x5D,			//bInterfaceSubClass
	0x01,			//bInterfaceProtocol
	0,				//iInterface (Index of string descriptor for describing this notused)
	//Some sort of common descriptor? I pulled this from Message Analyzer dumps of an actual controller
	17,33,0,1,1,37,129,20,0,0,0,0,19,2,8,0,0,
	//Endpoint 1 IN
	7,				//bLength (length of ep1in in descriptor 7 bytes)
	5,				//bDescriptorType (5 is endpoint)
	0x81,			//bEndpointAddress (0x81 is IN1)
	0x03,			//bmAttributes (0x03 is interrupt no synch, usage type data)
	0x20, 0x00,		//wMaxPacketSize (0x0020 is 1x32 bytes)
	4,				//bInterval (polling interval in frames 4 frames)
	//Endpoint 2 OUT
	7,				//bLength (length of ep2out in descriptor 7 bytes)
	5,				//bDescriptorType (5 is endpoint)
	0x02,			//bEndpointAddress (0x02 is OUT2)
	0x03,			//bmAttributes (0x03 is interrupt no synch, usage type data)
	0x20, 0x00,		//wMaxPacketSize (0x0020 is 1x32 bytes)
	8,				//bInterval (polling interval in frames 8 frames)
//Interface 1
	9,				//bLength (length of interface descriptor 9 bytes)
	4,				//bDescriptorType (4 is interface)
	1,				//bInterfaceNumber (This is interface 1)
	0,				//bAlternateSetting (used to select alternate setting.  notused)
	4,				//bNumEndpoints (this interface has 4 endpoints)
	0xFF,			//bInterfaceClass (Vendor Defined is 255)
	0x5D,			//bInterfaceSubClass (93)
	0x03,			//bInterfaceProtocol (3)
	0,				//iInterface (Index of string descriptor for describing this notused)
	//A different common descriptor? I pulled this from Message Analyzer dumps of an actual controller
	27,33,0,1,1,1,131,64,1,4,32,22,133,0,0,0,0,0,0,22,5,0,0,0,0,0,0,
	//Endpoint 3 IN
	7,				//bLength (length of ep3in descriptor 7 bytes)
	5,				//bDescriptorType (5 is endpoint)
	0x83,			//bEndpointAddress (0x83 is IN3)
	0x03,			//bmAttributes (0x03 is interrupt no synch, usage type data)
	0x20, 0x00,		//wMaxPacketSize (0x0020 is 1x32 bytes)
	2,				//bInterval (polling interval in frames 2 frames)
	//Endpoint 4 OUT
	7,				//bLength (length of ep4out descriptor 7 bytes)
	5,				//bDescriptorType (5 is endpoint)
	0x04,			//bEndpointAddress (0x04 is OUT4)
	0x03,			//bmAttributes (0x03 is interrupt no synch, usage type data)
	0x20, 0x00,		//wMaxPacketSize (0x0020 is 1x32 bytes)
	4,				//bInterval (polling interval in frames 4 frames)
	//Endpoint 5 IN
	7,				//bLength (length of ep5in descriptor 7 bytes)
	5,				//bDescriptorType (5 is endpoint)
	0x85,			//bEndpointAddress (0x85 is IN5)
	0x03,			//bmAttributes (0x03 is interrupt no synch, usage type data)
	0x20, 0x00,		//wMaxPacketSize (0x0020 is 1x32 bytes)
	64,				//bInterval (polling interval in frames 64 frames)
	//Endpoint 5 OUT (shares endpoint number with previous)
	7,				//bLength (length of ep5out descriptor 7 bytes)
	5,				//bDescriptorType (5 is endpoint)
	0x05,			//bEndpointAddress (0x05 is OUT5)
	0x03,			//bmAttributes (0x03 is interrupt no synch, usage type data)
	0x20, 0x00,		//wMaxPacketSize (0x0020 is 1x32 bytes)
	16,				//bInterval (polling interval in frames 16 frames)
//Interface 2
	9,				//bLength (length of interface descriptor 9 bytes)
	4,				//bDescriptorType (4 is interface)
	2,				//bInterfaceNumber (This is interface 2)
	0,				//bAlternateSetting (used to select alternate setting.  notused)
	1,				//bNumEndpoints (this interface has 4 endpoints)
	0xFF,			//bInterfaceClass (Vendor Defined is 255)
	0x5D,			//bInterfaceSubClass (93)
	0x02,			//bInterfaceProtocol (3)
	0,				//iInterface (Index of string descriptor for describing this notused)
	//Common Descriptor.  Seems that these come after every interface description?
	9,33,0,1,1,34,134,7,0,
	//Endpoint 6 IN
	7,				//bLength (length of ep6in descriptor 7 bytes)
	5,				//bDescriptorType (5 is endpoint)
	0x86,			//bEndpointAddress (0x86 is IN6)
	0x03,			//bmAttributes (0x03 is interrupt no synch, usage type data)
	0x20, 0x00,		//wMaxPacketSize (0x0020 is 1x32 bytes)
	16,				//bInterval (polling interval in frames 64 frames)+
//Interface 3
//This is the interface on which all the security handshaking takes place
//We don't use this but it could be used for man-in-the-middle stuff
	9,				//bLength (length of interface descriptor 9 bytes)
	4,				//bDescriptorType (4 is interface)
	3,				//bInterfaceNumber (This is interface 3)
	0,				//bAlternateSetting (used to select alternate setting.  notused)
	0,				//bNumEndpoints (this interface has 0 endpoints ???)
	0xFF,			//bInterfaceClass (Vendor Defined is 255)
	0xFD,			//bInterfaceSubClass (253)
	0x13,			//bInterfaceProtocol (19)
	4,				//iInterface (Computer never asks for this, but an x360 would. so include one day?)
	//Another interface another Common Descriptor
	6,65,0,1,1,3
};
