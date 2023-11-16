#include "BittleQuadrupedConfiguration.h"
#include "QuadrupedConfiguration.h"
#include "LimbSegment.h"
#include "DigitalServo.h"

BittleQuadrupedConfiguration::BittleQuadrupedConfiguration() {
    // Initialize your BittleQuadrupedConfiguration object here if needed
}



RoboticLimb BittleQuadrupedConfiguration::ConstructRoboticLimb(String name, DigitalServoConfiguration hipConfig, DigitalServoConfiguration kneeConfig)
{
    Serial.println("build limb " + name );
 LimbSegment baseSegment(name + " Base Segment");

    std::vector<LimbSegment> _limbSegments;
    _limbSegments.push_back(baseSegment);
    _limbSegments.push_back(LimbSegment(name + " Hip Segment",1,DigitalServo(hipConfig)));
  _limbSegments.push_back(LimbSegment(name + " Knee Segment",1,DigitalServo(kneeConfig)));

    return RoboticLimb(name,_limbSegments);
}

RoboticLimb BittleQuadrupedConfiguration::ConstructFrontLeftLimb() {

    DigitalServoConfiguration hipConfig;
hipConfig.pin = 33;
hipConfig.angleOffset = -45;
hipConfig.pwmOffset = 0;
hipConfig.minPWM = 500;
hipConfig.maxPWM = 2500;
hipConfig.maxAngleLimit = 134;
hipConfig.minAngleLimit = -134;
hipConfig.flip = false;

    DigitalServoConfiguration kneeConfig;
kneeConfig.pin = 19;
kneeConfig.angleOffset = -45;
kneeConfig.pwmOffset = 0;
kneeConfig.minPWM = 500;
kneeConfig.maxPWM = 2500;
kneeConfig.maxAngleLimit = 135;
kneeConfig.minAngleLimit = -135;
kneeConfig.flip = false;

   return ConstructRoboticLimb("FL",hipConfig,kneeConfig);
}



RoboticLimb BittleQuadrupedConfiguration::ConstructFrontRightLimb() {

        DigitalServoConfiguration hipConfig;
hipConfig.pin = 5;
hipConfig.angleOffset = -45;
hipConfig.pwmOffset = 0;
hipConfig.minPWM = 500;
hipConfig.maxPWM = 2500;
hipConfig.maxAngleLimit = 135;
hipConfig.minAngleLimit = -135;
hipConfig.flip = true;

    DigitalServoConfiguration kneeConfig;
kneeConfig.pin = 4;
kneeConfig.angleOffset = -45;
kneeConfig.pwmOffset = 0;
kneeConfig.minPWM = 500;
kneeConfig.maxPWM = 2500;
kneeConfig.maxAngleLimit = 135;
kneeConfig.minAngleLimit = -135;
kneeConfig.flip = false;

      return ConstructRoboticLimb("FR",hipConfig,kneeConfig);
}


RoboticLimb BittleQuadrupedConfiguration::ConstructBackRightLimb() {
        DigitalServoConfiguration hipConfig;
hipConfig.pin = 15;
hipConfig.angleOffset = -45;
hipConfig.pwmOffset = 80;
hipConfig.maxAngleLimit = 135;
hipConfig.minAngleLimit = -135;
hipConfig.minPWM = 500;
hipConfig.maxPWM = 2500;
hipConfig.flip = false;

    DigitalServoConfiguration kneeConfig;
kneeConfig.pin = 2;
kneeConfig.angleOffset = -45;
kneeConfig.pwmOffset = 0;
kneeConfig.minPWM = 500;
kneeConfig.maxPWM = 2500;
kneeConfig.maxAngleLimit = 135;
kneeConfig.minAngleLimit = -135;
kneeConfig.flip = false;

  return ConstructRoboticLimb("BR",hipConfig,kneeConfig);
}

RoboticLimb BittleQuadrupedConfiguration::ConstructBackLeftLimb() {
        DigitalServoConfiguration hipConfig;
hipConfig.pin = 14;
hipConfig.angleOffset = -45;
hipConfig.pwmOffset = 20;
hipConfig.minPWM = 500;
hipConfig.maxPWM = 2500;
hipConfig.maxAngleLimit = 135;
hipConfig.minAngleLimit = -135;
hipConfig.flip = true;

    DigitalServoConfiguration kneeConfig;
kneeConfig.pin = 27;
kneeConfig.angleOffset = -45;
kneeConfig.pwmOffset = 80;
kneeConfig.minPWM = 500;
kneeConfig.maxPWM = 2500;
kneeConfig.maxAngleLimit = 135;
kneeConfig.minAngleLimit = -135;
kneeConfig.flip = true;

  return ConstructRoboticLimb("BL",hipConfig,kneeConfig);
}
