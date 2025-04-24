#line 1 "C:\\Users\\carte\\Projects\\Robotics\\Quadruped\\ESP32 Robotic Controller\\ESP32RoboticController\\QuadrupedConfiguration.h"
#ifndef QUADRUPEDCONFIGURATION_H
#define QUADRUPEDCONFIGURATION_H


#include <memory>

#include <vector>

class QuadrupedConfiguration {
public:
    // Constructor
    QuadrupedConfiguration();

    // Destructor
   virtual ~QuadrupedConfiguration();


   //virtual std::vector<QuadrupedLimbData*>  GetLimbData();

    //std::vector<QuadrupedLimbData> LimbData;
};
 
#endif // QUADRUPEDCONFIGURATION_H
