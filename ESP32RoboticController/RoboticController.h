#ifndef ROBOTICCONTROLLER_H
#define ROBOTICCONTROLLER_H

#include "INetworkHandlerEventListener.h"
#include "RoboticLimb.h"
#include "BittleQuadrupedConstructor.h"
#include <array>
#include <vector>

class RoboticController : public INetworkHandlerEventListener {
public:
    explicit RoboticController();
    explicit RoboticController(const BittleQuadrupedConstructor& constructor);
    ~RoboticController();

    void RunControllerLoop();
    void activate();
    void deactivate();
    bool isActivated() const;

    void OnMessageReceived(int messageType, const std::vector<unsigned char>& message) override;
    void OnConnectionTimeout() override;

    void SendRobotInfo();
    void CalculateIKAllLimbs();

private:
    void EstablishConnection();
    void SerializeInt(byte* message, int value, int& offset, int messageSize);

    bool activated = false;
    bool connectedToClient = false;

    std::vector<RoboticLimb> _limbs;

    int preConnectionBaseAngle = 0;
    int preConnectionHipAngle = 65;
    int preConnectionKneeAngle = -145;

    int flConnectedBaseAngle = 0;
    int flConnectedHipAngle = 0;
    int flConnectedKneeAngle = 0;

    int frConnectedBaseAngle = 0;
    int frConnectedHipAngle = 0;
    int frConnectedKneeAngle = 0;

    int brConnectedBaseAngle = 0;
    int brConnectedHipAngle = 0;
    int brConnectedKneeAngle = 0;

    int blConnectedBaseAngle = 0;
    int blConnectedHipAngle = 0;
    int blConnectedKneeAngle = 0;
};

#endif // ROBOTICCONTROLLER_H
