#ifndef BITTLEQUADRUPEDCONFIGURATION_H
#define BITTLEQUADRUPEDCONFIGURATION_H

#include "QuadrupedConfiguration.h"
#include "LimbSegment.h"
#include "DigitalServo.h"
#include <vector>
#include <iostream>

class BittleQuadrupedConfiguration : public QuadrupedConfiguration {
public:
    BittleQuadrupedConfiguration();

    RoboticLimb GetFrontLeftLimb() override;
    RoboticLimb GetFrontRightLimb() override;
    RoboticLimb GetBackRightLimb() override;
    RoboticLimb GetBackLeftLimb() override;
};

#endif // BITTLEQUADRUPEDCONFIGURATION_H
