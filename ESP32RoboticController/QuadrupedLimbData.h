#ifndef QUADRUPEDLIMBDATA_H
#define QUADRUPEDLIMBDATA_H

#include "DigitalServo.h" // Include the header for DigitalServoConfiguration
#include "LimbSegmentData.h"
#include <vector>

class QuadrupedLimbData {
public:
   std::vector<LimbSegmentData> Segments;

    // Constructor
    QuadrupedLimbData( std::vector<LimbSegmentData> segments)
        : Segments(segments) {
        // Constructor body (if needed)
    }

    // Other member functions (if any)
};

#endif // QUADRUPEDLIMBDATA_H
