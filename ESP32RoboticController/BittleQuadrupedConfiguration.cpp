#include "BittleQuadrupedConfiguration.h"

BittleQuadrupedConfiguration::BittleQuadrupedConfiguration() {
    // Initialize your BittleQuadrupedConfiguration object here if needed
}

RoboticLimb BittleQuadrupedConfiguration::GetFrontLeftLimb() {
  
    std::vector<DigitalServo*> hipServos;
    std::vector<DigitalServo*> kneeServos;

    // Manually creating DigitalServo instances on the heap
    DigitalServo* hipServo = new DigitalServo(19, 0, -20, 20, false);
    //DigitalServo* kneeServo = new DigitalServo(12, 0, -20, 20, false);

    hipServos.push_back(hipServo);
   // kneeServos.push_back(kneeServo);

    // Creating the LimbSegment with the servos
    LimbSegment* hipSegment = new LimbSegment(1, hipServos);
   // LimbSegment* kneeSegment = new LimbSegment(1, kneeServos);

    std::vector<LimbSegment*> limbSegments;
    limbSegments.push_back(nullptr); // Assuming the first segment is null
    limbSegments.push_back(hipSegment);
  //  limbSegments.push_back(kneeSegment);
  limbSegments.push_back(nullptr); // Assuming the first segment is null
    return RoboticLimb(limbSegments);
}

RoboticLimb BittleQuadrupedConfiguration::GetFrontRightLimb() {
    // Similar implementation as GetFrontLeftLimb, with appropriate servo IDs
    // ...
}

RoboticLimb BittleQuadrupedConfiguration::GetBackRightLimb() {
    // Similar implementation as GetFrontLeftLimb, with appropriate servo IDs
    // ...
}

RoboticLimb BittleQuadrupedConfiguration::GetBackLeftLimb() {
    // Similar implementation as GetFrontLeftLimb, with appropriate servo IDs
    // ...
}
