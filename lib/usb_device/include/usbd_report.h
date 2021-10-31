#ifndef USBD_REPORT_H
#define USBD_REPORT_H

#include <stdint.h>

//#define HID_CUSTOM_REPORT_DESC_SIZE 34U
#define HID_JOYSTICK_REPORT_DESC_SIZE 89U

// USB Custom Report Descriptor
//extern uint8_t USBD_HID_CUSTOM_ReportDesc[HID_CUSTOM_REPORT_DESC_SIZE];
extern uint8_t USBD_HID_Joystick_ReportDesc[HID_JOYSTICK_REPORT_DESC_SIZE];

struct __attribute__((packed)) USBD_HID_Joystick_Report
{
    uint8_t  reportID = 20;
    uint32_t buttons;
    unsigned hat:4;
    unsigned x:10;
    unsigned y:10;
    unsigned rx:10;
    unsigned ry:10;
    unsigned trigger_left:10;
    unsigned trigger_right:10;
};

#endif