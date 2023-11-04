#include "RoboticController.h"
#include <iostream>
#include "RoboticLimb.h"

#include "QuadrupedConfiguration.h"

  // Default constructor
    // In your RoboticController.cpp
RoboticController::RoboticController() : activated(false) {
    // Initialize your controller without a configuration
}
// Constructor
RoboticController::RoboticController(QuadrupedConfiguration* config) : activated(true) 
{
        std::cout << "Robotic controller activated!" << std::endl;
          ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);


    _flLimb = config->GetFrontLeftLimb();
    _frLimb = config->GetFrontRightLimb();
    _brLimb = config->GetBackRightLimb();
    _blLimb= config->GetBackLeftLimb();


  

}

// Destructor
RoboticController::~RoboticController() {}

void RoboticController::RunControllerLoop(){
    _blLimb.CalculateIK();
    _frLimb.CalculateIK();
    _brLimb.CalculateIK();
    _flLimb.CalculateIK();
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
