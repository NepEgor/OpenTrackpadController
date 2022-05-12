#ifndef GYRO_H
#define GYRO_H

#include <stdint.h>

#include <MPU6050.h>

class Gyro
{
    private:
    int16_t x, y, z;

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

    MPU6050 mpu;

    bool (*_Enabled)();

    public:

    void init();

    void setEnabledCallback(bool (*_Enabled)());
    bool Enabled() { return _Enabled(); };

    void update();

    int16_t getX() { return x; }
    int16_t getY() { return y; }
    int16_t getZ() { return z; }

};

#endif