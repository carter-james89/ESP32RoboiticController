#ifndef ROBOTICLIMB_H
#define ROBOTICLIMB_H

#include "LimbSegment.h"

class RoboticLimb {
public:
    // Constructor
    RoboticLimb();

    // Destructor
    ~RoboticLimb();

    // Member functions
    void activate();
    void deactivate();
    bool isActivated() const;

    void CalculateIK();

private:
    bool activated;
     LimbSegment _baseSegment; 
     LimbSegment _hipSegment; 
     LimbSegment _kneeSegment; 
};

#endif // ROBOTICLIMB_H
