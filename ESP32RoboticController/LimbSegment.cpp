
#include <iostream>

#include "DigitalServo.h"
#include <vector>  // Include the vector header
#include "LimbSegment.h"


// Constructor
LimbSegment::LimbSegment() : isActive(true) {
    // Initialization can be added here
}

 LimbSegment::LimbSegment(double length, std::vector<DigitalServo*> servos): isActive(true) 
 {
  _length = length;
  _servos = servos;
 }

 void LimbSegment::SetServo(int servoPosInList, double angle){
    _servos[servoPosInList]->SetAngle(angle);
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

std::vector<DigitalServo*>  LimbSegment::GetServos(){
    return _servos;
}