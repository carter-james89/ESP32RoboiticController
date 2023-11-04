#include "Gyro.h"

Gyro::Gyro() : mpu() {}

void Gyro::begin() {
    Wire.begin();
    mpu.initialize();
    if (!mpu.testConnection()) {
        Serial.println("MPU6050 connection failed. Please check your connection.");
    }
}

void Gyro::update() {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
}

void Gyro::printData() {
    // Assuming ax, ay, az, gx, gy, gz are already populated
    Serial.print("Accel X: "); Serial.print(ax); 
    Serial.print(" Accel Y: "); Serial.print(ay); 
    Serial.print(" Accel Z: "); Serial.println(az);

    Serial.print("Gyro X: "); Serial.print(gx); 
    Serial.print(" Gyro Y: "); Serial.print(gy); 
    Serial.print(" Gyro Z: "); Serial.println(gz);
}
