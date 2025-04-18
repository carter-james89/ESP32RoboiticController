// RoboticController.cpp
#include "RoboticController.h"
#include "Gyro.h"
#include "NetworkHandler.h"
#include <Arduino.h>
#include <cmath>
#include <cstring>

Gyro gyro;
const int broadcastPort = 5501;
const String broadcastIP = "255.255.255.255";
NetworkHandler networkHandler(8081, broadcastIP, broadcastPort, 10000);

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

RoboticController::RoboticController() {}

RoboticController::RoboticController(const BittleQuadrupedConstructor& constructor) {
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);

    constructor.GetLimbs(_limbs);
    for (auto& limb : _limbs) {
        limb.Initialize();
        limb.SetLimbServos(preConnectionBaseAngle, preConnectionHipAngle, preConnectionKneeAngle);
    }

    networkHandler.SetRoboticController(this);
    networkHandler.initialize();
}

RoboticController::~RoboticController() {}

void RoboticController::RunControllerLoop() {
    networkHandler.loop();
    if (!networkHandler.broadcasting) {
        SendRobotInfo();
    }

    if (!connectedToClient) {
        for (auto& limb : _limbs) {
            limb.SetLimbServos(preConnectionBaseAngle, preConnectionHipAngle, preConnectionKneeAngle);
        }
    } else {
        _limbs[0].SetLimbServos(flConnectedBaseAngle, flConnectedHipAngle, flConnectedKneeAngle);
        _limbs[1].SetLimbServos(frConnectedBaseAngle, frConnectedHipAngle, frConnectedKneeAngle);
        _limbs[2].SetLimbServos(brConnectedBaseAngle, brConnectedHipAngle, brConnectedKneeAngle);
        _limbs[3].SetLimbServos(blConnectedBaseAngle, blConnectedHipAngle, blConnectedKneeAngle);
    }
}

void RoboticController::OnMessageReceived(int messageType, const std::vector<unsigned char>& message) {
    switch (messageType) {
        case 0:
            EstablishConnection();
            break;
        case 2:
            if (message.size() >= sizeof(QuadrupedData)) {
                QuadrupedData data;
                memcpy(&data, message.data(), sizeof(QuadrupedData));

                flConnectedBaseAngle = data.FLBaseAngle;
                flConnectedHipAngle = data.FLHipAngle;
                flConnectedKneeAngle = data.FLKneeAngle;

                frConnectedBaseAngle = data.FRBaseAngle;
                frConnectedHipAngle = data.FRHipAngle;
                frConnectedKneeAngle = data.FRKneeAngle;

                brConnectedBaseAngle = data.BRBaseAngle;
                brConnectedHipAngle = data.BRHipAngle;
                brConnectedKneeAngle = data.BRKneeAngle;

                blConnectedBaseAngle = data.BLBaseAngle;
                blConnectedHipAngle = data.BLHipAngle;
                blConnectedKneeAngle = data.BLKneeAngle;

                connectedToClient = true;
            }
            break;
    }
}

void RoboticController::OnConnectionTimeout() {
    connectedToClient = false;
}

void RoboticController::SendRobotInfo() {
    QuadrupedData data = {};
    int servoValues[3];

    for (size_t i = 0; i < _limbs.size(); ++i) {
        _limbs[i].GetServoValues(servoValues);

        switch (i) {
            case 0:
                data.FLBaseAngle = servoValues[0];
                data.FLHipAngle = servoValues[1];
                data.FLKneeAngle = servoValues[2];
                break;
            case 1:
                data.FRBaseAngle = servoValues[0];
                data.FRHipAngle = servoValues[1];
                data.FRKneeAngle = servoValues[2];
                break;
            case 2:
                data.BRBaseAngle = servoValues[0];
                data.BRHipAngle = servoValues[1];
                data.BRKneeAngle = servoValues[2];
                break;
            case 3:
                data.BLBaseAngle = servoValues[0];
                data.BLHipAngle = servoValues[1];
                data.BLKneeAngle = servoValues[2];
                break;
        }
    }

    uint8_t buffer[sizeof(QuadrupedData)];
    memcpy(buffer, &data, sizeof(QuadrupedData));
    networkHandler.sendMessage(1, buffer, sizeof(QuadrupedData));
}

void RoboticController::CalculateIKAllLimbs() {
    for (auto& limb : _limbs) {
        limb.CalculateIK(0.0, 0.0); // placeholder values
    }
}

void RoboticController::EstablishConnection() {
    Serial.print("Connection Request Received: ");
    Serial1.println(connectedToClient);
    networkHandler.AttemptEstablishConnection();
}

void RoboticController::activate() {
    activated = true;
    Serial.println("Robotic controller activated!");
}

void RoboticController::deactivate() {
    activated = false;
    Serial.println("Robotic controller deactivated!");
}

bool RoboticController::isActivated() const {
    return activated;
}
