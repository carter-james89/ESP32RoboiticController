#ifndef ROBOTICLIMB_H
#define ROBOTICLIMB_H

#include "LimbSegment.h"
#include <iostream>

class RoboticLimb {
public:

RoboticLimb() ;
    // Constructor
    RoboticLimb(std::vector<LimbSegment*>);

    // Destructor
    ~RoboticLimb();

    // Member functions
    void activate();
    void deactivate();
    bool isActivated() const;

    void CalculateIK();
     void CalculateIK(double xPos,double yPos);
     void SetLimbServos(float baseAngle, float hipAngle, float kneeAngle);

private:
float RadToDegree(float rad);
    bool activated;
     LimbSegment* _baseSegment; 
     LimbSegment* _hipSegment; 
     LimbSegment* _kneeSegment; 
};

#endif // ROBOTICLIMB_H
