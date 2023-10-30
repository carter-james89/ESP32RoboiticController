#ifndef QUADRUPEDCONFIGURATION_H
#define QUADRUPEDCONFIGURATION_H

#include "Limbs/LimbSegment.h"

class QuadrupedConfiguration {
public:
    // Pure virtual functions to be implemented by subclasses
    virtual LimbSegment GetBaseSegment() = 0;
    virtual LimbSegment GetHipSegment() = 0;
    virtual LimbSegment GetKneeSegment() = 0;

    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~QuadrupedConfiguration() {}
};

#endif // QUADRUPEDCONFIGURATION_H
