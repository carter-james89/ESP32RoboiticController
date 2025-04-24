#line 1 "C:\\Users\\carte\\Projects\\Robotics\\Quadruped\\ESP32 Robotic Controller\\ESP32RoboticController\\BittleQuadrupedConstructor.h"
#ifndef BITTLEQUADRUPEDCONSTRUCTOR_H
#define BITTLEQUADRUPEDCONSTRUCTOR_H

#include "RoboticLimb.h"
#include <vector>

// Default constructor

class BittleQuadrupedConstructor  {
public:

    BittleQuadrupedConstructor();
     void  GetLimbs(std::vector<RoboticLimb>& limbs) const;
    private:
   //  std::vector<DigitalServoConfiguration*> servoConfigs;
   // std::vector<QuadrupedLimbData*> limbData;
  //  std::vector<LimbSegmentData*> segmentData;
};

#endif // BITTLEQUADRUPEDCONFIGURATION_H
