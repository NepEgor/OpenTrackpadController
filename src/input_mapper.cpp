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

    TouchControl* tcontrols[] = 
    {
        &tjoystick_right,
        &tdpad_right,
    };

    uint8_t num_controls = sizeof(tcontrols) / sizeof(TouchControl*);


    void begin()
    {
        float ppmX = 1872 / 62.5;
        float ppmY = 3276 / 103.9;
        int32_t pos_x = 31.25 * ppmX;
        int32_t pos_y = (103.9 - 31.25) * ppmY;
        int32_t pos_r = 70 * ppmX / 2;
        int32_t dead_zone_inner = 3 * ppmX;
        int32_t dead_zone_outer = 13 * ppmX;

        tjoystick_right.init(pos_x, pos_y, pos_r, USB_Device::usb_joystick_x, USB_Device::usb_joystick_y, USB_Device::usb_joystick_r);
        tjoystick_right.setDeadZoneInner(dead_zone_inner);
        tjoystick_right.setDeadZoneOuter(dead_zone_outer);
        tjoystick_right.setInvertX();
        //tjoystick_right.setInvertY();

        pos_x = (62.5 - 20.636) * ppmX;
        pos_y = 20.636 * ppmY;
        pos_r = 45 * ppmX / 2;
        tdpad_right.init(pos_x, pos_y, pos_r, TouchDpad::DPAD_TYPE_SECTOR8);
        tdpad_right.setDeadZoneInner(dead_zone_inner);
        tdpad_right.setInvertX();
        tdpad_right.setInvertY();

        //tjoystick_left.init(pos_x, pos_y, pos_r, USB_Device::usb_joystick_x, USB_Device::usb_joystick_y, USB_Device::usb_joystick_r);
        //tjoystick_left.setDeadZoneInner(dead_zone_inner);
        //tjoystick_left.setDeadZoneOuter(dead_zone_outer);

        device.begin();
    }

    void mapTrackpad(uint8_t id, uint8_t fid, int32_t x, int32_t y)
    {
        for (uint8_t c = 0; c < num_controls; ++c)
        {
            int8_t res = tcontrols[c]->touch(fid, x, y);
            if (res < 0)
            {
                break;
            }
            
            switch(tcontrols[c]->getControlType())
            {
                case TouchControl::CT_NONE:
                    break;

                case TouchControl::CT_JOYSTICK:
                    //Serial.printf("%i, %i\n", ((TouchJoystick*)tcontrols[c])->getX(), ((TouchJoystick*)tcontrols[c])->getY());
                    //device.joystick_left(((TouchJoystick*)tcontrols[c])->getX(), ((TouchJoystick*)tcontrols[c])->getY());
                    device.joystick_right(((TouchJoystick*)tcontrols[c])->getX(), ((TouchJoystick*)tcontrols[c])->getY());
                    break;
                
                case TouchControl::CT_DPAD:
                    device.dpad(((TouchDpad*)tcontrols[c])->getButton());
                    break;
            }

            if (res > 0)
            {
                break;
            }
        }
    }

    void mapTriggers(uint32_t values[2])
    {
        //device.trigger_left(values[0]);
        device.trigger_right(values[1]);
    }

    void mapButtons(uint16_t buttons)
    {
        device.buttons(buttons >> 4);
    }

    void sendReport()
    {
        device.sendReport();
    }
}