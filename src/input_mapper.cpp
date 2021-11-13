#include "input_mapper.h"

#include "usb_device.h"
#include "touch_controls_all.h"

namespace InputMapper
{
    USB_Device device;

    TouchJoystick tjoystick_right;
    TouchJoystick tjoystick_left;
    TouchDpad tdpad_right;
    TouchDpad tdpad_left;

    TouchControl* tcontrols[2][2] = 
    {
        {
            &tjoystick_left,
            &tdpad_left,
        },
        {
            &tjoystick_right,
            &tdpad_right,
        }
    };

    const uint8_t num_controls = sizeof(tcontrols) / sizeof(TouchControl*[2]);


    void begin()
    {
        float ppmX = 1872 / 62.5;
        float ppmY = 3276 / 103.9;
        int32_t pos_x = 31.25 * ppmX;
        int32_t pos_y = (103.9 - 31.25) * ppmY;
        int32_t pos_r = 70 * ppmX / 2;
        int32_t dead_zone_inner = 3 * ppmX;
        int32_t dead_zone_outer = 20 * ppmX;

        tjoystick_left.init(pos_x, pos_y, pos_r, USB_Device::usb_joystick_x, USB_Device::usb_joystick_y, USB_Device::usb_joystick_r);
        tjoystick_left.setDeadZoneInner(dead_zone_inner);
        tjoystick_left.setDeadZoneOuter(dead_zone_outer);

        pos_x = 31.25 * ppmX;
        pos_y = (103.9 - 31.25) * ppmY;

        tjoystick_right.init(pos_x, pos_y, pos_r, USB_Device::usb_joystick_x, USB_Device::usb_joystick_y, USB_Device::usb_joystick_r);
        tjoystick_right.setDeadZoneInner(dead_zone_inner);
        tjoystick_right.setDeadZoneOuter(dead_zone_outer);

        pos_x = 20.636 * ppmX;
        pos_y = 20.636 * ppmY;
        pos_r = 45 * ppmX / 2;
        tdpad_right.init(pos_x, pos_y, pos_r, TouchDpad::DPAD_TYPE_SECTOR4);
        tdpad_right.setDeadZoneInner(dead_zone_inner);

        device.begin();
    }

    void mapTrackpad(uint8_t id, uint8_t fid, int32_t x, int32_t y)
    {
        for (uint8_t c = 0; c < num_controls; ++c)
        {
            int8_t res = tcontrols[id][c]->touch(fid, x, y);
            
            switch(tcontrols[id][c]->getControlType())
            {
                case TouchControl::CT_NONE:
                    break;

                case TouchControl::CT_JOYSTICK:
                    //Serial.printf("%i, %i\n", ((TouchJoystick*)tcontrols[c])->getX(), ((TouchJoystick*)tcontrols[c])->getY());
                    //device.joystick_left(((TouchJoystick*)tcontrols[c])->getX(), ((TouchJoystick*)tcontrols[c])->getY());
                    device.joystick(id, ((TouchJoystick*)tcontrols[id][c])->getX(), ((TouchJoystick*)tcontrols[id][c])->getY());
                    break;
                
                case TouchControl::CT_DPAD:
                    device.dpad(((TouchDpad*)tcontrols[id][c])->getButton());
                    break;
            }

            // if control is touched return
            if (res > 0)
            {
                return;
            }
        }
    }

    void mapTriggers(uint32_t values[2])
    {
        uint8_t mapped_values[2];

        mapped_values[0] = 0;

        // 160 - 540
        if (values[1] < 160)
        {
            mapped_values[1] = 0;
        }
        else if(values[1] >= 540)
        {
            mapped_values[1] = 0xFF;
        }
        else
        {
            mapped_values[1] = (values[1] - 160) * 0xFF / (540 - 160);
        }

        device.triggers(mapped_values);
    }

    void mapButtons(uint16_t buttons)
    {
        uint16_t mappedButtons = buttons >> 4;

        device.buttons(mappedButtons);
    }

    void sendReport()
    {
        device.sendReport();
    }
}