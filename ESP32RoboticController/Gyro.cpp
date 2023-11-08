// Gyro.cpp
#include "Gyro.h"
#include <ArduinoJson.h>

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

String Gyro::GetSerializedGyroData(){
    update();
StaticJsonDocument<256> doc;
  doc["ax"] = ax;
  doc["ay"] = ay;
  doc["az"] = az;
  doc["gx"] = gx;
  doc["gy"] = gy;
  doc["gz"] = gz;
  
  String output;
  serializeJson(doc, output);
  return output;
}

GyroData Gyro::GetGyroData() {
    // Make sure to update the sensor data before returning
    update();
    return GyroData(ax, ay, az, gx, gy, gz);
}
