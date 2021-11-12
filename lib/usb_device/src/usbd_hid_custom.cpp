#include "usbd_hid_custom.h"
#include "usbd_ctlreq.h"

#include "usbd_descriptors.h"
#include "usbd_report.h"

static uint8_t USBD_HID_Init(USBD_HandleTypeDef* pdev, uint8_t cfgidx);
static uint8_t USBD_HID_DeInit(USBD_HandleTypeDef* pdev, uint8_t cfgidx);

static uint8_t USBD_CUSTOM_HID_Setup(USBD_HandleTypeDef* pdev, USBD_SetupReqTypedef* req);
static uint8_t USBD_HID_XINPUT_EP81_Setup(USBD_HandleTypeDef* pdev, USBD_SetupReqTypedef* req);

static uint8_t* USBD_HID_GetFSCfgDesc(uint16_t* length);

static uint8_t USBD_HID_DataIn(USBD_HandleTypeDef* pdev, uint8_t epnum);

USBD_ClassTypeDef USBD_CUSTOM_HID = {
    USBD_HID_Init,
    USBD_HID_DeInit,
    USBD_CUSTOM_HID_Setup,
    NULL,            //EP0_TxSent
    NULL,            //EP0_RxReady
    USBD_HID_DataIn, //DataIn
    NULL,            //DataOut
    NULL,            //SOF
    NULL,
    NULL,
    NULL,//USBD_HID_GetHSCfgDesc,
    USBD_HID_GetFSCfgDesc,
    NULL,//USBD_HID_GetOtherSpeedCfgDesc,
    NULL,//USBD_HID_GetDeviceQualifierDesc,
};

static uint8_t USBD_HID_Init(USBD_HandleTypeDef* pdev, uint8_t cfgidx)
{
    UNUSED(cfgidx);
    uint8_t ret = USBD_OK;

    // Open EP IN
    USBD_LL_OpenEP(pdev, HID_CUSTOM_EPIN_ADDR, USBD_EP_TYPE_INTR, HID_CUSTOM_EPIN_SIZE);
    pdev->ep_in[HID_CUSTOM_EPIN_ADDR & 0xFU].is_used = 1U;

    // TODO open all end points for all interfaces

    /*
    // Open EP IN
    USBD_LL_OpenEP(pdev,
                    HID_KEYBOARD_EPIN_ADDR,
                    USBD_EP_TYPE_INTR,
                    HID_KEYBOARD_EPIN_SIZE);
    pdev->ep_in[HID_KEYBOARD_EPIN_ADDR & 0xFU].is_used = 1U;
    */
    pdev->pClassData = USBD_malloc(sizeof(USBD_HID_HandleTypeDef));

    if (pdev->pClassData == NULL)
    {
        ret = USBD_FAIL;
    }
    else
    {
        ((USBD_HID_HandleTypeDef*)pdev->pClassData)->Mousestate = HID_IDLE;
        //((USBD_HID_HandleTypeDef *)pdev->pClassData)->Keyboardstate = HID_IDLE;
    }

    return ret;
}

static uint8_t USBD_HID_DeInit(USBD_HandleTypeDef* pdev, uint8_t cfgidx)
{
    UNUSED(cfgidx);
    /* Close HID EPs */
    USBD_LL_CloseEP(pdev, HID_CUSTOM_EPIN_ADDR);
    pdev->ep_in[HID_CUSTOM_EPIN_ADDR & 0xFU].is_used = 0U;
    /*
    USBD_LL_CloseEP(pdev, HID_KEYBOARD_EPIN_ADDR);
    pdev->ep_in[HID_KEYBOARD_EPIN_ADDR & 0xFU].is_used = 0U;
    */
    /* Free allocated memory */
    if (pdev->pClassData != NULL)
    {
        USBD_free(pdev->pClassData);
        pdev->pClassData = NULL;
    }

    return USBD_OK;
}

#include <Arduino.h>

static uint8_t USBD_CUSTOM_HID_Setup(USBD_HandleTypeDef* pdev, USBD_SetupReqTypedef* req)
{
    Serial.printf("usb req %02X %02X %02X\n", req->wIndex, req->bRequest, req->wValue);
    /* Check which interface is targetted by this request */
    //if ((req->wIndex & 0x00FF) == HID_KEYBOARD_INTERFACE)
    //{
    //    return USBD_HID_KEYBOARD_Setup(pdev, req);
    //}
    //else
    //{
    return USBD_HID_XINPUT_EP81_Setup(pdev, req);
    //}
}

