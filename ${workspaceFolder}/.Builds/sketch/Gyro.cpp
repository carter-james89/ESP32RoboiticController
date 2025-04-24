#line 1 "C:\\Users\\carte\\Projects\\Robotics\\Quadruped\\ESP32 Robotic Controller\\ESP32RoboticController\\Gyro.cpp"
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
    // You might want to take 
    return;
    
    //multiple readings and average them for better accuracy
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

void Gyro::GetSerializedGyroData(byte* &byteArray, unsigned int &length) {
    update();

    // Create a JSON object
    StaticJsonDocument<256> doc;
    doc["ax"] = ax;
    doc["ay"] = ay;
    doc["az"] = az;
    doc["gx"] = gx;
    doc["gy"] = gy;
    doc["gz"] = gz;

    // Serialize JSON to string
    String json;
    serializeJson(doc, json);

    // Check if byteArray is already allocated
    if (byteArray != nullptr) {
        delete[] byteArray; // Free existing memory
    }

    // Allocate memory for byteArray
    length = json.length();
    byteArray = new byte[length + 1]; // +1 for null-termination

    // Copy the JSON string into byteArray
    memcpy(byteArray, json.c_str(), length);
    byteArray[length] = '\0'; // Null-terminate the string
}


GyroData Gyro::GetGyroData() {
    // Make sure to update the sensor data before returning
    update();
    return GyroData(ax, ay, az, gx, gy, gz);
}
