
#include <iostream>

#include "DigitalServo.h"
#include <vector>  // Include the vector header
#include "LimbSegment.h"

// Constructor
LimbSegment::LimbSegment() : isActive(false) {
    // Initialization can be added here
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

 std::vector<DigitalServo> LimbSegment::GetServos(){
    return _servos;
}