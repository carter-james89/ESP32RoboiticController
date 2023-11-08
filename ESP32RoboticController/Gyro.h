// Gyro.h
#ifndef GYRO_H
#define GYRO_H

#include <ArduinoJson.h>

#include <Wire.h>
#include <MPU6050.h>
#include "GyroData.h" // Include the GyroData header

class Gyro {
public:
    Gyro();
    void begin();
    void update();
    void printData();
    GyroData GetGyroData(); // Function to get gyro data
    String GetSerializedGyroData();

private:
    MPU6050 mpu;
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
};

#endif // GYRO_H
