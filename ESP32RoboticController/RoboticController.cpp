#include "RoboticController.h"
#include <iostream>
#include "RoboticLimb.h"
#include "QuadrupedLimbData.h"
#include "Gyro.h"
#include "QuadrupedConfiguration.h"
#include "NetworkHandler.h"
#include <cstdint>
#include <cstring> // For memcpy

struct QuadrupedData {
  int16_t VelocityX;
    int16_t VelocityY;
    int16_t VelocityZ;
    int16_t GyroX;
    int16_t GyroY;
    int16_t GyroZ;

    int FLBaseAngle;
    int FLHipAngle;
    int FLKneeAngle;

    int FRBaseAngle;
    int FRHipAngle;
    int FRKneeAngle;

    int BRBaseAngle;
    int BRHipAngle;
    int BRKneeAngle;

    int BLBaseAngle;
    int BLHipAngle;
    int BLKneeAngle;
};


Gyro gyro;
NetworkHandler networkHandler(8081,  10000);

//unsigned long syncTimestamp = 0; // The Unix timestamp received from the PC


  // Default constructor
    // In your RoboticController.cpp
RoboticController::RoboticController() : activated(false) {
    // Initialize your controller without a configuration
}
// Constructor
RoboticController::RoboticController(QuadrupedConfiguration* config) : activated(true) 
{
    std::cout << "Robotic controller activated!" << std::endl;
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);

  networkHandler.subscribeToEvents(this);
  networkHandler.SetRoboticController(this);
    networkHandler.initialize();
  

      gyro.begin();
   Serial.println("Robot Configured");

    _flLimb = config->GetFrontLeftLimb();
    _frLimb = config->GetFrontRightLimb();
    _brLimb = config->GetBackRightLimb();
    _blLimb= config->GetBackLeftLimb();

float baseStartAngle = 0;
    float hipStartAngle = -80;
    float kneeStartAgnle = 130;
    SetLimbs(new QuadrupedLimbData(baseStartAngle,hipStartAngle,kneeStartAgnle,baseStartAngle,hipStartAngle,kneeStartAgnle,baseStartAngle,hipStartAngle,kneeStartAgnle,baseStartAngle,hipStartAngle,kneeStartAgnle));
}
void RoboticController::OnMessageReceived1(int messageType, const std::vector<unsigned char>& message) 
{ 
    Serial.println(messageType);
   switch (messageType) {
        case 0:  // Connection established, sync time
            EstablishConnection();
           // gyro.Calibrate();
            break;
        case 1:  // Return sensor data
         SendRobotInfo();
            break;
        case 2:  // Set motor values
            runSensors();
            break;
        // ... other cases ...
    }}
void RoboticController::OnMessageReceived(int messageType, const std::vector<unsigned char>& message) {
    Serial.println("Message received in RoboticController.");

    // switch (messageType) {
    //     case 0:  // Connection established, sync time
    //         EstablishConnection();
    //         break;
    //     case 1:  // Return sensor data
    //           SendRobotInfo();
    //         break;
    //     case 2:  // Set motor values
    //         runSensors();
    //         break;
    //     // ... other cases ...
    // }
}

void RoboticController::SetLimbs(QuadrupedLimbData* limbData)
{
    if (limbData != nullptr) {
        _blLimb.SetLimbServos(limbData->BLBaseAngle,limbData->BLHipAngle,limbData->BLKneeAngle);
           _flLimb.SetLimbServos(limbData->FLBaseAngle,limbData->FLHipAngle,limbData->FLKneeAngle);
              _blLimb.SetLimbServos(limbData->BLBaseAngle,limbData->BLHipAngle,limbData->BLKneeAngle);
                 _brLimb.SetLimbServos(limbData->BRBaseAngle,limbData->BRHipAngle,limbData->BRKneeAngle);
    }
}

// Destructor
RoboticController::~RoboticController() {}

void RoboticController::RunSpeedTest() {
  
    // Send the message with header 1
    //networkHandler.sendMessage(1, timeByteArray, sizeof(timeSinceSync));
}

void RoboticController::calculateRotation(bool resetOffset) {
    // Assuming Gyro::GetSerializedGyroData has been updated to fill a byte array
    unsigned int length = 0;
    byte* gyroData = nullptr;

    // Get the serialized gyro data as a byte array
    gyro.GetSerializedGyroData(gyroData, length);

    // Check if gyroData is not null and length is greater than 0
    if (gyroData != nullptr && length > 0) {
        // Send the message with the appropriate header
        networkHandler.sendMessage(1, gyroData, length);
    } else {
        // Handle the error: gyroData is null or length is 0
        Serial.println("Error: Gyro data is null or length is 0");
    }

      std::vector<std::uint8_t> message;

    //RoboticLimb _flLimb, _frLimb, _brLimb, _blLimb;
    _flLimb.SerializeLimbData(message);
    _frLimb.SerializeLimbData(message);
    _brLimb.SerializeLimbData(message);
    _blLimb.SerializeLimbData(message);

    if (message.size() != 8) { // 4 limbs, each contributing 2 bytes
        // Something bad happened
    }
  for (size_t i = 0; i < message.size(); i += 4) {
        // Reconstruct each int from 4 bytes
        int reconstructedAngle = 
            (message[i] << 24) |
            (message[i + 1] << 16) |
            (message[i + 2] << 8) |
            message[i + 3];

        std::cout << "Angle: " << reconstructedAngle << std::endl;
    }

    // Clean up the allocated gyroData after sending the message
    delete[] gyroData;
}

  void RoboticController::SerializeInt(byte* message, int value, int& offset, int messageSize) {
    if (offset + sizeof(int) > messageSize) {
        // Handle error: not enough space in the message array
        return;
    }

    memcpy(message + offset, &value, sizeof(value));
    offset += sizeof(value);
}

