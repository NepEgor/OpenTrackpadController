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
__ALIGN_BEGIN uint8_t USBD_HID_Joystick_ReportDesc[]  __ALIGN_END = {
	HID_USAGE_PAGE(GENERIC_DESKTOP),
		HID_USAGE(JOYSTICK),
		HID_COLLECTION(APPLICATION),

            HID_REPORT_ID(20), // HID Joystick Report ID

            HID_LOGICAL_MINIMUM(1, 0),
            HID_LOGICAL_MAXIMUM(1, 1),
            HID_REPORT_SIZE(1),
            HID_REPORT_COUNT(32),

            HID_USAGE_PAGE(BUTTON),
            HID_USAGE_MINIMUM(1, 0),
            HID_USAGE_MAXIMUM(1, 32),
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
            HID_USAGE(POINTER),
            HID_COLLECTION(PHYSICAL),
                HID_USAGE(X),
                HID_USAGE(Y),
                HID_USAGE(RX),
                HID_USAGE(RY),
                HID_LOGICAL_MINIMUM(1, 0),
                HID_LOGICAL_MAXIMUM(2, 1022),
                HID_REPORT_SIZE(10),
                HID_REPORT_COUNT(4),
                HID_INPUT(DATA, VARIABLE, ABSOLUTE),
			HID_END_COLLECTION(PHYSICAL),
            
            HID_USAGE(Z),
            HID_USAGE(RZ),
            HID_LOGICAL_MINIMUM(1, 0),
            HID_LOGICAL_MAXIMUM(2, 1022),
            HID_REPORT_SIZE(10),
            HID_REPORT_COUNT(2),
            HID_INPUT(DATA, VARIABLE, ABSOLUTE),

		HID_END_COLLECTION(APPLICATION)
};