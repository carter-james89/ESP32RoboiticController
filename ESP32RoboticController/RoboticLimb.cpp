#include <iostream>
#include "RoboticLimb.h"
#include "LimbSegment.h"
#include "DigitalServo.h"
#include <cmath>
#include <memory>

RoboticLimb::RoboticLimb() : activated(true) {}
// Constructor



RoboticLimb::~RoboticLimb() {
}

RoboticLimb::RoboticLimb(String name, std::vector<LimbSegment> limbSegments): _name(name) {
    this->limbSegments = limbSegments;
    Serial.print("make ");
    _name = name;
    Serial.println(_name);
}


void RoboticLimb::SetLimbServos(int base, int hip, int knee){
    Serial.print("set servos at ");
Serial.println(_name);
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
        Serial.print("get servos at ");
        Serial.println(_name);
 servoValues[0] = 0;
 servoValues[1] = limbSegments[1].GetServoAngle();
  servoValues[2] = limbSegments[2].GetServoAngle();
}
     
    //}
//    void RoboticLimb::SerializeLimbData(std::vector<std::uint8_t>& existingSerializedInts) {
//         for (const auto& segment : _limbSegments) {
//             int angle = segment.GetServoAngle(0);
//             // Convert angle to byte and append to the vector
//             existingSerializedInts.push_back(static_cast<std::uint8_t>(angle));
//         }
//     }

void RoboticLimb::CalculateIK(){
//       std::cout << "Run IK!" << std::endl;
//   // _hipSegment.SetServo(0,-50);
//   // _kneeSegment.SetServo(0,90);

//        _hipSegment.SetServo(0,-70);
//     _kneeSegment.SetServo(0,150);
// }
// void RoboticLimb::CalculateIK(double targetX, double targetY) {
//     std::cout << "Running IK for target (" << targetX << ", " << targetY << ")!" << std::endl;

//      _kneeSegment.SetServo(0, 90);

//     // Calculate the distance to the target
//     double distance = std::sqrt(targetX * targetX + targetY * targetY);

//     // Retrieve lengths of the limb segments
//     double armLength1 = _hipSegment.GetLength(); // Replace with actual method to get length
//     double armLength2 = _kneeSegment.GetLength(); // Replace with actual method to get length

//     float angle1;
//     float angle2;

//     // Check if the target is within reach
//     if (distance > armLength1 + armLength2) {
//         // Target is out of reach
//         angle1 = 0.0f;
//         angle2 = 0.0f;
//     } else {
//         // Calculate angles using the law of cosines
//         double cosAngle2 = (distance * distance - armLength1 * armLength1 - armLength2 * armLength2) / (2 * armLength1 * armLength2);
//         double sinAngle2 = std::sqrt(1 - cosAngle2 * cosAngle2);
//         angle2 = std::atan2(sinAngle2, cosAngle2);

//         double alpha = std::atan2(targetY, targetX);
//         double beta = std::acos((distance * distance + armLength1 * armLength1 - armLength2 * armLength2) / (2 * distance * armLength1));
//         angle1 = alpha - beta;

//         // Convert angles from radians to degrees
//         float jointAngle1 = RadToDegree(angle1);
//         float jointAngle2 = RadToDegree(angle2);

//         // Set servo positions
//         _hipSegment.SetServo(0, jointAngle1);
//         _kneeSegment.SetServo(0, jointAngle2);
//     }

//     // If there's a base segment, you would also calculate its angle here
//     // based on the position of the target relative to the base
//     // This part of the code is omitted for brevity
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

float RadToDegree(float rad) {
    return rad * (180.0f / M_PI);
}
