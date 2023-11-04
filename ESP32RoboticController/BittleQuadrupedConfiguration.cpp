#include "BittleQuadrupedConfiguration.h"

BittleQuadrupedConfiguration::BittleQuadrupedConfiguration() {
    // Initialize your BittleQuadrupedConfiguration object here if needed
}


 std::vector<LimbSegment*>  BuildLimbSegments(int hipPin,int kneePin, int hipAngleOffset, int kneeAngleOffset,int hipPWMOffset,int kneePWMOffset, float hipMin, float hipMax, float kneeMin, float kneeMax, bool flipHip, bool flipKnee){
        std::vector<DigitalServo*> hipServos;
    std::vector<DigitalServo*> kneeServos;

    int maxPWM = 2500;
    int minPWM = 500;
    int homePWM = (maxPWM + minPWM)/2;

    // Manually creating DigitalServo instances on the heap
    DigitalServo* hipServo = new DigitalServo(hipPin, hipAngleOffset,hipPWMOffset, minPWM,maxPWM, hipMin, hipMax, flipHip);
    DigitalServo* kneeServo = new DigitalServo(kneePin, kneeAngleOffset, kneePWMOffset, minPWM,maxPWM, kneeMin, kneeMax, flipKnee);

    hipServos.push_back(hipServo);
    kneeServos.push_back(kneeServo);

    // Creating the LimbSegment with the servos
    LimbSegment* hipSegment = new LimbSegment(1, hipServos);
    LimbSegment* kneeSegment = new LimbSegment(1, kneeServos);

    std::vector<LimbSegment*> limbSegments;
    limbSegments.push_back(nullptr); // Assuming the first segment is null
    limbSegments.push_back(hipSegment);
    limbSegments.push_back(kneeSegment);
    return limbSegments;
}

RoboticLimb BittleQuadrupedConfiguration::GetFrontLeftLimb() {
      //  return RoboticLimb(BuildLimbSegments(33,19,0,0,-135,135,-135,135,false,true));
    return RoboticLimb(BuildLimbSegments(33,19,-45,-45,40,0,-135,135,-135,135,false,true));
}

RoboticLimb BittleQuadrupedConfiguration::GetFrontRightLimb() {
        return RoboticLimb(BuildLimbSegments(5,4,-45,-45,0,0,-135,135,-135,135,true,false));
      //   return RoboticLimb(BuildLimbSegments(5,4,0,0,-135,135,-135,135,true,false));
}

RoboticLimb BittleQuadrupedConfiguration::GetBackRightLimb() {
        return RoboticLimb(BuildLimbSegments(15,2,45,-45,80,0,-135,135,-135,135,true,false));
       //    return RoboticLimb(BuildLimbSegments(15,2,0,0,-135,135,-135,135,true,false));
}

RoboticLimb BittleQuadrupedConfiguration::GetBackLeftLimb() {
       return RoboticLimb(BuildLimbSegments(14,27,45,-45,20,80,-135,135,-135,135,false,true));
      //    return RoboticLimb(BuildLimbSegments(14,27,0,0,-135,135,-135,135,false,true));
}
