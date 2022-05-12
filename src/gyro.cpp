#include "gyro.h"

#include <stdint.h>
 
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
    mpu.CalibrateGyro();

    uint8_t filter_size = 5;
    x_filter.init(filter_size);
    y_filter.init(filter_size);
    z_filter.init(filter_size);

    mpu.setIntDataReadyEnabled(1);

    mpu.setDLPFMode(MPU6050_DLPF_BW_5);

    _Enabled = [] { return false; };
}

void Gyro::setEnabledCallback(bool (*Enabled)())
{
    this->_Enabled = Enabled;
}

void Gyro::update()
{
    if (Enabled())
    {
        mpu.getRotation(&x, &y, &z);

        x = x_filter.filter(x);
        y = y_filter.filter(y);
        z = z_filter.filter(z);
    }
}
