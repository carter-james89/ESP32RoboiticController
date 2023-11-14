#ifndef ROBOTICLIMB_H
#define ROBOTICLIMB_H

#include "LimbSegment.h"
#include <iostream>
#include "QuadrupedLimbData.h"
#include <memory>
#include "DigitalServo.h"

class RoboticLimb {
public:

RoboticLimb() ;
    // Constructor

    RoboticLimb(std::vector<LimbSegment> limbSegments);

    // Destructor
    ~RoboticLimb();

    // Member functions
    void activate();
    void deactivate();
    bool isActivated() const;

    void CalculateIK();
     void CalculateIK(double xPos,double yPos);
     void SetLimbServos(float baseAngle, float hipAngle, float kneeAngle);
     void SerializeLimbData(std::vector<std::uint8_t>& message);
      void GetServoValues(int servoValues[3]);

 

private:
float RadToDegree(float rad);
    bool activated;
    //  LimbSegment _baseSegment; 
    //  LimbSegment _hipSegment; 
    //  LimbSegment _kneeSegment; 
     std::vector<LimbSegment> limbSegments;
};

#endif // ROBOTICLIMB_H
