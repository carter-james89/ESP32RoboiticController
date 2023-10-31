#ifndef LIMBSEGMENT_H
#define LIMBSEGMENT_H

#include "Servos/DigitalServo.h"
#include <vector>  // Include the vector header

class LimbSegment {
public:
    // Constructor
    LimbSegment();

    // Destructor
    ~LimbSegment();

    // Member functions can be added here
    void activate();
    void deactivate();

   //  std::vector<DigitalServo> GetServos();

private:
    // Member variables can be added here
    bool isActive;
 //  std::vector<DigitalServo> _servos; 
};

#endif // LIMBSEGMENT_H
