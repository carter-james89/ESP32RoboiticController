#include "BittleQuadrupedConfiguration.h"

BittleQuadrupedConfiguration::BittleQuadrupedConfiguration() {
    // Initialize your BittleQuadrupedConfiguration object here if needed
}

RoboticLimb BittleQuadrupedConfiguration::GetFrontLeftLimb() {
  
    std::vector<DigitalServo*> hipServos;
    std::vector<DigitalServo*> kneeServos;

    int maxPWM = 8000;
    int minPWM = 1300;
    int homePWM = (maxPWM + minPWM)/2;

    // Manually creating DigitalServo instances on the heap
    DigitalServo* hipServo = new DigitalServo(19, 0,homePWM, minPWM,maxPWM,270, -60, 60, false);
    DigitalServo* kneeServo = new DigitalServo(33, 1,homePWM, minPWM,maxPWM,270, -60, 60, false);

    hipServos.push_back(hipServo);
    kneeServos.push_back(kneeServo);

    // Creating the LimbSegment with the servos
    LimbSegment* hipSegment = new LimbSegment(1, hipServos);
    LimbSegment* kneeSegment = new LimbSegment(1, kneeServos);

    std::vector<LimbSegment*> limbSegments;
    limbSegments.push_back(nullptr); // Assuming the first segment is null
    limbSegments.push_back(hipSegment);
    limbSegments.push_back(kneeSegment);
 // limbSegments.push_back(nullptr); // Assuming the first segment is null
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
