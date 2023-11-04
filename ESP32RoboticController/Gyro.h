#ifndef GYRO_H
#define GYRO_H

#include <Wire.h>
#include <MPU6050.h>

class Gyro {
public:
    Gyro();
    void begin();
    void update();
    void printData();
private:
    MPU6050 mpu;
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
};

#endif // GYRO_H
