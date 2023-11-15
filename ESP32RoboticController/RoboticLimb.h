#ifndef ROBOTICLIMB_H
#define ROBOTICLIMB_H

#include "LimbSegment.h"
#include <iostream>
#include "QuadrupedLimbData.h"
#include <memory>

class RoboticLimb {
public:

RoboticLimb() ;
    // Constructor

    RoboticLimb(String name, std::vector<LimbSegment> limbSegments);

    // Destructor
    ~RoboticLimb();

    // Member functions
    void activate();
    void deactivate();
    bool isActivated() const;

    void CalculateIK();
     void CalculateIK(double xPos,double yPos);
     void SetLimbServos(int baseAngle, int hipAngle, int kneeAngle);
     void SerializeLimbData(std::vector<std::uint8_t>& message);
      void GetServoValues(int servoValues[3]);

 

private:
float RadToDegree(float rad);
    bool activated;
    String _name;
    //  LimbSegment _baseSegment; 
    //  LimbSegment _hipSegment; 
    //  LimbSegment _kneeSegment; 
     std::vector<LimbSegment> limbSegments;
};

#endif // ROBOTICLIMB_H
