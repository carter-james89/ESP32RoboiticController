#ifndef BITTLEQUADRUPEDCONFIGURATION_H
#define BITTLEQUADRUPEDCONFIGURATION_H

#include "QuadrupedConfiguration.h"
#include "LimbSegment.h"


class BittleQuadrupedConfiguration  {
public:
    // Implementations of pure virtual functions from the base class
    LimbSegment GetBaseSegment(){
        // Return a LimbSegment with specific properties for the base segment
        return LimbSegment(); // Example values
    }

    LimbSegment GetHipSegment(){
        // Return a LimbSegment with specific properties for the hip segment
        return LimbSegment(); // Example values
    }

    LimbSegment GetKneeSegment(){
        // Return a LimbSegment with specific properties for the knee segment
        return LimbSegment(); // Example values
    }
};

#endif // BITTLEQUADRUPEDCONFIGURATION_H
