#ifndef __USB_HID_CUSTOM_H
#define __USB_HID_CUSTOM_H

#include "usbd_ioreq.h"
#include "usbd_ep_conf.h"

#define HID_REPORT_DESC               0x22

#define HID_REQ_SET_PROTOCOL          0x0BU
#define HID_REQ_GET_PROTOCOL          0x03U

#define HID_REQ_SET_IDLE              0x0AU
#define HID_REQ_GET_IDLE              0x02U

#define HID_REQ_SET_REPORT            0x09U
#define HID_REQ_GET_REPORT            0x01U

typedef enum
{
    HID_IDLE = 0,
    HID_BUSY,
}
HID_StateTypeDef;

typedef struct
{
    uint32_t         Protocol;
    uint32_t         IdleState;
    uint32_t         AltSetting;
    HID_StateTypeDef Mousestate;
}
USBD_HID_HandleTypeDef;

extern USBD_ClassTypeDef USBD_CUSTOM_HID;
#define USBD_CUSTOM_HID_CLASS &USBD_CUSTOM_HID

uint8_t USBD_HID_CUSTOM_SendReport(USBD_HandleTypeDef *pdev, uint8_t *report, uint16_t len);

uint32_t USBD_HID_GetPollingInterval(USBD_HandleTypeDef *pdev);

#endif
