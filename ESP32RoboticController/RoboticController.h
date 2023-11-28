#ifndef ROBOTICCONTROLLER_H
#define ROBOTICCONTROLLER_H

#include "INetworkHandlerEventListener.h"
#include <iostream>
#include <vector>
#include "RoboticLimb.h"
#include "BittleQuadrupedConstructor.h"

class RoboticController : public INetworkHandlerEventListener {
public:
  // Default constructor 
   RoboticController();
    // Constructor
  //  RoboticController(BittleQuadrupedConfiguration& config);
RoboticController(BittleQuadrupedConstructor constructor);
    // Destructor
    ~RoboticController();

    // Member functions
    void RunControllerLoop();
    void activate();
    void deactivate();
    bool isActivated() const;
  //void OnMessageReceived(int messageType, const std::vector<unsigned char>& message);
 
      // Correctly overriding the OnMessageReceived method from INetworkHandlerEventListener
    void OnMessageReceived(int messageType, const std::vector<unsigned char>& message) override;
    void OnConnectionTimeout() override ;
 void OnConnectionTimeout1();
      void OnMessageReceived1(int messageType, const std::vector<unsigned char>& message);

      void SendRobotInfo();
     

private:
   bool activated;
    bool connectedToClient;
   std::vector<RoboticLimb> _limbs;
 void RunSpeedTest();
    void calculateRotation(bool resetOffset);
    void runSensors();
    void calculateHeight();
     void EstablishConnection();
 void SerializeInt(byte* message, int value, int& offset, int messageSize);
 //RoboticLimb ConstructRoboticLimb(QuadrupedLimbData limbData);
 int preConnectionBaseAngle;
  int preConnectionHipAngle;
   int preConnectionKneeAngle;
    int connectedBaseAngle;
  int connectedHipAngle;
   int connectedKneeAngle;
};

#endif // ROBOTICCONTROLLER_H
