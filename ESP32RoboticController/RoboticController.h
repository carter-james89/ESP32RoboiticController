#ifndef ROBOTICCONTROLLER_H
#define ROBOTICCONTROLLER_H


#include "Limbs/RoboticLimb.h" // Include the header file here

class RoboticController {
public:
    // Constructor
    RoboticController();

    // Destructor
    ~RoboticController();

    // Member functions
    void activate();
    void deactivate();
    bool isActivated() const;

private:
    bool activated;
   //  RoboticLimb _flLimb;
    // RoboticLimb _frLimb;
    // RoboticLimb _brLimb;
    // RoboticLimb _blLimb;
};

#endif // ROBOTICCONTROLLER_H