static uint8_t USBD_HID_XINPUT_EP81_Setup(USBD_HandleTypeDef* pdev, USBD_SetupReqTypedef* req)
{
    USBD_HID_HandleTypeDef* hhid = (USBD_HID_HandleTypeDef*)pdev->pClassData;
    uint16_t len = 0U;
    uint8_t* pbuf = NULL;
    uint16_t status_info = 0U;
    USBD_StatusTypeDef ret = USBD_OK;

    switch (req->bmRequest & USB_REQ_TYPE_MASK)
    {
        case USB_REQ_TYPE_CLASS:
            switch (req->bRequest)
            {
                case HID_REQ_SET_PROTOCOL:
                    hhid->Protocol = (uint8_t)(req->wValue);
                    break;

                case HID_REQ_GET_PROTOCOL:
                    USBD_CtlSendData(pdev, (uint8_t*)&hhid->Protocol, 1U);
                    break;

                case HID_REQ_SET_IDLE:
                    hhid->IdleState = (uint8_t)(req->wValue >> 8);
                    break;

                case HID_REQ_GET_IDLE:
                    USBD_CtlSendData(pdev, (uint8_t*)&hhid->IdleState, 1U);
                    break;

                default:
                    USBD_CtlError(pdev, req);
                    ret = USBD_FAIL;
                    break;
            }
            break;

        case USB_REQ_TYPE_STANDARD:
            switch (req->bRequest)
            {
                case USB_REQ_GET_STATUS:
                    if (pdev->dev_state == USBD_STATE_CONFIGURED)
                    {
                        USBD_CtlSendData(pdev, (uint8_t*)(void*)&status_info, 2U);
                    }
                    else
                    {
                        USBD_CtlError(pdev, req);
                        ret = USBD_FAIL;
                    }
                    break;
                /*
                case USB_REQ_GET_DESCRIPTOR:
                    if (req->wValue >> 8 == HID_REPORT_DESC)
                    {
                        len = MIN(HID_JOYSTICK_REPORT_DESC_SIZE, req->wLength);
                        pbuf = USBD_HID_Joystick_ReportDesc;
                    }
                    else if (req->wValue >> 8 == HID_DESCRIPTOR_TYPE)
                    {
                        pbuf = USBD_HID_CUSTOM_Desc;
                        len = MIN(USB_HID_CUSTOM_DESC_SIZ, req->wLength);
                    }
                    else
                    {
                        USBD_CtlError(pdev, req);
                        ret = USBD_FAIL;
                        break;
                    }
                    USBD_CtlSendData(pdev, pbuf, len);
                    break;
                */
                case USB_REQ_GET_INTERFACE:
                    if (pdev->dev_state == USBD_STATE_CONFIGURED)
                    {
                        USBD_CtlSendData(pdev, (uint8_t*)&hhid->AltSetting, 1U);
                    }
                    else
                    {
                        USBD_CtlError(pdev, req);
                        ret = USBD_FAIL;
                    }
                    break;

                case USB_REQ_SET_INTERFACE:
                    if (pdev->dev_state == USBD_STATE_CONFIGURED)
                    {
                        hhid->AltSetting = (uint8_t)(req->wValue);
                    }
                    else
                    {
                        USBD_CtlError(pdev, req);
                        ret = USBD_FAIL;
                    }
                    break;

                default:
                    USBD_CtlError(pdev, req);
                    ret = USBD_FAIL;
                    break;
            }
            break;

        default:
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
            break;
    }

    return ret;
}

uint8_t USBD_HID_CUSTOM_SendReport(USBD_HandleTypeDef* pdev, uint8_t* report, uint16_t len)
{
    USBD_HID_HandleTypeDef* hhid = (USBD_HID_HandleTypeDef*)pdev->pClassData;

    if (pdev->dev_state == USBD_STATE_CONFIGURED)
    {
        if (hhid->Mousestate == HID_IDLE)
        {
            hhid->Mousestate = HID_BUSY;
            USBD_LL_Transmit(pdev, HID_CUSTOM_EPIN_ADDR, report, len);
        }
    }
    return USBD_OK;
}

uint32_t USBD_HID_GetPollingInterval(USBD_HandleTypeDef* pdev)
{
    uint32_t polling_interval = 0U;

    /* HIGH-speed endpoints */
    if (pdev->dev_speed == USBD_SPEED_HIGH)
    {
        /* Sets the data transfer polling interval for high speed transfers.
        Values between 1..16 are allowed. Values correspond to interval
        of 2 ^ (bInterval-1). This option (8 ms, corresponds to HID_HS_BINTERVAL */
        polling_interval = (((1U << (HID_HS_BINTERVAL - 1U))) / 8U);
    }
    else
    { /* LOW and FULL-speed endpoints */
        /* Sets the data transfer polling interval for low and full
        speed transfers */
        polling_interval = HID_FS_BINTERVAL;
    }

    return ((uint32_t)(polling_interval));
}

static uint8_t* USBD_HID_GetFSCfgDesc(uint16_t* length)
{
    *length = sizeof(USBD_HID_CUSTOM_CfgFSDesc);
    return USBD_HID_CUSTOM_CfgFSDesc;
}

static uint8_t USBD_HID_DataIn(USBD_HandleTypeDef* pdev, uint8_t epnum)
{
    // Ensure that the FIFO is empty before a new transfer, this condition could
    // be caused by  a new transfer before the end of the previous transfer
    //if (epnum == (HID_KEYBOARD_EPIN_ADDR & 0x7F))
    //{
    //((USBD_HID_HandleTypeDef *)pdev->pClassData)->Keyboardstate = HID_IDLE;
    //}
    //else if (epnum == (HID_CUSTOM_EPIN_ADDR & 0x7F))
    //{
    ((USBD_HID_HandleTypeDef*)pdev->pClassData)->Mousestate = HID_IDLE;
    //}
    return USBD_OK;
}
