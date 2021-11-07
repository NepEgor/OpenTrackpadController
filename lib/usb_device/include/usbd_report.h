#ifndef USBD_REPORT_H
#define USBD_REPORT_H

#include <stdint.h>

#define HID_JOYSTICK_REPORT_DESC_SIZE 104U

// USB Joystick Report Descriptor
extern uint8_t USBD_HID_Joystick_ReportDesc[HID_JOYSTICK_REPORT_DESC_SIZE];

struct __attribute__((packed)) USBD_HID_Joystick_Report
{
    uint8_t  reportID = 20;
    uint32_t buttons;
    unsigned hat:4;
    unsigned trigger_left:10;
    unsigned trigger_right:10;
    unsigned x:10;
    unsigned y:10;
    unsigned rx:10;
    unsigned ry:10;
};
/*
struct __attribute__((packed)) USBD_HID_Joystick_Report
{
    unsigned header:16;
    unsigned buttons:16;
    //unsigned hat:4;
    unsigned trigger_left:8;
    unsigned trigger_right:8;
    unsigned x:16;
    unsigned y:16;
    unsigned rx:16;
    unsigned ry:16;
};
*/

#endif