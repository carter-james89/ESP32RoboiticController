#include <iostream>

#include "DigitalServo.h"
#include <vector>  // Include the vector header
#include "LimbSegment.h"


// Constructor
LimbSegment::LimbSegment() : isActive(true) {
    // Initialization can be added here
}

 LimbSegment::LimbSegment(float length, DigitalServo servo): isActive(true) 
 {
  _length = length;
        // Create DigitalServo objects dynamically and store their pointers
        _servo = servo;
 }

 void LimbSegment::SetServoAngle(int newAngle){
_servo.SetAngle(newAngle);
 }
 int LimbSegment::GetServoAngle(){
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