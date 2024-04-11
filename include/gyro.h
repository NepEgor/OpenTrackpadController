#ifndef GYRO_H
#define GYRO_H

#include <stdint.h>

#include <MPU6050.h>

class Gyro
{
    private:
    class Filter
    {
        private:
        uint8_t size;
        int16_t *buffer;
        uint8_t pointer;
        int32_t sum;

        public:

        void init(uint8_t size);

        ~Filter();

        int16_t filter(int16_t x);
    };

    Filter x_filter, y_filter, z_filter;

    float x, y, z;
    uint8_t mapped_id;

    int8_t invert_x, invert_y, invert_z;

    float sensitivity;
    float deadzone;
    float deadzone2;
    float min_delta;
    float min_delta2;

    public:
    enum BindToX : uint8_t
    {
        BIND_X,
        BIND_Z,
        BIND_XZ,
    };
    private:

    BindToX bind_to_x;

    MPU6050 mpu;

    uint32_t time0;
    uint32_t delay;
    bool (*_EnabledCallback)();
    bool enabled;

    public:

    Gyro();

    void init();

    void setEnabledCallback(bool (*_EnabledCallback)()) { this->_EnabledCallback = _EnabledCallback; }
    void enable() { enabled = true; }
    void disable() { enabled = false; }
    bool Enabled() { return enabled && _EnabledCallback(); }

    void setMappedId(uint8_t mapped_id) { this->mapped_id = mapped_id; }
    uint8_t getMappedId() { return mapped_id; }

    void setInvertX(bool invert_x = true) { this->invert_x = invert_x? -1 : 1; }
    void setInvertY(bool invert_y = true) { this->invert_y = invert_y? -1 : 1; }
    void setInvertZ(bool invert_z = true) { this->invert_z = invert_z? -1 : 1; }

    void setSensitivity(float sensitivity) { this->sensitivity = sensitivity; }
    void setDeadzone(float deadzone) { this->deadzone = deadzone; this->deadzone2 = deadzone * deadzone;}
    void setMinDelta(float min_delta) { this->min_delta = min_delta; this->min_delta2 = min_delta * min_delta;}

    void setBindToX(BindToX bind_to_x) { this->bind_to_x = bind_to_x; }

    void setDelay(uint32_t delay) { this->delay = delay; }

    void update(uint32_t time);

    int16_t getX() { return x; }
    int16_t getY() { return y; }
    int16_t getZ() { return z; }

    int16_t getDX();
    int16_t getDY();

    void getD(float &dx, float &dy);
};

#endif