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

  //     RoboticLimb ConstructFrontLeftLimb() override;
  //   RoboticLimb ConstructFrontRightLimb() override;
  //  RoboticLimb ConstructBackRightLimb() override;
     std::vector<QuadrupedLimbData*>  GetLimbData() override;
  void OnConstructionComplete();
    private:
     std::vector<DigitalServoConfiguration*> servoConfigs;
    std::vector<QuadrupedLimbData*> limbData;
    std::vector<LimbSegmentData*> segmentData;
   // RoboticLimb ConstructRoboticLimb( String name, DigitalServoConfiguration hipServo, DigitalServoConfiguration kneeServo);
};

#endif // BITTLEQUADRUPEDCONFIGURATION_H
