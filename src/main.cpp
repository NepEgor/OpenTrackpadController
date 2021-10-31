#include <Arduino.h>

//#include "usbd_hid_custom_if.h"

#include "usb_device.h"
USB_Device device;

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

    //attachInterrupt(CLOCK_PIN_left, int_touchpad_left, FALLING);
    //trackpad_left.initialize(CLOCK_PIN_left, DATA_PIN_left);
    
    
    float ppmX = trackpad_right.getMaxY() / 62.5;
    float ppmY = trackpad_right.getMaxX() / 103.9;
    int32_t pos_x = 31.25 * ppmX;
    int32_t pos_y = (103.9 - 31.25) * ppmY;
    int32_t pos_r = 70 * ppmX / 2;
    int32_t dead_zone_inner = 3 * ppmX;
    int32_t dead_zone_outer = 13 * ppmX;

    tjoystick_right.init(pos_x, pos_y, pos_r, USB_Device::usb_joystick_x, USB_Device::usb_joystick_y, USB_Device::usb_joystick_r);
    tjoystick_right.setDeadZoneInner(dead_zone_inner);
    tjoystick_right.setDeadZoneOuter(dead_zone_outer);
    tjoystick_right.setInvertX();
    tjoystick_right.setInvertY();

    //tjoystick_left.init(pos_x, pos_y, pos_r, USB_Device::usb_joystick_x, USB_Device::usb_joystick_y, USB_Device::usb_joystick_r);
    //tjoystick_left.setDeadZoneInner(dead_zone_inner);
    //tjoystick_left.setDeadZoneOuter(dead_zone_outer);

    device.begin();

    // Turn off LED
    digitalWrite(PC13, HIGH);
}

void loop()
{
    uint32_t right_trigger = analogRead(TRIGGER_RIGHT_PIN);
    uint8_t right_tp_click = digitalRead(TRACKPAD_CLICK_RIGHT_PIN);

    FingerPosition* fp;
    int8_t fingers_touching = trackpad_right.poll(&fp);
    if (fingers_touching > 0)
    {
        if (fp != NULL)
        {
            for (uint8_t id = 0; id < TrackPad::fingers_num; ++id)
            {
                if (fingers_touching & (1 << id))
                {
                    int8_t res = tjoystick_right.touch(fp[id].y, fp[id].x);
                    if (res > 0)
                    {
                        switch(tjoystick_right.getControlType())
                        {
                            case TouchControl::CT_NONE:
                                
                                break;

                            case TouchControl::CT_JOYSTICK:

                                int16_t x = tjoystick_right.getX();
                                int16_t y = tjoystick_right.getY();
                                device.joystick_left(x, y);

                                Serial.printf("(%i, %i) (%i, %i)\n", fp[id].x, fp[id].y, x, y);

                                break;
                        }
                    }
                    else
                    if (res < 0)
                    {
                        Serial.printf("Impossible Error\n");
                    }
                    else
                    {
                        device.joystick_left(USB_Device::usb_joystick_x, USB_Device::usb_joystick_y);
                    }
                }
            }
            
        }
    }
    else
    if (fingers_touching == 0)
    {
        device.joystick_left(USB_Device::usb_joystick_x, USB_Device::usb_joystick_y);
    }

    device.trigger_right(right_trigger);
    device.button(0, right_tp_click);

    device.sendReport();
}
