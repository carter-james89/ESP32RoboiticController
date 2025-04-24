#ifndef ROBOTICCONTROLLER_H
#define ROBOTICCONTROLLER_H

#include "Network/NetworkEventListener.h"
#include "Limbs/RoboticLimb.h"
#include "RoboticConstructor/BittleQuadrupedConstructor.h"
#include <array>
#include <vector>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


struct QuadrupedData {
    int16_t VelocityX;
    int16_t VelocityY;
    int16_t VelocityZ;
    int16_t GyroX;
    int16_t GyroY;
    int16_t GyroZ;

    int FLBaseAngle, FLHipAngle, FLKneeAngle;
    int FRBaseAngle, FRHipAngle, FRKneeAngle;
    int BRBaseAngle, BRHipAngle, BRKneeAngle;
    int BLBaseAngle, BLHipAngle, BLKneeAngle;
};

class RoboticController : public NetworkEventListener {
public:
    explicit RoboticController();
    explicit RoboticController(const BittleQuadrupedConstructor& constructor);
    ~RoboticController();

    QuadrupedData GetQuadrupedData();

    void OnMessageReceived(int messageType, const std::vector<unsigned char>& message) override;
    void OnConnectionTimeout() override;
    void OnConnectionEstablished() override;

    void RunControllerLoop();
    void activate();
    void deactivate();
    bool isActivated() const;

    void CalculateIKAllLimbs();

private:
    void SerializeInt(byte* message, int value, int& offset, int messageSize);

    TaskHandle_t _controllerTaskHandle = nullptr;

    bool activated = false;
    bool connectedToClient = false;

    std::vector<RoboticLimb> _limbs;

    void SyncRobotData();

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
