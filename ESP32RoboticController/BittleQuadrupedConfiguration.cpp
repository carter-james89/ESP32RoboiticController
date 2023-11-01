#ifndef BITTLEQUADRUPEDCONFIGURATION_H
#define BITTLEQUADRUPEDCONFIGURATION_H

#include "QuadrupedConfiguration.h"
#include "LimbSegment.h"
#include "DigitalServo.h"
#include <vector>

class BittleQuadrupedConfiguration {
public:
    RoboticLimb GetFrontLeftLimb()
    {
        std::vector<DigitalServo*> hipServos;
         std::vector<DigitalServo*> kneeServos;

        // Manually creating DigitalServo instances on the heap
        DigitalServo* hipServo = new DigitalServo(8, 0, -20, 20, false);
        DigitalServo* kneeServo = new DigitalServo(12, 0, -20, 20, false);

       hipServos.push_back(hipServo);
       kneeServos.push_back(kneeServo);     

        // Creating the LimbSegment with the servos
        LimbSegment* hipSegment = new LimbSegment(1, hipServos);
        LimbSegment* kneeSegment = new LimbSegment(1, kneeServos);

           std::vector<LimbSegment*> limbSegments;

           limbSegments.push_back(nullptr);
           limbSegments.push_back(hipSegment);
           limbSegments.push_back(kneeSegment);

        return RoboticLimb(limbSegments);
    }
      RoboticLimb GetFrontRightLimb()
    {
        std::vector<DigitalServo*> hipServos;
         std::vector<DigitalServo*> kneeServos;

        // Manually creating DigitalServo instances on the heap
        DigitalServo* hipServo = new DigitalServo(9, 0, -20, 20, false);
        DigitalServo* kneeServo = new DigitalServo(13, 0, -20, 20, false);

       hipServos.push_back(hipServo);
       kneeServos.push_back(kneeServo);     

        // Creating the LimbSegment with the servos
        LimbSegment* hipSegment = new LimbSegment(1, hipServos);
        LimbSegment* kneeSegment = new LimbSegment(1, kneeServos);

           std::vector<LimbSegment*> limbSegments;

           limbSegments.push_back(nullptr);
           limbSegments.push_back(hipSegment);
           limbSegments.push_back(kneeSegment);

        return RoboticLimb(limbSegments);
    }
      RoboticLimb GetBackRightLimb()
    {
        std::vector<DigitalServo*> hipServos;
         std::vector<DigitalServo*> kneeServos;

        // Manually creating DigitalServo instances on the heap
        DigitalServo* hipServo = new DigitalServo(10, 0, -20, 20, false);
        DigitalServo* kneeServo = new DigitalServo(14, 0, -20, 20, false);

       hipServos.push_back(hipServo);
       kneeServos.push_back(kneeServo);     

        // Creating the LimbSegment with the servos
        LimbSegment* hipSegment = new LimbSegment(1, hipServos);
        LimbSegment* kneeSegment = new LimbSegment(1, kneeServos);

           std::vector<LimbSegment*> limbSegments;

           limbSegments.push_back(nullptr);
           limbSegments.push_back(hipSegment);
           limbSegments.push_back(kneeSegment);

        return RoboticLimb(limbSegments);
    }
   RoboticLimb GetBackLeftLimb()
    {
        std::vector<DigitalServo*> hipServos;
         std::vector<DigitalServo*> kneeServos;

        // Manually creating DigitalServo instances on the heap
        DigitalServo* hipServo = new DigitalServo(11, 0, -20, 20, false);
        DigitalServo* kneeServo = new DigitalServo(15, 0, -20, 20, false);

       hipServos.push_back(hipServo);
       kneeServos.push_back(kneeServo);     

        // Creating the LimbSegment with the servos
        LimbSegment* hipSegment = new LimbSegment(1, hipServos);
        LimbSegment* kneeSegment = new LimbSegment(1, kneeServos);

           std::vector<LimbSegment*> limbSegments;

           limbSegments.push_back(nullptr);
           limbSegments.push_back(hipSegment);
           limbSegments.push_back(kneeSegment);

        return RoboticLimb(limbSegments);
    }
    // Implementations of pure virtual functions from the base class
    // ...
};

#endif // BITTLEQUADRUPEDCONFIGURATION_H