void serializeQuadrupedData(const QuadrupedData& data, uint8_t* buffer) {
    memcpy(buffer, &data, sizeof(QuadrupedData));
}

void RoboticController::SendRobotInfo(){

// Create an instance of QuadrupedData
QuadrupedData data;

data.VelocityX = 0;
data.VelocityY = 0;
data.VelocityZ = 0;
data.GyroX = 0;
data.GyroY = 0;
data.GyroZ = 0;

// Temporary array to hold servo values for each limb
int servoValues[3];
    // Populate servo values for Front Left (FL) limb
_flLimb.GetServoValues(servoValues);
data.FLBaseAngle = servoValues[0];
data.FLHipAngle = servoValues[1];
data.FLKneeAngle = servoValues[2];

// Populate servo values for Front Right (FR) limb
_frLimb.GetServoValues(servoValues);
data.FRBaseAngle = servoValues[0];
data.FRHipAngle = servoValues[1];
data.FRKneeAngle = servoValues[2];

_brLimb.GetServoValues(servoValues);
data.BRBaseAngle = servoValues[0];
data.BRHipAngle = servoValues[1];
data.BRKneeAngle = servoValues[2];

_blLimb.GetServoValues(servoValues);
data.BLBaseAngle = servoValues[0];
data.BLHipAngle = servoValues[1];
data.BLKneeAngle = servoValues[2];

   int servoValues[3];
_flLimb.GetServoValues(servoValues);


  QuadrupedData data = {100, 200, 300, 1, 2, 3, 15, 2.0, 3.0 ,1, 2, 3, 1.0, 2.0, 3.0};


 uint8_t buffer[sizeof(QuadrupedData)];
    serializeQuadrupedData(data, buffer);

 networkHandler.sendMessage(1, buffer, sizeof(QuadrupedData));
return;
   // networkHandler.SendEmptyResponse(1);
   // return;
    int64_t gyroVelocityX;
      int64_t gyroVelocityY;
        int64_t gyroVelocityZ;

             const int messageSize = 3 * sizeof(int64_t) + 12 * sizeof(int);
        byte message[messageSize];
        int offset = 0;

      
for (int i = 0; i < 6; ++i) {
     SerializeInt(message, (int64_t)i, offset,messageSize);
}

        int servoValues[3];
_flLimb.GetServoValues(servoValues);
for (int i = 0; i < 3; ++i) {
     SerializeInt(message, servoValues[i], offset,messageSize);
}

networkHandler.sendMessage(1, message, messageSize);
        return;

servoValues[3];
_frLimb.GetServoValues(servoValues);
for (int i = 0; i < 3; ++i) {
     SerializeInt(message, servoValues[i], offset,messageSize);
}

servoValues[3];
_brLimb.GetServoValues(servoValues);
for (int i = 0; i < 3; ++i) {
     SerializeInt(message, servoValues[i], offset,messageSize);
}

servoValues[3];
_blLimb.GetServoValues(servoValues);
for (int i = 0; i < 3; ++i) {
     SerializeInt(message, servoValues[i], offset,messageSize);
}


        networkHandler.sendMessage(1, message, messageSize);
    }



void RoboticController::RunControllerLoop(){
     networkHandler.loop();
   // _blLimb.CalculateIK();
   // _frLimb.CalculateIK();
   // _brLimb.CalculateIK();
   // _flLimb.CalculateIK();
}


  void RoboticController::runSensors() {
 // calculateHeight();
  calculateRotation(false);
}
void RoboticController::calculateHeight() {
  //_groundHeight = sonar.ping_cm();
}

void RoboticController::OnConnectionTimeout(){

}
void RoboticController::OnConnectionTimeout1(){

}


void RoboticController::EstablishConnection() {
 // Serial.print("Connection Request Received : ");

  networkHandler.AttemptEstablishConnection();


}

// Activate the robotic controller
void RoboticController::activate() {
    activated = true;
    std::cout << "Robotic controller activated!" << std::endl;
}

// Deactivate the robotic controller
void RoboticController::deactivate() {
    activated = false;
    std::cout << "Robotic controller deactivated!" << std::endl;
}

// Check if the robotic controller is activated
bool RoboticController::isActivated() const {
    return activated;
}
