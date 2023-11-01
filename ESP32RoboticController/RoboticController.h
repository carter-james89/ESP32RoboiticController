#ifndef ROBOTICCONTROLLER_H
#define ROBOTICCONTROLLER_H


#include "RoboticLimb.h"
#include "QuadrupedConfiguration.h"

class RoboticController {
public:
  // Default constructor
    RoboticController();
    // Constructor
    RoboticController(QuadrupedConfiguration config);

    // Destructor
    ~RoboticController();

    // Member functions
    void RunControllerLoop();
    void activate();
    void deactivate();
    bool isActivated() const;

private:
    bool activated;
     RoboticLimb _flLimb;
     RoboticLimb _frLimb;
     RoboticLimb _brLimb;
     RoboticLimb _blLimb;
};

#endif // ROBOTICCONTROLLER_H
