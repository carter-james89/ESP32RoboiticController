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

      RoboticLimb ConstructFrontLeftLimb() override;
    RoboticLimb ConstructFrontRightLimb() override;
   RoboticLimb ConstructBackRightLimb() override;
    RoboticLimb ConstructBackLeftLimb() override;

    private:
    RoboticLimb ConstructRoboticLimb( DigitalServo::DigitalServoConfiguration hipServo, DigitalServo::DigitalServoConfiguration kneeServo);
};

#endif // BITTLEQUADRUPEDCONFIGURATION_H
