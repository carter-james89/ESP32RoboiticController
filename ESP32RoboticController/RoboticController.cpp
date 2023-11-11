#include "RoboticController.h"
#include <iostream>
#include "RoboticLimb.h"
#include "QuadrupedLimbData.h"
#include "Gyro.h"
#include "QuadrupedConfiguration.h"
#include "NetworkHandler.h"


Gyro gyro;
NetworkHandler networkHandler(8081,  10000);

//unsigned long syncTimestamp = 0; // The Unix timestamp received from the PC
unsigned long syncMillis = 0;    // The millis() value when the timestamp was set

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
   switch (messageType) {
        case 0:  // Connection established, sync time
            EstablishConnection();
            break;
        case 1:  // Return sensor data
            RunSpeedTest();
            break;
        case 2:  // Set motor values
            runSensors();
            break;
        // ... other cases ...
    }}
void RoboticController::OnMessageReceived(int messageType, const std::vector<unsigned char>& message) {
   // Serial.println("Message received in RoboticController.");

    switch (messageType) {
        case 0:  // Connection established, sync time
            EstablishConnection();
            break;
        case 1:  // Return sensor data
            RunSpeedTest();
            break;
        case 2:  // Set motor values
            runSensors();
            break;
        // ... other cases ...
    }
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
    unsigned long currentMillis = millis();
    unsigned long timeSinceSync = currentMillis - syncMillis; // Time since synchronization in milliseconds
 // Serial.println(timeSinceSync);
    // Convert the timeSinceSync to a byte array
    byte timeByteArray[sizeof(timeSinceSync)];
    memcpy(timeByteArray, &timeSinceSync, sizeof(timeSinceSync));

    // Send the message with header 1
    networkHandler.sendMessage(1, timeByteArray, sizeof(timeSinceSync));
}

void RoboticController::calculateRotation(bool resetOffset) {
    // Assuming Gyro::GetSerializedGyroData has been updated to fill a byte array
    unsigned int length = 0;
    byte* gyroData = nullptr;

    // Get the serialized gyro data as a byte array
    gyro.GetSerializedGyroData(gyroData, length);

    // Send the message with the appropriate header
    networkHandler.sendMessage(2, gyroData, length);

    // Clean up the allocated gyroData after sending the message
    delete[] gyroData;
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
  Serial.print("Connection Request Received : ");

  syncMillis = millis();
  Serial.print("Received sync time: ");
   networkHandler.SendEmptyResponse(0);
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
