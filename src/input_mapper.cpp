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

        pos_x = (62.5 - 20.636) * ppmX;
        pos_y = 20.636 * ppmY;

        tdpad_left.init(pos_x, pos_y, pos_r, TouchDpad::DPAD_TYPE_SECTOR4);
        tdpad_left.setDeadZoneInner(dead_zone_inner);

        device.begin();
    }

    uint16_t dpad_map[][4] =
    {
        {
            USB_Device::DPAD_UP,
            USB_Device::DPAD_DOWN,
            USB_Device::DPAD_LEFT,
            USB_Device::DPAD_RIGHT,
        },
        {
            USB_Device::FACE_Y,
            USB_Device::FACE_A,
            USB_Device::FACE_X,
            USB_Device::FACE_B,
        },
    };
    
    uint16_t mapDpad(uint8_t dpad, uint8_t direction)
    {
        uint16_t button = 0;

        for (uint8_t i = 0; i < 4; ++i)
        {
            if (direction & (1 << i))
            {
                button |= dpad_map[dpad][i];
            }
        }

        return button;
    }

    void mapTrackpad(uint8_t id, uint8_t fid, int32_t x, int32_t y)
    {
        for (uint8_t c = 0; c < num_controls; ++c)
        {
            int res;

            switch(tcontrols[id][c]->getControlType())
            {
                case TouchControl::CT_NONE:
                    break;

                case TouchControl::CT_JOYSTICK:
                    res = tcontrols[id][c]->touch(fid, x, y);
                    device.joystick(id, ((TouchJoystick*)tcontrols[id][c])->getX(), ((TouchJoystick*)tcontrols[id][c])->getY());
                    break;
                
                case TouchControl::CT_DPAD:
                    {
                        uint16_t prev_button = mapDpad(id, ((TouchDpad*)tcontrols[id][c])->getButton());
                        device.button(prev_button, 0);

                        res = tcontrols[id][c]->touch(fid, x, y);

                        uint16_t button = mapDpad(id, ((TouchDpad*)tcontrols[id][c])->getButton());
                        device.button(button, button);
                    }
                    break;
            }

            // if control is touched return
            if (res > 0)
            {
                return;
            }
        }
    }

    void mapTriggers(uint32_t value[2])
    {
        static const uint32_t max = 70;
        static const uint32_t min = 2;

        uint8_t mapped_value[2];
 
        for (uint8_t i = 0; i < 2; ++i)
        {
             if (value[i] < min)
             {
                 mapped_value[i] = 0;
             }
             else if (value[i] > max)
             {
                 mapped_value[i] = 255;
             }
             else
             {
                 mapped_value[i] = (value[i] - min) * 255 / (max - min);
             }
        }

        device.triggers(mapped_value);
    }

    uint16_t button_map[] =
    {
        USB_Device::START,
        USB_Device::SELECT,
        USB_Device::JOYSTICK_LEFT,
        USB_Device::JOYSTICK_RIGHT,
        USB_Device::BUMPER_LEFT,
        USB_Device::BUMPER_RIGHT,
        USB_Device::HOME,
        USB_Device::FACE_A,
        USB_Device::FACE_B,
        USB_Device::FACE_X,
        USB_Device::FACE_Y,
    };

    void mapButton(HardwareButtons button, bool value)
    {
        device.button(button_map[button], value? button_map[button] : 0);
    }

    void sendReport()
    {
        device.sendReport();
    }
}