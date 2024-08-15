#include <Arduino.h>

#include "trackpad.h"
#include "input_mapper.h"

const uint8_t pin_trigger[2] = {PA1, PA0};

const uint8_t pin_button[]  =
{
    PB12, 0, // START
    PB13, 0, // SELECT
    PB5,  0, // BUMPER_LEFT
    PA8,  0, // BUMPER_RIGHT
    PB1,  0, // HOME
    PB14, 0, // GRIP_A
    PB15, 0, // GRIP_B
    PA4,  0, // GRIP_X
    PB4,  0, // GRIP_Y
    PC15, 0, // TRACKPAD_LEFT
    PB3,  0, // TRACKPAD_RIGHT
};

uint8_t button_state[sizeof(pin_button) / 2] = {0};

const uint8_t gyro_int = PC14;

#ifndef DISABLE_TRACKPADS

const uint8_t pin_trackpad_data[2]  = {PA2, PB9}; // elan 33200v-3600 pad T8
const uint8_t pin_trackpad_clock[2] = {PA3, PB8}; // elan 33200v-3600 pad T7

TrackPad trackpad[2]; // 0 - left, 1 - right

int32_t trackpad_maxX, trackpad_maxY;

#endif

void setup()
{
    // Turn on LED
    pinMode(PC13, OUTPUT);
    digitalWrite(PC13, LOW);

    Serial.begin(115200);

    // Init Hardware
    for (uint8_t i = 0; i < sizeof(pin_trigger); ++i)
    {
        pinMode(pin_trigger[i], INPUT_ANALOG);
    }

    for (uint8_t i = 0; i < sizeof(pin_button); i += 2)
    {
        pinMode(pin_button[i], pin_button[i + 1]? INPUT_PULLDOWN : INPUT_PULLUP);
    }
    
    #ifndef DISABLE_TRACKPADS

    for (uint8_t i = 0; i < sizeof(pin_trackpad_clock); ++i)
    {
        trackpad[i].initialize(pin_trackpad_clock[i], pin_trackpad_data[i]);
    }

    trackpad_maxX = trackpad[0].getMaxX();
    trackpad_maxY = trackpad[0].getMaxY();

    #endif

    InputMapper::begin();

    // Turn off LED
    digitalWrite(PC13, HIGH);
}

uint8_t tevent_size;
TouchEvent tevent[5];

void loop()
{
    #ifndef DISABLE_TRACKPADS

    for (uint8_t t = 0; t < 2; ++t)
    {
        if (trackpad[t].poll(tevent, tevent_size) > 0)
        {
            for (uint8_t i = 0; i < tevent_size; ++i)
            {
                int32_t x = -1;
                int32_t y = -1;
                int32_t dx = 0;
                int32_t dy = 0;
                switch (tevent[i].type)
                {
                    case TET_DOWN:
                    case TET_MOVE:

                         // trackpad is rotated 90 deg so x and y are switched
                        x = tevent[i].fp.y;
                        y = tevent[i].fp.x;
                        dx = tevent[i].fp.dy;
                        dy = tevent[i].fp.dx;
                        
                        // invert axis for the trackpads
                        if(t == 0)
                        {
                            y = trackpad_maxX - y;
                            dy = -dy;
                        }
                        else
                        {
                            x = trackpad_maxY - x;
                            dx = -dx;
                        }

                        break;
                    
                    case TET_UP:

                        break;

                    default:
                        break;
                }
                
                InputMapper::mapTrackpad(t, tevent[i].finger_id, x, y, dx, dy, micros());
            }
        }
    }

    #endif

    uint32_t triggers[] = {analogRead(pin_trigger[0]), analogRead(pin_trigger[1])};

    //Serial.print(0);
    //Serial.print('\t');
    //Serial.print(triggers[0]);
    //Serial.print('\t');
    //Serial.print(triggers[1]);
    //Serial.print('\t'); 
    //Serial.println(1000);

    InputMapper::mapTriggers(triggers);

    for (uint8_t i = 0; i < sizeof(pin_button); i += 2)
    {
        uint8_t value = digitalRead(pin_button[i]);
        if (value != button_state[i / 2])
        {
            if (InputMapper::mapButton((InputMapper::HardwareButtons)(i / 2), value == pin_button[i + 1]))
            {
                button_state[i / 2] = value;
            }
        }
    }

    InputMapper::update(micros());

    InputMapper::sendReport();
}
