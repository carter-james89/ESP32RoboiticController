#include <iostream>
#include "RoboticLimb.h"
#include "RoboticController.h"
#include "Gyro.h"
#include "QuadrupedConfiguration.h"
#include <cstdint>
#include <cstring> // For memcpy
#include "NetworkHandler.h"

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
   class QuadrupedLimbData
    {
      public:
         float FLBaseAngle;
         float FLHipAngle;
         float FLKneeAngle;

         float FRBaseAngle;
         float FRHipAngle;
         float FRKneeAngle;

         float BRBaseAngle;
         float BRHipAngle;
         float BRKneeAngle;

         float BLBaseAngle;
         float BLHipAngle;
         float BLKneeAngle;
    };

Gyro gyro;
NetworkHandler networkHandler(8081,  10000);

RoboticController::RoboticController() : activated(false), connectedToClient(false){
   // Initialize your controller without a configuration
    Serial.print("RoboticController instance created at: ");
    Serial.println((uintptr_t)this, HEX);
}

RoboticController::RoboticController(BittleQuadrupedConstructor constructor) : activated(false), connectedToClient(false)
{
   Serial.println("Begin Robotic Controller Construction");
   //   Serial.print("RoboticController instance created at: ");
 //   Serial.println((uintptr_t)this, HEX);
       ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);  

 constructor.GetLimbs(_limbs);
 Serial.println("Limbs Constructed");

for (auto& limbData : _limbs) {
  limbData.Initialize();
}
  preConnectionBaseAngle = 0;
  preConnectionHipAngle = 65;
  preConnectionKneeAngle = -145;

   for (auto& limb : _limbs) {
  
   limb.SetLimbServos(preConnectionBaseAngle,preConnectionHipAngle,preConnectionKneeAngle);
  }
  networkHandler.SetRoboticController(this);
   networkHandler.initialize();
}

void RoboticController::OnMessageReceived1(int messageType, const std::vector<unsigned char>& message) 
{ 
   switch (messageType) {
        case 0:  // Connection established, sync time
            EstablishConnection();
            break;
        case 1:  // Return sensor data
            break;
        case 2:  // Set motor values
          if (message.size() >= sizeof(QuadrupedLimbData)) {
                QuadrupedLimbData limbData;
                memcpy(&limbData, message.data(), sizeof(QuadrupedLimbData));

              flConnectedBaseAngle = limbData.BLBaseAngle;
              flConnectedHipAngle = limbData.FLHipAngle;
               flConnectedKneeAngle = limbData.FLKneeAngle;

   frConnectedBaseAngle = limbData.FRBaseAngle;
              frConnectedHipAngle = limbData.FRHipAngle;
               frConnectedKneeAngle = limbData.FRKneeAngle;

                  brConnectedBaseAngle = limbData.BRBaseAngle;
              brConnectedHipAngle = limbData.BRHipAngle;
               brConnectedKneeAngle = limbData.BRKneeAngle;

                  blConnectedBaseAngle = limbData.BLBaseAngle;
              blConnectedHipAngle = limbData.BLHipAngle;
               blConnectedKneeAngle = limbData.BLKneeAngle;

                 connectedToClient = true;
            break;
    }
   }
}
    
void RoboticController::OnMessageReceived(int messageType, const std::vector<unsigned char>& message) {
    Serial.println("Message received in RoboticController.");
}

// Destructor
RoboticController::~RoboticController() {}

void serializeQuadrupedData(const QuadrupedData& data, uint8_t* buffer) {
    memcpy(buffer, &data, sizeof(QuadrupedData));
}

void RoboticController::SendRobotInfo() {
  uint8_t* buffer = nullptr;

    try {
        QuadrupedData data;

        data.VelocityX = 0;
        data.VelocityY = 0;
        data.VelocityZ = 0;
        data.GyroX = 0;
        data.GyroY = 0;
        data.GyroZ = 0;

        int servoValues[3];
int limbCount = 0;
        for (auto& limb : _limbs) {

  limb.GetServoValues(servoValues);
if(limbCount == 0){
   
       data.FLBaseAngle = servoValues[0];
        data.FLHipAngle = servoValues[1];
        data.FLKneeAngle = servoValues[2];
}
else if(limbCount == 1){
    data.FRBaseAngle = servoValues[0];
        data.FRHipAngle = servoValues[1];
        data.FRKneeAngle = servoValues[2];
}
else if(limbCount == 2){
       data.BRBaseAngle = servoValues[0];
        data.BRHipAngle = servoValues[1];
        data.BRKneeAngle = servoValues[2];
}
else if(limbCount == 3){
      data.BLBaseAngle = servoValues[0];
        data.BLHipAngle = servoValues[1];
        data.BLKneeAngle = servoValues[2];
}
limbCount++;
        }
        buffer = new uint8_t[sizeof(QuadrupedData)];
       
        serializeQuadrupedData(data, buffer);
        networkHandler.sendMessage(1, buffer, sizeof(QuadrupedData));
 
       
    } catch (const std::exception& e) {
        Serial.print("Exception caught: ");
        Serial.println(e.what());
    } catch (...) {
        Serial.println("Unknown exception caught");
    }

     delete[] buffer;
}

void RoboticController::RunControllerLoop(){
networkHandler.loop();
  if(!networkHandler.broadcasting){
       SendRobotInfo();
  }
  for (auto& limb : _limbs) {
    if(!connectedToClient){
      limb.SetLimbServos(preConnectionBaseAngle,preConnectionHipAngle,preConnectionKneeAngle);
    }
    else{
       _limbs[0].SetLimbServos(flConnectedBaseAngle,flConnectedHipAngle,flConnectedKneeAngle);
       _limbs[1].SetLimbServos(frConnectedBaseAngle,frConnectedHipAngle,frConnectedKneeAngle);
       _limbs[2].SetLimbServos(brConnectedBaseAngle,brConnectedHipAngle,brConnectedKneeAngle);
       _limbs[3].SetLimbServos(blConnectedBaseAngle,blConnectedHipAngle,blConnectedKneeAngle);
    }
  }
}

void RoboticController::OnConnectionTimeout(){
connectedToClient = false;
}
void RoboticController::OnConnectionTimeout1(){
connectedToClient = false;
}

void RoboticController::EstablishConnection() {
  Serial.print("Connection Request Received : ");

Serial1.println(connectedToClient);
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
