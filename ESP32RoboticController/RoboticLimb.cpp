#include <iostream>
#include "RoboticLimb.h"
#include "LimbSegment.h"
#include "DigitalServo.h"
#include <cmath>
#include <memory>
#include <vector>



RoboticLimb::RoboticLimb() : activated(true),_initialized(false) {}
// Constructor



RoboticLimb::~RoboticLimb() {
}

RoboticLimb::RoboticLimb(String name, std::vector<LimbSegment> limbs) :_name(name),limbSegments(limbs),_initialized(false)
{

}

void RoboticLimb::Initialize(){
    if(_initialized){
          Serial.print("This Limb has already been initialized : ");
Serial.println(_name);
        return;
    }
     Serial.print("Initialize : ");
Serial.println(_name);

    _initialized = true;

limbSegments[1].Initialize();
limbSegments[2].Initialize();
}


void RoboticLimb::SetLimbServos(int base, int hip, int knee){
   // Serial.print("set servos at ");
//Serial.println(_name);
    //return;
  limbSegments[1].SetServoAngle(hip);
  limbSegments[2].SetServoAngle(knee);
}
 void RoboticLimb::SerializeLimbData(std::vector<std::uint8_t>& message) {
       // for (const auto& segment : _limbSegments) {
       // int angle = segment.GetServoAngle(0);

        //    const int messageSize = 3 * sizeof(int64_t) + 12 * sizeof(int);
        // byte message[messageSize];
        // int offset = 0;
//int offset =0;
        // Serialize each integer


        // Repeat for all other integer fields
        //memcpy(message + offset, angle, sizeof(angle));
        //offset += sizeof(angle);

        // // Convert the int angle to bytes and append to the message
        // std::uint8_t* angleBytes = reinterpret_cast<std::uint8_t*>(&angle);
        // for (size_t i = 0; i < sizeof(int); ++i) {
        //     message.push_back(angleBytes[i]);
        // }
    }

    void RoboticLimb::GetServoValues(int servoValues[3]) {
       // Serial.print("get servos at ");
       // Serial.println(_name);
 servoValues[0] = 0;
 servoValues[1] = limbSegments[1].GetServoAngle();
  servoValues[2] = limbSegments[2].GetServoAngle();
}

float RadToDegree(float rad) {
    return rad * (180.0f / M_PI);
}

void CalculateIK(float targetX, float targetY) {
    double distance = std::sqrt(targetX * targetX + targetY * targetY);

    auto armLength1 = 1;//m_hipRoboticLimbSegment.GetLength();
    auto armLength2 = 1;//m_kneeRoboticLimbSegment.GetLength();

    float angle1, angle2;

    // ... Rest of the code with C++ syntax ...

    if (distance > armLength1 + armLength2) {
        // Target is out of reach
        angle1 = 0.0f;
        angle2 = 0.0f;
    } else {
        // Calculate angles using the law of cosines
        double cosAngle2 = (distance * distance - armLength1 * armLength1 - armLength2 * armLength2) / (2 * armLength1 * armLength2);
        double sinAngle2 = std::sqrt(1 - cosAngle2 * cosAngle2);
        angle2 = static_cast<float>(std::atan2(sinAngle2, cosAngle2));

        double alpha = std::atan2(targetY, targetX);
        double beta = std::acos((distance * distance + armLength1 * armLength1 - armLength2 * armLength2) / (2 * distance * armLength1));
        angle1 = static_cast<float>(alpha - beta);

        float jointAngle1 = RadToDegree(angle1);
        float jointAngle2 = RadToDegree(angle2);
    }
}

// Activate the robotic limb
void RoboticLimb::activate() {
    activated = true;
    std::cout << "Robotic limb activated!" << std::endl;
}

// Deactivate the robotic limb
void RoboticLimb::deactivate() {
    activated = false;
    std::cout << "Robotic limb deactivated!" << std::endl;
}

// Check if the robotic limb is activated
bool RoboticLimb::isActivated() const {
    return activated;
}


