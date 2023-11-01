#include <iostream>
#include "RoboticLimb.h"
#include "LimbSegment.h"

RoboticLimb::RoboticLimb() : activated(true) {}
// Constructor
RoboticLimb::RoboticLimb(std::vector<LimbSegment*> limbSegments) : activated(true) {
_baseSegment = limbSegments[0];
_hipSegment = limbSegments[1];
_kneeSegment = limbSegments[2];

}

// Destructor
RoboticLimb::~RoboticLimb() {}

void RoboticLimb::CalculateIK(){
_hipSegment->SetServo(1,10);
}

// Activate the robotic limb
void RoboticLimb::activate() {
    activated = true;
    std::cout << "Robotic limb activated!" << std::endl;
}

// Deactivate the robotic limb
void RoboticLimb::deactivate() {
    activated = false;
    std::cout << "Robotic limb deactivated!" << std::endl;
}

// Check if the robotic limb is activated
bool RoboticLimb::isActivated() const {
    return activated;
}
