#include <Arduino.h>

#include "trackpad.h"
#include "input_mapper.h"

const uint8_t pin_trigger[2] = {0, PA3};

const uint8_t pin_trackpad_click[2] = {0, PB4};

const uint8_t pin_trackpad_data[2]  = {PB7, PB9};
const uint8_t pin_trackpad_clock[2] = {PB6, PB8};

TrackPad trackpad[2]; // 0 - left, 1 - right

int32_t trackpad_maxX, trackpad_maxY;

void setup()
{
    // Turn on LED
    pinMode(PC13, OUTPUT);
    digitalWrite(PC13, LOW);

    Serial.begin(256000);

    // Init Hardware
    pinMode(pin_trigger[1], INPUT_ANALOG);
    pinMode(pin_trackpad_click[1], INPUT_PULLDOWN);
    
    trackpad[0].initialize(pin_trackpad_clock[0], pin_trackpad_data[0]);

    trackpad[1].initialize(pin_trackpad_clock[1], pin_trackpad_data[1]);

    trackpad_maxX = trackpad[0].getMaxX();
    trackpad_maxY = trackpad[0].getMaxY();
    
    InputMapper::begin();

    // Turn off LED
    digitalWrite(PC13, HIGH);
}

uint8_t tevent_size;
TouchEvent tevent[5];

void loop()
{
    for (uint8_t t = 0; t < 2; ++t)
    {
        if (trackpad[t].poll(tevent, tevent_size) > 0)
        {
            for (uint8_t i = 0; i < tevent_size; ++i)
            {
                int32_t x = -1;
                int32_t y = -1;
                switch (tevent[i].type)
                {
                    case TET_DOWN:
                    case TET_MOVE:

                         // trackpad is rotated 90 deg so x and y are switched
                        x = tevent[i].fp.y;
                        y = tevent[i].fp.x;
                        
                        // invert axis for the trackpads
                        if(t == 0)
                        {
                            y = trackpad_maxX - y;
                        }
                        else
                        {
                            x = trackpad_maxY - x;
                        }

                        break;
                    
                    case TET_UP:

                        break;

                    default:
                        break;
                }
                
                InputMapper::mapTrackpad(t, tevent[i].finger_id, x, y);
            }
        }
    }
    
    uint32_t triggers[] = {0, analogRead(pin_trigger[1])};
    //Serial.printf("T %u %u\n", triggers[0], triggers[1]);

    InputMapper::mapTriggers(triggers);

    uint16_t right_tp_click = digitalRead(pin_trackpad_click[1]);
    InputMapper::mapButtons(right_tp_click << (5 + 8)); // B

    InputMapper::sendReport();
    
}
