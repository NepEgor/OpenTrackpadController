#include <Arduino.h>

//#include "usbd_hid_custom_if.h"

#include "usbd_device.h"
USBD_Device device;

#include "trackpad.h"
TrackPad trackpad_right(0);
TrackPad trackpad_left(1);

void int_touchpad_right(){trackpad_right.int_on_clock();}
void int_touchpad_left(){trackpad_left.int_on_clock();}

const uint8_t TRIGGER_RIGHT_PIN = PA3;
const uint8_t TRACKPAD_CLICK_RIGHT_PIN = PB4;
const uint8_t DATA_PIN_right  = PB9;
const uint8_t CLOCK_PIN_right = PB8;
const uint8_t DATA_PIN_left  = PB7;
const uint8_t CLOCK_PIN_left = PB6;

#include "touch_controls_all.h"
TouchJoystick tjoystick_right;
TouchJoystick tjoystick_left;
TouchDpad tdpad_right;
TouchDpad tdpad_left;

const int16_t usb_x = 512;
const int16_t usb_y = 512;
const int16_t usb_r = 512;

/*
typedef struct
{
    int16_t x:16;
    int16_t y:16;
    int16_t r:16;
} __packed TestReport_t;

TestReport_t testReport;
*/
void setup()
{
    // Turn on LED
    pinMode(PC13, OUTPUT);
    digitalWrite(PC13, LOW);

    Serial.begin(256000);

    pinMode(TRIGGER_RIGHT_PIN, INPUT_ANALOG);
    pinMode(TRACKPAD_CLICK_RIGHT_PIN, INPUT_PULLDOWN);

    attachInterrupt(CLOCK_PIN_right, int_touchpad_right, FALLING);
    trackpad_right.initialize(CLOCK_PIN_right, DATA_PIN_right);

    attachInterrupt(CLOCK_PIN_left, int_touchpad_left, FALLING);
    trackpad_left.initialize(CLOCK_PIN_left, DATA_PIN_left);

    /*
    float ppmX = trackpad_right.getMaxY() / 62.5;
    float ppmY = trackpad_right.getMaxX() / 103.9;
    int32_t pos_x = 31.25 * ppmX;
    int32_t pos_y = (103.9 - 31.25) * ppmY;
    int32_t pos_r = 70 * ppmX / 2;
    int32_t dead_zone_inner = 3 * ppmX;
    int32_t dead_zone_outer = 13 * ppmX;
    tjoystick.init(pos_x, pos_y, pos_r, usb_x, usb_y, usb_r);

    tjoystick.setDeadZoneInner(dead_zone_inner);
    tjoystick.setDeadZoneOuter(dead_zone_outer);
    tjoystick.setInvertY(true);

    testReport = { 0, 0, 0 };

    HID_Custom_Init();
    */

    device.begin();

    // Turn off LED
    digitalWrite(PC13, HIGH);
}

void loop()
{
    /*
    uint32_t right_trigger = analogRead(TRIGGER_RIGHT_PIN);
    uint8_t right_tp_click = digitalRead(TRACKPAD_CLICK_RIGHT_PIN);

    //Serial.printf("RT: %u RTPC: %u\n", right_trigger, right_tp_click);
    
    testReport.r = (int16_t)(right_trigger % 1024);

    FingerPosition* fp;
    int8_t fingers_touching = trackpad_right.poll(&fp);
    
    if (fingers_touching > 0)
    {
        if (fp != NULL)
        {
            int16_t x, y;
            
            for (int8_t id = 0; id < TrackPad::fingers_num; ++id)
            {
                if (fingers_touching & (1 << id))
                {
                    if (tjoystick.touch(fp[id].y, fp[id].x, &x, &y))
                    {
                        break;
                    }
                }
            }
            
            testReport.x = x;
            testReport.y = y;
        }
    }
    else
    if (fingers_touching == 0)
    {
        testReport.x = usb_x;
        testReport.y = usb_y;
    }

    //Serial.printf("%u %u %u\n", testReport.x, testReport.y, testReport.r);

    //device.move(testReport.x, testReport.y);

    HID_Custom_sendReport((uint8_t*)(&testReport), sizeof(testReport));
    */
    //delay(100);
}
