#include "BittleQuadrupedConfiguration.h"
#include "QuadrupedConfiguration.h"
#include "LimbSegment.h"
#include "DigitalServo.h"

BittleQuadrupedConfiguration::BittleQuadrupedConfiguration() {
    // Initialize your BittleQuadrupedConfiguration object here if needed
}



RoboticLimb BittleQuadrupedConfiguration::ConstructRoboticLimb( DigitalServo::DigitalServoConfiguration hipConfig, DigitalServo::DigitalServoConfiguration kneeConfig)
{
 LimbSegment baseSegment;

    std::vector<LimbSegment> _limbSegments;
    _limbSegments.push_back(baseSegment);
    _limbSegments.push_back(LimbSegment(1,DigitalServo(hipConfig)));
  _limbSegments.push_back(LimbSegment(1,DigitalServo(kneeConfig)));

    return RoboticLimb(_limbSegments);
}

RoboticLimb BittleQuadrupedConfiguration::ConstructFrontLeftLimb() {

    DigitalServo::DigitalServoConfiguration hipConfig;
hipConfig.pin = 22;
hipConfig.angleOffset = -45;
hipConfig.pwmOffset = 0;
hipConfig.maxAngleLimit = 135;
hipConfig.minAngleLimit = -135;
hipConfig.flip = false;

    DigitalServo::DigitalServoConfiguration kneeConfig;
kneeConfig.pin = 19;
kneeConfig.angleOffset = -45;
kneeConfig.pwmOffset = 0;
kneeConfig.maxAngleLimit = 135;
kneeConfig.minAngleLimit = -135;
kneeConfig.flip = false;

   return ConstructRoboticLimb(hipConfig,kneeConfig);
}



RoboticLimb BittleQuadrupedConfiguration::ConstructFrontRightLimb() {

        DigitalServo::DigitalServoConfiguration hipConfig;
hipConfig.pin = 5;
hipConfig.angleOffset = -45;
hipConfig.pwmOffset = 0;
hipConfig.maxAngleLimit = 135;
hipConfig.minAngleLimit = -135;
hipConfig.flip = true;

    DigitalServo::DigitalServoConfiguration kneeConfig;
kneeConfig.pin = 4;
kneeConfig.angleOffset = -45;
kneeConfig.pwmOffset = 0;
kneeConfig.maxAngleLimit = 135;
kneeConfig.minAngleLimit = -135;
kneeConfig.flip = false;

      return ConstructRoboticLimb(hipConfig,kneeConfig);
}


RoboticLimb BittleQuadrupedConfiguration::ConstructBackRightLimb() {
        DigitalServo::DigitalServoConfiguration hipConfig;
hipConfig.pin = 15;
hipConfig.angleOffset = -45;
hipConfig.pwmOffset = 80;
hipConfig.maxAngleLimit = 135;
hipConfig.minAngleLimit = -135;
hipConfig.flip = false;

    DigitalServo::DigitalServoConfiguration kneeConfig;
kneeConfig.pin = 2;
kneeConfig.angleOffset = -45;
kneeConfig.pwmOffset = 0;
kneeConfig.maxAngleLimit = 135;
kneeConfig.minAngleLimit = -135;
kneeConfig.flip = false;

  return ConstructRoboticLimb(hipConfig,kneeConfig);
}

RoboticLimb BittleQuadrupedConfiguration::ConstructBackLeftLimb() {
        DigitalServo::DigitalServoConfiguration hipConfig;
hipConfig.pin = 14;
hipConfig.angleOffset = -45;
hipConfig.pwmOffset = 20;
hipConfig.maxAngleLimit = 135;
hipConfig.minAngleLimit = -135;
hipConfig.flip = true;

    DigitalServo::DigitalServoConfiguration kneeConfig;
kneeConfig.pin = 27;
kneeConfig.angleOffset = -45;
kneeConfig.pwmOffset = 80;
kneeConfig.maxAngleLimit = 135;
kneeConfig.minAngleLimit = -135;
kneeConfig.flip = true;

  return ConstructRoboticLimb(hipConfig,kneeConfig);
}
