#line 1 "C:\\Users\\carte\\Projects\\Robotics\\Quadruped\\ESP32 Robotic Controller\\ESP32RoboticController\\BittleQuadrupedConstructor.cpp"
#include "DigitalServo.h"
#include "BittleQuadrupedConstructor.h"

// Constructor
BittleQuadrupedConstructor::BittleQuadrupedConstructor() {
    // Initialize your constructor here
    // For example, you might want to initialize the servoConfigs, limbData, and segmentData vectors
    // if they are uncommented in your class definition.
}

void BittleQuadrupedConstructor::GetLimbs(std::vector<RoboticLimb>& limbs) const {
    // 1) Ensure the vector is empty and has capacity for 4 limbs
    limbs.clear();
    limbs.reserve(4);

    // --- Front‑Left Limb ---
    DigitalServo::ServoBuildData flHipConfig;
    flHipConfig.pin            = 33;
    flHipConfig.angleOffset    = 53;
    flHipConfig.pwmOffset      = 0;
    flHipConfig.minPWM         = 500;
    flHipConfig.maxPWM         = 2500;
    flHipConfig.minAngleLimit  = -134;
    flHipConfig.maxAngleLimit  = 134;
    flHipConfig.flip           = false;

    DigitalServo::ServoBuildData flKneeConfig;
    flKneeConfig.pin           = 19;
    flKneeConfig.angleOffset   = 43;
    flKneeConfig.pwmOffset     = 0;
    flKneeConfig.minPWM        = 500;
    flKneeConfig.maxPWM        = 2500;
    flKneeConfig.minAngleLimit = -134;
    flKneeConfig.maxAngleLimit = 134;
    flKneeConfig.flip          = true;

    limbs.emplace_back("FL Limb", std::vector<LimbSegment>{
        LimbSegment("FL Base (Disabled)"),
        LimbSegment("FLHip", 1.0f, DigitalServo(String("FL Hip"), flHipConfig)),
        LimbSegment("FLKnee", 1.0f, DigitalServo(String("FL Knee"), flKneeConfig))
    });
    

    // --- Front‑Right Limb ---
    DigitalServo::ServoBuildData frHipConfig;
    frHipConfig.pin            = 5;
    frHipConfig.angleOffset    = 45;
    frHipConfig.pwmOffset      = 0;
    frHipConfig.minPWM         = 500;
    frHipConfig.maxPWM         = 2500;
    frHipConfig.minAngleLimit  = -134;
    frHipConfig.maxAngleLimit  = 134;
    frHipConfig.flip           = true;

    DigitalServo::ServoBuildData frKneeConfig;
    frKneeConfig.pin           = 4;
    frKneeConfig.angleOffset   = 45;
    frKneeConfig.pwmOffset     = 0;
    frKneeConfig.minPWM        = 500;
    frKneeConfig.maxPWM        = 2500;
    frKneeConfig.minAngleLimit = -134;
    frKneeConfig.maxAngleLimit = 134;
    frKneeConfig.flip          = false;

    limbs.emplace_back("FR Limb", std::vector<LimbSegment>{
        LimbSegment("FR Base (Disabled)"),
        LimbSegment("FRHip", 1.0f, DigitalServo(String("FR Hip"), frHipConfig)),
        LimbSegment("FRKnee", 1.0f, DigitalServo(String("FR Knee"), frKneeConfig))
    });
    

    // --- Back‑Right Limb ---
    DigitalServo::ServoBuildData brHipConfig;
    brHipConfig.pin            = 15;
    brHipConfig.angleOffset    = -55;
    brHipConfig.pwmOffset      = 0;
    brHipConfig.minPWM         = 500;
    brHipConfig.maxPWM         = 2500;
    brHipConfig.minAngleLimit  = -134;
    brHipConfig.maxAngleLimit  = 134;
    brHipConfig.flip           = true;

    DigitalServo::ServoBuildData brKneeConfig;
    brKneeConfig.pin           = 2;
    brKneeConfig.angleOffset   = 45;
    brKneeConfig.pwmOffset     = 0;
    brKneeConfig.minPWM        = 500;
    brKneeConfig.maxPWM        = 2500;
    brKneeConfig.minAngleLimit = -134;
    brKneeConfig.maxAngleLimit = 134;
    brKneeConfig.flip          = false;

    limbs.emplace_back("BR Limb", std::vector<LimbSegment>{
        LimbSegment("BR Base (Disabled)"),
        LimbSegment("BRHip", 1.0f, DigitalServo(String("BR Hip"), brHipConfig)),
        LimbSegment("BRKnee", 1.0f, DigitalServo(String("BR Knee"), brKneeConfig))
    });
    

    // --- Back‑Left Limb ---
    DigitalServo::ServoBuildData blHipConfig;
    blHipConfig.pin            = 14;
    blHipConfig.angleOffset    = -42;
    blHipConfig.pwmOffset      = 0;
    blHipConfig.minPWM         = 500;
    blHipConfig.maxPWM         = 2500;
    blHipConfig.minAngleLimit  = -134;
    blHipConfig.maxAngleLimit  = 134;
    blHipConfig.flip           = false;

    DigitalServo::ServoBuildData blKneeConfig;
    blKneeConfig.pin           = 27;
    blKneeConfig.angleOffset   = 35;
    blKneeConfig.pwmOffset     = 0;
    blKneeConfig.minPWM        = 500;
    blKneeConfig.maxPWM        = 2500;
    blKneeConfig.minAngleLimit = -134;
    blKneeConfig.maxAngleLimit = 134;
    blKneeConfig.flip          = true;

    limbs.emplace_back("BL Limb", std::vector<LimbSegment>{
        LimbSegment("BL Base (Disabled)"),
        LimbSegment("BLHip", 1.0f, DigitalServo(String("BL Hip"), blHipConfig)),
        LimbSegment("BLKnee", 1.0f, DigitalServo(String("BL Knee"), blKneeConfig))
    });    
}
