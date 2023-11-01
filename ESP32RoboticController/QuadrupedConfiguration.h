#ifndef QUADRUPEDCONFIGURATION_H
#define QUADRUPEDCONFIGURATION_H


#include "RoboticLimb.h"
#include <memory>

class QuadrupedConfiguration {
public:
    // Constructor
    QuadrupedConfiguration ();

    // Destructor
    ~QuadrupedConfiguration ();


     RoboticLimb GetFrontLeftLimb();
     RoboticLimb GetFrontRightLimb();
  RoboticLimb GetBackLeftLimb();
     RoboticLimb GetBackRightLimb();

};

#endif // QUADRUPEDCONFIGURATION_H
