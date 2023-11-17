#ifndef LimbSegmentData_H
#define LimbSegmentData_H

#include "DigitalServo.h" // Include the header for DigitalServoConfiguration


class LimbSegmentData {
public:
    DigitalServoConfiguration ServoConfig;
    float Length;

LimbSegmentData(float segmentLength,  DigitalServoConfiguration ServoConfig) {}
};

#endif // QUADRUPEDLIMBDATA_H
