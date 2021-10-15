#include <Arduino.h>

#include "usbd_hid_custom_if.h"

//USBD_Device device;

const uint8_t TRIGGER_RIGHT_PIN = PA3;
const uint8_t TRACKPAD_CLICK_RIGHT_PIN = PB4;

typedef struct
{
    uint16_t x:16;
    uint16_t y:16;
    uint16_t r:16;
} __packed PedalsReport_t;

PedalsReport_t PedalsReport;

void setup()
{
    Serial.begin(256000);

    pinMode(TRIGGER_RIGHT_PIN, INPUT_ANALOG);
    pinMode(TRACKPAD_CLICK_RIGHT_PIN, INPUT_PULLDOWN);

    //device.begin();

    printf("HID Init\n");

    HID_Custom_Init();

    printf("HID Init success\n");

    PedalsReport = { 0, 1024/3, 2048/3 };
}

void loop()
{

    uint32_t right_trigger = analogRead(TRIGGER_RIGHT_PIN);
    uint8_t right_tp_click = digitalRead(TRACKPAD_CLICK_RIGHT_PIN);

    //Serial.printf("RT: %u RTPC: %u\n", right_trigger, right_tp_click);
    
    PedalsReport.x = (PedalsReport.x + 10) % 1024;
    PedalsReport.y = (PedalsReport.y + 20) % 1024;
    PedalsReport.r = (PedalsReport.r + 30) % 1024;

    //Serial.printf("%u %u %u\n", PedalsReport.x, PedalsReport.y, PedalsReport.r);

    //device.move(PedalsReport.x, PedalsReport.y);

    HID_Custom_sendReport((uint8_t*)(&PedalsReport), 6);

    delay(100);
}
