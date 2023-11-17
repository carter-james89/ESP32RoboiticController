#include <iostream>

#include "DigitalServo.h"
#include <vector>  // Include the vector header
#include "LimbSegment.h"
#include "LimbSegmentData.h"

// Constructor
 LimbSegment::LimbSegment(String name) : isActive(true),_initialized(false){
//     // Initialization can be added here
//     _name = name;
 }

 LimbSegment::LimbSegment(String name, LimbSegmentData configData) : isActive(true) ,_initialized(false)
 {
  //_length = length;
        // Create DigitalServo objects dynamically and store their pointers
        _servo = DigitalServo(name + " Servo",configData.ServoConfig);
      
        _name = name;
 }

 void LimbSegment::Initialize(){
    if(_initialized){
        Serial.print("this segment has already been initialized :");
        Serial.println(_name);
        return;
    }
       Serial.print("initialize segment :");
        Serial.println(_name);
    _initialized = true;
  _servo.Initialize();
}

 void LimbSegment::SetServoAngle(int newAngle){
 // Serial.println(_name);
_servo.SetAngle(newAngle);
 }
 int LimbSegment::GetServoAngle(){
   //   Serial.println(_name);
    return _servo.GetAngle();
 }

// Destructor
LimbSegment::~LimbSegment() {
    // Cleanup can be added here if necessary
}

void LimbSegment::activate() {
    isActive = true;
    std::cout << "LimbSegment activated!" << std::endl;
}

void LimbSegment::deactivate() {
    isActive = false;
    std::cout << "LimbSegment deactivated!" << std::endl;
}