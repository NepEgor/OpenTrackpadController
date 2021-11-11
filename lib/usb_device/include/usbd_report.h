#ifndef USBD_REPORT_H
#define USBD_REPORT_H

#include <stdint.h>

#define HID_JOYSTICK_REPORT_DESC_SIZE 104U

// USB Joystick Report Descriptor
//extern uint8_t USBD_HID_Joystick_ReportDesc[HID_JOYSTICK_REPORT_DESC_SIZE];
/*
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
*/
struct __attribute__((packed)) USBD_HID_Joystick_Report
{
    uint8_t  msg_type:8;        // byte 0
    uint8_t  msg_len:8;         // byte 1

    uint16_t buttons:16;        // bytes 2 and 3
    uint8_t  trigger_left:8;    // byte 4
    uint8_t  trigger_right:8;   // byte 5
    int16_t  x:16;              // byte 6
    int16_t  y:16;              // byte 7
    int16_t  rx:16;             // byte 8
    int16_t  ry:16;             // byte 9
    
    //uint32_t unused0:32;
    //uint16_t unused1:16;
};

#endif