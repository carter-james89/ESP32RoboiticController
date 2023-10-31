#ifndef QUADRUPEDCONFIGURATION_H
#define QUADRUPEDCONFIGURATION_H

#include "LimbSegment.h"

class QuadrupedConfiguration {
public:
    // Constructor
    QuadrupedConfiguration ();

    // Destructor
    ~QuadrupedConfiguration ();
    // Pure virtual functions to be implemented by subclasses
     LimbSegment GetBaseSegment();
     LimbSegment GetHipSegment() ;
     LimbSegment GetKneeSegment();

};

#endif // QUADRUPEDCONFIGURATION_H
