#include "DigitalServo.h"
#include "BittleQuadrupedConstructor.h"



// Constructor
BittleQuadrupedConstructor::BittleQuadrupedConstructor() {
    // Initialize your constructor here
    // For example, you might want to initialize the servoConfigs, limbData, and segmentData vectors
    // if they are uncommented in your class definition.
}

// GetLimbs method
void BittleQuadrupedConstructor::GetLimbs(std::vector<RoboticLimb>& limbs) {
      DigitalServo::ServoBuildData flHipConfig;
        flHipConfig.pin = 33;
        flHipConfig.angleOffset = -45;
        flHipConfig.pwmOffset = 0;
        flHipConfig.minPWM = 500;
        flHipConfig.maxPWM = 2500;
        flHipConfig.minAngleLimit = 134;
        flHipConfig.maxAngleLimit = -134;
        flHipConfig.flip = false;
   DigitalServo:: ServoBuildData flKneeConfig;
        flKneeConfig.pin = 19;
        flKneeConfig.angleOffset = -45;
        flKneeConfig.pwmOffset = 0;
        flKneeConfig.minPWM = 500;
        flKneeConfig.maxPWM = 2500;
        flHipConfig.minAngleLimit = 134;
        flHipConfig.maxAngleLimit = -134;
        flHipConfig.flip = false;

 std::vector<LimbSegment> segments;
 segments.push_back(LimbSegment("FL Base (Disabled)"));
segments.push_back(LimbSegment("FLHip", 1, DigitalServo("FL Hip", flHipConfig)));
segments.push_back(LimbSegment("FLKnee", 1, DigitalServo("FL Knee", flKneeConfig)));

   limbs.push_back(RoboticLimb("FL Limb", segments));
}
