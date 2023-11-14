#ifndef QUADRUPEDCONFIGURATION_H
#define QUADRUPEDCONFIGURATION_H

#include "RoboticLimb.h"
#include <memory>
#include "DigitalServo.h"

class QuadrupedConfiguration {
public:
    // Constructor
    QuadrupedConfiguration();

    // Destructor
    virtual ~QuadrupedConfiguration();

//     struct LimbConfig {     
// DigitalServo::DigitalServoConfiguration baseConfig;
// DigitalServo::DigitalServoConfiguration hipConfig;
// DigitalServo::DigitalServoConfiguration kneeConfig;
// };

    // Pure virtual functions
    virtual RoboticLimb ConstructFrontLeftLimb()=0;
    virtual RoboticLimb ConstructFrontRightLimb()=0;
   virtual RoboticLimb ConstructBackRightLimb()=0;
   virtual RoboticLimb ConstructBackLeftLimb()=0;
};
 
#endif // QUADRUPEDCONFIGURATION_H
