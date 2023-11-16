#include <iostream>

#include "DigitalServo.h"
#include <vector>  // Include the vector header
#include "LimbSegment.h"


// Constructor
LimbSegment::LimbSegment(String name) : isActive(true){
    // Initialization can be added here
    _name = name;
}

 LimbSegment::LimbSegment(String name, float length, DigitalServo servo): isActive(true) 
 {
  _length = length;
        // Create DigitalServo objects dynamically and store their pointers
        _servo = servo;
        _name = name;
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