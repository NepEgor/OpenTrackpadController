#ifndef __USBD_HID_CUSTOM_IF_H
#define __USBD_HID_CUSTOM_IF_H

void HID_Custom_Init();
void HID_Custom_DeInit();

void HID_Custom_sendReport(uint8_t* report, uint16_t len);

#endif
