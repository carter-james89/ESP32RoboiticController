#include "RoboticLimb.h"
#include <iostream>

// Constructor
RoboticLimb::RoboticLimb() : activated(true) {}

// Destructor
RoboticLimb::~RoboticLimb() {}

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
