#include "input_mapper.h"

#include "usb_device.h"
#include "touch_controls_all.h"

#include <map>

namespace InputMapper
{
    USB_Device device;

    TouchMouseJoustick tjoystick_right;
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
    /*
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
    */
    // Genshin map
    uint16_t button_map[] =
    {
        USB_Device::START,
        USB_Device::SELECT,
        USB_Device::FACE_B,
        USB_Device::FACE_X,
        USB_Device::BUMPER_LEFT,
        USB_Device::BUMPER_RIGHT,
        USB_Device::HOME,
        USB_Device::FACE_A,
        USB_Device::JOYSTICK_RIGHT,
        USB_Device::FACE_A,
        USB_Device::JOYSTICK_LEFT,
    };

    uint16_t dpad_left_map[] = 
    {
        USB_Device::DPAD_UP,
        USB_Device::DPAD_DOWN,
        USB_Device::DPAD_LEFT,
        USB_Device::DPAD_RIGHT,
    };

    uint16_t dpad_right_map[] = 
    {
        USB_Device::FACE_Y,
        USB_Device::FACE_A,
        USB_Device::FACE_X,
        USB_Device::FACE_B,
    };

    uint16_t* dpad_map[] =
    {
        dpad_left_map,
        dpad_right_map,
    };
    
    std::map<uint16_t, uint8_t> xinput_counter;

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
        tjoystick_left.setMappedId(0);

        pos_x = 31.25 * ppmX;
        pos_y = (103.9 - 31.25) * ppmY;
        dead_zone_outer = 10 * ppmX;

        tjoystick_right.init(pos_x, pos_y, pos_r, USB_Device::usb_joystick_x, USB_Device::usb_joystick_y, USB_Device::usb_joystick_r);
        //tjoystick_right.setDeadZoneInner(dead_zone_inner);
        tjoystick_right.setTrackballFriction(1.f / 4000000.f);
        //tjoystick_right.setTrackballFriction(0);
        tjoystick_right.setDeadZoneOuter(dead_zone_outer);
        tjoystick_right.setSensitivity(10);
        tjoystick_right.setMappedId(1);

        pos_x = 20.636 * ppmX;
        pos_y = 20.636 * ppmY;
        pos_r = 45 * ppmX / 2;
        tdpad_right.init(pos_x, pos_y, pos_r, TouchDpad::DPAD_TYPE_SECTOR_4);
        tdpad_right.setDeadZoneInner(dead_zone_inner);

        pos_x = (62.5 - 20.636) * ppmX;
        pos_y = 20.636 * ppmY;

        tdpad_left.init(pos_x, pos_y, pos_r, TouchDpad::DPAD_TYPE_SECTOR_4);
        tdpad_left.setDeadZoneInner(dead_zone_inner);

        for (uint8_t i = 0; i < sizeof(button_map) / sizeof(uint16_t); ++i)
        {
            auto search = xinput_counter.find(button_map[i]);
            if (search == xinput_counter.end())
            {
                xinput_counter.insert(std::make_pair(button_map[i], 0));
            }
        }

        for (uint8_t d = 0; d < 2; ++d)
        {
            for (uint8_t i = 0; i < 4; ++i)
            {
                auto search = xinput_counter.find(dpad_map[d][i]);
                if (search == xinput_counter.end())
                {
                    xinput_counter.insert(std::make_pair(dpad_map[d][i], 0));
                }
            }
        }

        device.begin();
    }

    void modifyCounter(uint16_t xinput_button, bool value)
    {
        auto search = xinput_counter.find(xinput_button);

        if (search != xinput_counter.end())
        {
            if (value)
            {
                search->second++;
            }
            else
            {
                if (search->second > 0)
                {
                    search->second--;
                }
            }
        }
    }

    void mapDpad(uint8_t dpad, uint8_t direction, bool value)
    {
        for (uint8_t i = 0; i < 4; ++i)
        {
            if (direction & (1 << i))
            {
                modifyCounter(dpad_map[dpad][i], value);
            }
        }
    }

    void mapTrackpad(uint8_t id, uint8_t fid, int32_t x, int32_t y, int32_t dx, int32_t dy, uint32_t time)
    {
        for (uint8_t c = 0; c < num_controls; ++c)
        {
            int res = 0;

            switch(tcontrols[id][c]->getControlType())
            {
                case TouchControl::CT_NONE:
                    break;

                case TouchControl::CT_JOYSTICK:
                    {
                        TouchJoystick* tjoy = (TouchJoystick*)tcontrols[id][c];

                        res = tjoy->touch(fid, x, y);

                        device.joystick(tjoy->getMappedId(), tjoy->getX(), tjoy->getY());
                    }
                    break;
                
                case TouchControl::CT_MOUSE_JOYSTICK:
                    {
                        TouchMouseJoustick* tmjoy = (TouchMouseJoustick*)tcontrols[id][c];

                        res = tmjoy->touch(fid, x, y, dx, dy, time);

                        device.joystick(tmjoy->getMappedId(), tmjoy->getX(), tmjoy->getY());
                    }
                    break;

                case TouchControl::CT_DPAD:
                    {
                        TouchDpad* dpad = (TouchDpad*)tcontrols[id][c];

                        mapDpad(id, dpad->getButton(), 0);

                        res = dpad->touch(fid, x, y);

                        mapDpad(id, dpad->getButton(), 1);
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

    void update(uint32_t time)
    {
        for (uint8_t id = 0; id < 2; ++id)
        {
            for (uint8_t c = 0; c < num_controls; ++c)
            {
                int res = 0;

                switch(tcontrols[id][c]->getControlType())
                {
                    case TouchControl::CT_MOUSE_JOYSTICK:
                        {
                            TouchMouseJoustick* tmjoy = (TouchMouseJoustick*)tcontrols[id][c];

                            tmjoy->updateTrackball(time);

                            device.joystick(tmjoy->getMappedId(), tmjoy->getX(), tmjoy->getY());
                        }
                        break;

                    default:
                        break;
                }

            }
        }
    }

    void mapTriggers(uint32_t value[2])
    {
        static const uint32_t max = 70;
        static const uint32_t min = 13;

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

    void mapButton(HardwareButtons button, bool value)
    {
        modifyCounter(button_map[button], value);
    }

    void sendReport()
    {   
        for (auto it = xinput_counter.begin(); it != xinput_counter.end(); ++it)
        {
            device.button(it->first, it->second > 0? it->first : 0);
        }

        device.sendReport();
    }
}