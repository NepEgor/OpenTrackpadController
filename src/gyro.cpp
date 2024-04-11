#include "gyro.h"

#include <stdint.h>

#include "util_func.h"
 
void Gyro::Filter::init(uint8_t size)
{
    this->size = size;
    buffer = new int16_t[size];
    for (uint8_t i = 0; i < size; i++)
    {
        buffer[i] = 0;
    }
    pointer = 0;
    sum = 0;
}

Gyro::Filter::~Filter()
{
    delete[] buffer;
}

int16_t Gyro::Filter::filter(int16_t x)
{
    sum -= buffer[pointer];
    sum += x;
    buffer[pointer] = x;

    pointer = (pointer + 1) % size;

    return sum / size;
}

Gyro::Gyro()
{
    invert_x = 1;
    invert_y = 1;
    invert_z = 1;

    sensitivity = 1.0f;

    time0 = 0;
    delay = 0;

    bind_to_x = BIND_X;

    _EnabledCallback = [] { return false; };
}

void Gyro::init()
{
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    mpu.initialize();
    Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    /*
    mpu.setXGyroOffset(0);
    mpu.setYGyroOffset(0);
    mpu.setZGyroOffset(0);
    */
    mpu.CalibrateGyro(6);

    uint8_t filter_size = 5;
    x_filter.init(filter_size);
    y_filter.init(filter_size);
    z_filter.init(filter_size);

    //mpu.setIntDataReadyEnabled(1);

    //mpu.setDLPFMode(MPU6050_DLPF_BW_5);
}

void Gyro::update(uint32_t time)
{
    if (Enabled())
    {
        float dt = time - time0;
        if (dt > delay)
        {
            time0 = time;

            int16_t x, y, z;

            mpu.getRotation(&x, &y, &z);

            //x = x_filter.filter(x) * invert_x;
            //y = y_filter.filter(y) * invert_y;
            //z = z_filter.filter(z) * invert_z;

            dt /= 1000.0f;

            this->x = x * sensitivity * invert_x * dt;
            this->y = y * sensitivity * invert_y * dt;
            this->z = z * sensitivity * invert_z * dt;
        }
    }
}

int16_t Gyro::getDX()
{
    int32_t dx;

    switch (bind_to_x)
    {
        case BIND_X:
            dx = x;
            break;

        case BIND_Z:
            dx = z;
            break;

        case BIND_XZ:
            dx = x + z;
    }
    
    if (dx > -deadzone && dx < deadzone)
    {
        dx = 0;
    }
    else
    if (dx >= deadzone && dx < min_delta)
    {
        dx = min_delta;
    }
    else
    if (dx <= -deadzone && dx > -min_delta)
    {
        dx = -min_delta;
    }
    
    return clamp(dx, -32767, 32767);
}

int16_t Gyro::getDY()
{
    
    if (y > -deadzone && y < deadzone)
    {
        y = 0;
    }
    else
    if (y >= deadzone && y < min_delta)
    {
        y = min_delta;
    }
    else
    if (y <= -deadzone && y > -min_delta)
    {
        y = -min_delta;
    }
    
    return clamp(y, -32767, 32767);
}

void Gyro::getD(float &dx, float &dy)
{
    switch (bind_to_x)
    {
        case BIND_X:
            dx = x;
            break;

        case BIND_Z:
            dx = z;
            break;

        case BIND_XZ:
            dx = x + z;
    }

    dy = y;

    float dxy2 = dx * dx + dy * dy;

    if (dxy2 < deadzone2)
    {
        dx = 0;
        dy = 0;
    }
    else
    if (dxy2 < min_delta2)
    {
        float factor = min_delta / sqrt(dxy2);
        dx *= factor;
        dy *= factor;
    }
    else
    if (dxy2 > 1.f)
    {
        float len = sqrt(dxy2);
        dx /= len;
        dy /= len;
    }
}
