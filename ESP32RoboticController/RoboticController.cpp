
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
}

RoboticController::RoboticController(BittleQuadrupedConstructor constructor)
{
   Serial.println("Begin Robotic Controller Construction");
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
  preConnectionHipAngle = 45;
  preConnectionKneeAngle = -90;

   for (auto& limb : _limbs) {
  
   limb.SetLimbServos(preConnectionBaseAngle,preConnectionHipAngle,preConnectionKneeAngle);
  }
       networkHandler.subscribeToEvents(this);
  networkHandler.SetRoboticController(this);
   networkHandler.initialize();

}

void RoboticController::OnMessageReceived1(int messageType, const std::vector<unsigned char>& message) 
{ 
   // Serial.println(messageType);
   switch (messageType) {
        case 0:  // Connection established, sync time
            EstablishConnection();
           // gyro.Calibrate();
            break;
        case 1:  // Return sensor data
      //  SendRobotInfo();
            break;
        case 2:  // Set motor values
          if (message.size() >= sizeof(QuadrupedLimbData)) {
                QuadrupedLimbData limbData;
                memcpy(&limbData, message.data(), sizeof(QuadrupedLimbData));

                // Debugging: Print raw bytes
                // Serial.println("Raw Data:");
                // for (size_t i = 0; i < sizeof(QuadrupedLimbData); ++i) {
                //     Serial.print(message[i], HEX);
                //     Serial.print(" ");
                // }
                // Serial.println();

             //  connectedBaseAngle =  0;//limbData.FLBaseAngle;
connectedHipAngle = limbData.BLHipAngle;
               connectedKneeAngle = limbData.BLKneeAngle;
//               for (auto& limb : _limbs) {
// limb.SetLimbServos(0,limbData.BLHipAngle,limbData.BLKneeAngle);
//               }

                // Print the angle
                Serial.print("BLHipAngle from network: ");
                Serial.println(limbData.BLHipAngle);
                 Serial.println(limbData.BLKneeAngle);
            break;
        // ... other cases ...
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
        uint8_t* buffer = new uint8_t[sizeof(QuadrupedData)];
       
        serializeQuadrupedData(data, buffer);
        networkHandler.sendMessage(1, buffer, sizeof(QuadrupedData));
  return;
        delete[] buffer;
    } catch (const std::exception& e) {
        Serial.print("Exception caught: ");
        Serial.println(e.what());
    } catch (...) {
        Serial.println("Unknown exception caught");
    }
}

void RoboticController::RunControllerLoop(){
networkHandler.loop();
  if(!networkHandler.broadcasting){
       SendRobotInfo();
       


 Serial.print("angles");
 Serial.println(connectedHipAngle);
   Serial.println(connectedKneeAngle);
  }

     for (auto& limb : _limbs) {
if(!connectedToClient){
 limb.SetLimbServos(preConnectionBaseAngle,preConnectionHipAngle,preConnectionKneeAngle);
}
else{

 // limb.SetLimbServos(connectedBaseAngle,connectedHipAngle,connectedKneeAngle);
}
}
   // Serial.println(connectedToClient);

}


void RoboticController::OnConnectionTimeout(){
connectedToClient = false;
}
void RoboticController::OnConnectionTimeout1(){
connectedToClient = false;
}


void RoboticController::EstablishConnection() {
  Serial.print("Connection Request Received : ");
connectedToClient = true;
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
