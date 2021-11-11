#include "usbd_report.h"

#include "usbd_descriptors.h"
#include "usbd_def.h"

#include "hid_def.h"
/*
__ALIGN_BEGIN uint8_t USBD_HID_CUSTOM_ReportDesc[]  __ALIGN_END = {
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
*/
/*
__ALIGN_BEGIN uint8_t USBD_HID_Joystick_ReportDesc[]  __ALIGN_END = {
	HID_USAGE_PAGE(GENERIC_DESKTOP),
		HID_USAGE(GAME_PAD),
		HID_COLLECTION(APPLICATION),

            HID_REPORT_ID(20), // HID Joystick Report ID

            HID_USAGE_PAGE(BUTTON),
            HID_USAGE_MINIMUM(1, 0),
            HID_USAGE_MAXIMUM(1, 9),
            HID_REPORT_SIZE(1),
            HID_REPORT_COUNT(32),
            HID_INPUT(DATA, VARIABLE, ABSOLUTE),

            HID_USAGE_PAGE(GENERIC_DESKTOP),
            HID_LOGICAL_MINIMUM(1, 0),
            HID_LOGICAL_MAXIMUM(1, 7),
            HID_PHYSICAL_MINIMUM(1, 0),
            HID_PHYSICAL_MAXIMUM(2, 315),
            HID_REPORT_SIZE(4),
            HID_REPORT_COUNT(1),
            HID_USAGE(HAT_SWITCH),
            HID_INPUT(DATA, VARIABLE, ABSOLUTE),

            HID_USAGE_PAGE(GENERIC_DESKTOP),
            HID_COLLECTION(PHYSICAL),
                HID_USAGE(Z),
                HID_USAGE(RZ),
                HID_LOGICAL_MINIMUM(1, 0),
                HID_LOGICAL_MAXIMUM(2, 1022),
                HID_REPORT_SIZE(10),
                HID_REPORT_COUNT(2),
                HID_INPUT(DATA, VARIABLE, ABSOLUTE),
			HID_END_COLLECTION(PHYSICAL),

            HID_USAGE_PAGE(GENERIC_DESKTOP),
            HID_USAGE(POINTER),
            HID_COLLECTION(PHYSICAL),
                HID_USAGE(X),
                HID_USAGE(Y),
                HID_LOGICAL_MINIMUM(1, 0),
                HID_LOGICAL_MAXIMUM(2, 1022),
                HID_REPORT_SIZE(10),
                HID_REPORT_COUNT(2),
                HID_INPUT(DATA, VARIABLE, ABSOLUTE),
			HID_END_COLLECTION(PHYSICAL),

            HID_USAGE_PAGE(GENERIC_DESKTOP),
            HID_USAGE(POINTER),
            HID_COLLECTION(PHYSICAL),
                HID_USAGE(RX),
                HID_USAGE(RY),
                HID_LOGICAL_MINIMUM(1, 0),
                HID_LOGICAL_MAXIMUM(2, 1022),
                HID_REPORT_SIZE(10),
                HID_REPORT_COUNT(2),
                HID_INPUT(DATA, VARIABLE, ABSOLUTE),
			HID_END_COLLECTION(PHYSICAL),
            
		HID_END_COLLECTION(APPLICATION)
};
*/
/*
__ALIGN_BEGIN uint8_t USBD_HID_Joystick_ReportDesc2[]  __ALIGN_END = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x05,                    // USAGE (Game Pad)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x05, 0x01,                    //   USAGE_PAGE (Generic Desktop)
    0x09, 0x3a,                    //   USAGE (Counted Buffer)
    0xa1, 0x02,                    //   COLLECTION (Logical)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x02,                    //     REPORT_COUNT (2)
    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    0x09, 0x3f,                    //     USAGE (Reserved)
    0x09, 0x3b,                    //     USAGE (Byte Count)
    0x81, 0x01,                    //     INPUT (Cnst,Ary,Abs)

    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x35, 0x00,                    //     PHYSICAL_MINIMUM (0)
    0x45, 0x01,                    //     PHYSICAL_MAXIMUM (1)
    0x95, 0x04,                    //     REPORT_COUNT (4)
    0x05, 0x09,                    //     USAGE_PAGE (Button)
    0x19, 0x0c,                    //     USAGE_MINIMUM (Button 12)
    0x29, 0x0f,                    //     USAGE_MAXIMUM (Button 15)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)

    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x35, 0x00,                    //     PHYSICAL_MINIMUM (0)
    0x45, 0x01,                    //     PHYSICAL_MAXIMUM (1)
    0x95, 0x04,                    //     REPORT_COUNT (4)
    0x05, 0x09,                    //     USAGE_PAGE (Button)
    0x09, 0x09,                    //     USAGE (Button 9)
    0x09, 0x0a,                    //     USAGE (Button 10)
    0x09, 0x07,                    //     USAGE (Button 7)
    0x09, 0x08,                    //     USAGE (Button 8)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)

    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x35, 0x00,                    //     PHYSICAL_MINIMUM (0)
    0x45, 0x01,                    //     PHYSICAL_MAXIMUM (1)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x05, 0x09,                    //     USAGE_PAGE (Button)
    0x09, 0x05,                    //     USAGE (Button 5)
    0x09, 0x06,                    //     USAGE (Button 6)
    0x09, 0x0b,                    //     USAGE (Button 11)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)

    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x81, 0x01,                    //     INPUT (Cnst,Ary,Abs)

    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x35, 0x00,                    //     PHYSICAL_MINIMUM (0)
    0x45, 0x01,                    //     PHYSICAL_MAXIMUM (1)
    0x95, 0x04,                    //     REPORT_COUNT (4)
    0x05, 0x09,                    //     USAGE_PAGE (Button)
    0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
    0x29, 0x04,                    //     USAGE_MAXIMUM (Button 4)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)

    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //     LOGICAL_MAXIMUM (255)
    0x35, 0x00,                    //     PHYSICAL_MINIMUM (0)
    0x46, 0xff, 0x00,              //     PHYSICAL_MAXIMUM (255)
    0x95, 0x02,                    //     REPORT_COUNT (2)
    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    0x09, 0x32,                    //     USAGE (Z)
    0x09, 0x35,                    //     USAGE (Rz)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)

    0x75, 0x10,                    //     REPORT_SIZE (16)
    0x16, 0x00, 0x80,              //     LOGICAL_MINIMUM (-32768)
    0x26, 0xff, 0x7f,              //     LOGICAL_MAXIMUM (32767)
    0x36, 0x00, 0x80,              //     PHYSICAL_MINIMUM (-32768)
    0x46, 0xff, 0x7f,              //     PHYSICAL_MAXIMUM (32767)
    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    0x09, 0x01,                    //     USAGE (Pointer)
    0xa1, 0x00,                    //     COLLECTION (Physical)
    0x95, 0x02,                    //       REPORT_COUNT (2)
    0x05, 0x01,                    //       USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    //       USAGE (X)
    0x09, 0x31,                    //       USAGE (Y)
    0x81, 0x02,                    //       INPUT (Data,Var,Abs)
    0xc0,                          //     END_COLLECTION

    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    0x09, 0x01,                    //     USAGE (Pointer)
    0xa1, 0x00,                    //     COLLECTION (Physical)
    0x95, 0x02,                    //       REPORT_COUNT (2)
    0x05, 0x01,                    //       USAGE_PAGE (Generic Desktop)
    0x09, 0x33,                    //       USAGE (Rx)
    0x09, 0x34,                    //       USAGE (Ry)
    0x81, 0x02,                    //       INPUT (Data,Var,Abs)
    0xc0,                          //     END_COLLECTION
    0xc0,                          //   END_COLLECTION
    0xc0                           // END_COLLECTION
};
*/
