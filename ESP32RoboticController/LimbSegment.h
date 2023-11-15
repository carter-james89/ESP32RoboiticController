#ifndef LIMBSEGMENT_H
#define LIMBSEGMENT_H

#include "DigitalServo.h"
#include <vector>  // Include the vector header


class LimbSegment {
public:
    // Constructor
    LimbSegment(String name);

        // Constructor
    LimbSegment(String name, float length, DigitalServo servo);

    // Destructor
    ~LimbSegment();

    // Member functions can be added here
    void activate();
    void deactivate();

    double GetLength();

int GetServoAngle();
   void SetServoAngle(int newAngle);

private:
    // Member variables can be added here
    bool isActive;
    double _length;
   DigitalServo  _servo; 
   String _name;


};

#endif // LIMBSEGMENT_H
