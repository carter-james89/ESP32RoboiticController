#ifndef QUADRUPEDCONFIGURATION_H
#define QUADRUPEDCONFIGURATION_H

#include "RoboticLimb.h"
#include <memory>

class QuadrupedConfiguration {
public:
    // Constructor
    QuadrupedConfiguration();

    // Destructor
    virtual ~QuadrupedConfiguration();

    // Pure virtual functions
    virtual RoboticLimb GetFrontLeftLimb() = 0;
    virtual RoboticLimb GetFrontRightLimb() = 0;
    virtual RoboticLimb GetBackLeftLimb() = 0;
    virtual RoboticLimb GetBackRightLimb() = 0;
};

#endif // QUADRUPEDCONFIGURATION_H
