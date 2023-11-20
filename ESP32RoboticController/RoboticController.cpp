
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

Gyro gyro;
NetworkHandler networkHandler(8081,  10000);

//unsigned long syncTimestamp = 0; // The Unix timestamp received from the PC
  // Default constructor
    // In your RoboticController.cpp
RoboticController::RoboticController() : activated(false), connectedToClient(false) {
   // Initialize your controller without a configuration
}
// void printServoConfig(const DigitalServoConfiguration config) {
//     Serial.print("Pin: "); Serial.println(config.pin);
//     // Serial.print("Min Angle: "); Serial.println(config.minAngle);
//     // Serial.print("Max Angle: "); Serial.println(config.maxAngle);
//     // Serial.print("Min Pulse: "); Serial.println(config.minPulseWidth);
//     // Serial.print("Max Pulse: "); Serial.println(config.maxPulseWidth);
//     // Serial.print("Default Angle: "); Serial.println(config.defaultAngle);
//     // Serial.print("Angle Range: "); Serial.println(config.angleRange);
//     // Serial.print("Inverted: "); Serial.println(config.inverted ? "Yes" : "No");
// }

RoboticController::RoboticController(BittleQuadrupedConstructor constructor)
{
 constructor.GetLimbs(_limbs);
}

// Constructor
// RoboticController::RoboticController(BittleQuadrupedConfiguration& config) : activated(true) , connectedToClient(false) 
// {
// Serial.println("Begin Robotic Controller Construction");

// //config.GetLimbs(_limbs);

//    for (auto& limbData : _limbs) {
//     Serial.println("config info ");
//     //Serial.println(limb.pin);
//   //  _limbs.push_back(RoboticLimb("Limb",limb.pin));
//   //_limbs.push_back(RoboticLimb("Limb",limbData));
//   }



//     for (auto& limb : _limbs) {

// //limb.Initialize();
//     }

// //Serial.println(config1.pin);

// //std::vector<QuadrupedLimbData*> limbData = config.GetLimbData();
//     // for (const auto& limb : config.GetLimbData()) {
//     //     for (const auto& segment : limb->Segments) {
//     //        // printServoConfig(segment->ServoConfig);
//     //          Serial.print("Pin: "); Serial.println(segment->ServoConfig.pin);
//     //     }
//     // }



// return;
// //    for (auto& limb : limbData) {
// //     _limbs.push_back(RoboticLimb("Limb",limb.Segments));
// //   }

// Serial.println("Limbs Constructed");
// return;

//     ESP32PWM::allocateTimer(0);
//     ESP32PWM::allocateTimer(1);
//     ESP32PWM::allocateTimer(2);
//     ESP32PWM::allocateTimer(3);  

// //     networkHandler.subscribeToEvents(this);
// //   networkHandler.SetRoboticController(this);
// //    networkHandler.initialize();
// Serial.print("Initialize Limbs : ");
// Serial.println(_limbs.size());
//    for (auto& limb : _limbs) {
  
//     limb.Initialize();
//   }
// return;


//  Serial.println("set start angles");

// int baseAngle = 0;
// int hipAngle = 0;
// int kneeAngle = 0;
// for (auto& limb : _limbs) {
  
//     limb.SetLimbServos(baseAngle,hipAngle,kneeAngle);
//   }
//     int servoValues[3]{0,0,0};


// // Serial.println("attempt to read angles");
// // for (auto& limb : _limbs) {
// //        limb.GetServoValues(servoValues);
// //        for (size_t i = 0; i < 3; i++)
// //        {
// //           Serial.println("Read angle ");
// //           Serial.println(servoValues[i]);
// //        }    
// //    }

//       gyro.begin();
//    Serial.println("Robot Configured");

// }

// RoboticLimb RoboticController::ConstructRoboticLimb(QuadrupedLimbData limbData)
// {
//    // Serial.println("build limb " + name );
// ;

//     std::vector<LimbSegment> _limbSegments;
//     _limbSegments.push_back(LimbSegment (" Base Segment"));
//     _limbSegments.push_back(LimbSegment("Hip Segment",limbData.Segments[1]));//  DigitalServo(name + " Hip Servo",hipConfig)));
//   _limbSegments.push_back(LimbSegment( " Knee Segment",limbData.Segments[2]));//DigitalServo(name + " Knee Servo",kneeConfig)));

//     return RoboticLimb("1",_limbSegments);

// }

void RoboticController::OnMessageReceived1(int messageType, const std::vector<unsigned char>& message) 
{ 
  //  Serial.println(messageType);
   switch (messageType) {
        case 0:  // Connection established, sync time
            EstablishConnection();
           // gyro.Calibrate();
            break;
        case 1:  // Return sensor data
      //  SendRobotInfo();
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
     for (auto& limb : _limbs) {

limb.SetLimbServos(10,15,56);
    }

    return;
   // Serial.println(connectedToClient);
if(!networkHandler.broadcasting){
 SendRobotInfo();
}
int baseAngle = 0;
int hipAngle = 0;
int kneeAngle = 0;
   for (auto& limb : _limbs) {
  
  //  limb.SetLimbServos(baseAngle,hipAngle,kneeAngle);
  }
     networkHandler.loop();
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
