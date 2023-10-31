#include "RoboticController.h"
#include <iostream>
#include "RoboticLimb.h"



// Constructor
RoboticController::RoboticController() : activated(true) {}

// Destructor
RoboticController::~RoboticController() {}

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
