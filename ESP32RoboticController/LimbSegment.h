#ifndef LIMBSEGMENT_H
#define LIMBSEGMENT_H

#include "DigitalServo.h"
#include <vector>  // Include the vector header


class LimbSegment {
public:
    // Constructor
    LimbSegment();

        // Constructor
    LimbSegment(double length, std::vector<DigitalServo*> servos);

    // Destructor
    ~LimbSegment();

    // Member functions can be added here
    void activate();
    void deactivate();

    void SetServo(int servoPosInList, double angle);
    int GetServoAngle(int servoPosInList);

    double GetLength();

     std::vector<DigitalServo*>  GetServos();

private:
    // Member variables can be added here
    bool isActive;
    double _length;
   std::vector<DigitalServo*>  _servos; 


};

#endif // LIMBSEGMENT_H
