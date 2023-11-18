#ifndef QUADRUPEDCONFIGURATION_H
#define QUADRUPEDCONFIGURATION_H


#include <memory>
#include "QuadrupedLimbData.h"

#include <vector>

class QuadrupedConfiguration {
public:
    // Constructor
    QuadrupedConfiguration();

    // Destructor
   virtual ~QuadrupedConfiguration();


   virtual std::vector<QuadrupedLimbData*>  GetLimbData();

    //std::vector<QuadrupedLimbData> LimbData;
};
 
#endif // QUADRUPEDCONFIGURATION_H
