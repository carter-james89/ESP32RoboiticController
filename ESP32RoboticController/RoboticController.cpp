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
RoboticController::RoboticController(std::vector<RoboticLimb> limbs) : activated(true) 
{
    std::cout << "Robotic controller activated!" << std::endl;
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);

  networkHandler.subscribeToEvents(this);
  networkHandler.SetRoboticController(this);
    networkHandler.initialize();
  
  
   _flLimb = limbs[0];
   _frLimb = limbs[1];
   _brLimb = limbs[2];
   _blLimb = limbs[3];

      gyro.begin();
   Serial.println("Robot Configured");

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
          //  runSensors();
            break;
        // ... other cases ...
    }
    }

    
void RoboticController::OnMessageReceived(int messageType, const std::vector<unsigned char>& message) {
    Serial.println("Message received in RoboticController.");
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

void serializeQuadrupedData(const QuadrupedData& data, uint8_t* buffer) {
    memcpy(buffer, &data, sizeof(QuadrupedData));
}

void RoboticController::SendRobotInfo() {
    try {
        Serial.println("Broadcast robot info.");

        // Create an instance of QuadrupedData
        QuadrupedData data;

        data.VelocityX = 0;
        data.VelocityY = 0;
        data.VelocityZ = 0;
        data.GyroX = 0;
        data.GyroY = 0;
        data.GyroZ = 0;

        // // Temporary array to hold servo values for each limb
        int servoValues[3];

        // Populate servo values for each limb
        _flLimb.GetServoValues(servoValues);
        data.FLBaseAngle = servoValues[0];
        data.FLHipAngle = servoValues[1];
        data.FLKneeAngle = servoValues[2];

        // _frLimb.GetServoValues(servoValues);
        // data.FRBaseAngle = servoValues[0];
        // data.FRHipAngle = servoValues[1];
        // data.FRKneeAngle = servoValues[2];

        // _brLimb.GetServoValues(servoValues);
        // data.BRBaseAngle = servoValues[0];
        // data.BRHipAngle = servoValues[1];
        // data.BRKneeAngle = servoValues[2];

        // _blLimb.GetServoValues(servoValues);
        // data.BLBaseAngle = servoValues[0];
        // data.BLHipAngle = servoValues[1];
        // data.BLKneeAngle = servoValues[2];

        uint8_t* buffer = new uint8_t[sizeof(QuadrupedData)];
        serializeQuadrupedData(data, buffer);
  Serial.println("Data ready to be sent.");
        networkHandler.sendMessage(1, buffer, sizeof(QuadrupedData));

        delete[] buffer;
    } catch (const std::exception& e) {
        Serial.print("Exception caught: ");
        Serial.println(e.what());
        // Optionally: rethrow the exception if you cannot handle it
        // throw;
    } catch (...) {
        Serial.println("Unknown exception caught");
        // Optionally: rethrow the exception
        // throw;
    }
}




void RoboticController::RunControllerLoop(){
     networkHandler.loop();
   // _blLimb.CalculateIK();
   // _frLimb.CalculateIK();
   // _brLimb.CalculateIK();
   // _flLimb.CalculateIK();
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
