#line 1 "C:\\Users\\carte\\Projects\\Robotics\\Quadruped\\ESP32 Robotic Controller\\ESP32RoboticController\\Gyro.h"
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
    void GetSerializedGyroData(byte* &byteArray, unsigned int &length);
     void Calibrate(); 

private:
    MPU6050 mpu;
    int16_t ax, ay, az;
    int16_t gx, gy, gz;

     // Variables to store the offsets
    int16_t ax_offset, ay_offset, az_offset;
    int16_t gx_offset, gy_offset, gz_offset;
};

#endif // GYRO_H
