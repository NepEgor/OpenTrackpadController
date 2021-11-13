#include <Arduino.h>

#include "trackpad.h"
#include "input_mapper.h"

const uint8_t pin_trigger[2] = {0, PA3};

const uint8_t pin_trackpad_click[2] = {0, PB4};

const uint8_t pin_trackpad_data[2]  = {PB7, PB9};
const uint8_t pin_trackpad_clock[2] = {PB6, PB8};

TrackPad trackpad[2]; // 0 - left, 1 - right

void int_touchpad_0(){trackpad[0].int_on_clock();}
void int_touchpad_1(){trackpad[1].int_on_clock();}

void setup()
{
    // Turn on LED
    pinMode(PC13, OUTPUT);
    digitalWrite(PC13, LOW);

    Serial.begin(256000);

    // Init Hardware
    pinMode(pin_trigger[1], INPUT_ANALOG);
    pinMode(pin_trackpad_click[1], INPUT_PULLDOWN);
    
    //attachInterrupt(pin_trackpad_clock[0], int_touchpad_0, FALLING);
    //trackpad[0].initialize(pin_trackpad_clock[0], pin_trackpad_data[0]);

    attachInterrupt(pin_trackpad_clock[1], int_touchpad_1, FALLING);
    trackpad[1].initialize(pin_trackpad_clock[1], pin_trackpad_data[1]);


    
    InputMapper::begin();

    // Turn off LED
    digitalWrite(PC13, HIGH);
}

uint8_t tevent_size;
TouchEvent tevent[5];

void loop()
{
    if (trackpad[1].poll(tevent, tevent_size) > 0)
    {
        for (uint8_t i = 0; i < tevent_size; ++i)
        {
            int32_t x = -1;
            int32_t y = -1;
            switch (tevent[i].type)
            {
                case TET_DOWN:
                case TET_MOVE:

                    x = tevent[i].fp.x;
                    y = tevent[i].fp.y;

                    break;
                
                case TET_UP:

                    break;

                default:
                    break;
            }

            InputMapper::mapTrackpad(1, tevent[i].finger_id, y, x); // trackpad is rotated 90 deg so x and y are flipped
        }
    }

    uint32_t triggers[] = {0, analogRead(pin_trigger[1])};
    InputMapper::mapTriggers(triggers);

    uint16_t right_tp_click = digitalRead(pin_trackpad_click[1]);
    InputMapper::mapButtons(right_tp_click << 7); // R3

    InputMapper::sendReport();
}
