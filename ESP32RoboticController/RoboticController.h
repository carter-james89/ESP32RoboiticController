#ifndef ROBOTICCONTROLLER_H
#define ROBOTICCONTROLLER_H

#include "INetworkHandlerEventListener.h"
#include <iostream>
#include <vector>
#include "RoboticLimb.h"
#include "QuadrupedConfiguration.h"
#include "QuadrupedLimbData.h"

class RoboticController : public INetworkHandlerEventListener {
public:
  // Default constructor
    RoboticController();
    // Constructor
    RoboticController(QuadrupedConfiguration* config);

    // Destructor
    ~RoboticController();

    // Member functions
    void RunControllerLoop();
    void activate();
    void deactivate();
    bool isActivated() const;
  //void OnMessageReceived(int messageType, const std::vector<unsigned char>& message);
    void SetLimbs(QuadrupedLimbData* limbData);
      // Correctly overriding the OnMessageReceived method from INetworkHandlerEventListener
    void OnMessageReceived(int messageType, const std::vector<unsigned char>& message) override;
    void OnConnectionTimeout() override ;
 void OnConnectionTimeout1();
      void OnMessageReceived1(int messageType, const std::vector<unsigned char>& message);
     

private:
 void RunSpeedTest();
    void calculateRotation(bool resetOffset);
    void runSensors();
    void calculateHeight();
     void EstablishConnection();

    bool activated;
     RoboticLimb _flLimb;
     RoboticLimb _frLimb;
     RoboticLimb _brLimb;
     RoboticLimb _blLimb;
};

#endif // ROBOTICCONTROLLER_H
