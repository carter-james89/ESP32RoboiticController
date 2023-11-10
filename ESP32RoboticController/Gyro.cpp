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

    // Apply scale factors for ±250 dps and ±2g
    float gyroScale = 131.0;
    float accelScale = 16384.0;

    // Convert to standard units
    ax = ax / accelScale;
    ay = ay / accelScale;
    az = az / accelScale;
    gx = gx / gyroScale;
    gy = gy / gyroScale;
    gz = gz / gyroScale;

//      // Convert gyro readings from degrees per second to radians per second
//     gx = gx * (PI / 180);
//     gy = gy * (PI / 180);
//     gz = gz * (PI / 180);
 }

// ... [other includes, constructors, and methods]

void Gyro::Calibrate() {
    // You might want to take multiple readings and average them for better accuracy
    update(); // Make sure we have the latest data
    
    // Cache the current sensor values as offsets
    ax_offset = ax;
    ay_offset = ay;
    az_offset = az;
    gx_offset = gx;
    gy_offset = gy;
    gz_offset = gz;

    // You may also want to print out these values for debugging
    Serial.println("Calibration complete. Offsets:");
    Serial.print("ax_offset: "); Serial.print(ax_offset); 
    Serial.print(" ay_offset: "); Serial.print(ay_offset); 
    Serial.print(" az_offset: "); Serial.println(az_offset);
    Serial.print("gx_offset: "); Serial.print(gx_offset); 
    Serial.print(" gy_offset: "); Serial.print(gy_offset); 
    Serial.print(" gz_offset: "); Serial.println(gz_offset);
}



// ... [rest of the methods]


void Gyro::printData() {
    // Assuming ax, ay, az, gx, gy, gz are already populated
    Serial.print("Accel X: "); Serial.print(ax); 
    Serial.print(" Accel Y: "); Serial.print(ay); 
    Serial.print(" Accel Z: "); Serial.println(az);

    Serial.print("Gyro X: "); Serial.print(gx); 
    Serial.print(" Gyro Y: "); Serial.print(gy); 
    Serial.print(" Gyro Z: "); Serial.println(gz);
}

void Gyro::GetSerializedGyroData(byte* byteArray, unsigned int &length) {
    update();
    String json = "{";
    json += "\"ax\":" + String(ax) + ",";
    json += "\"ay\":" + String(ay) + ",";
    json += "\"az\":" + String(az) + ",";
    json += "\"gx\":" + String(gx) + ",";
    json += "\"gy\":" + String(gy) + ",";
    json += "\"gz\":" + String(gz);
    json += "}";

    // Ensure the byte array is large enough to hold the JSON string
    length = json.length(); // Get the length of the JSON string
    byteArray = new byte[length]; // Allocate memory for the byte array

    // Copy the JSON string into the byte array
    json.getBytes(byteArray, length);
}

GyroData Gyro::GetGyroData() {
    // Make sure to update the sensor data before returning
    update();
    return GyroData(ax, ay, az, gx, gy, gz);
}
