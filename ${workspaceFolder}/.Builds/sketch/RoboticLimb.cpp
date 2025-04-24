#line 1 "C:\\Users\\carte\\Projects\\Robotics\\Quadruped\\ESP32 Robotic Controller\\ESP32RoboticController\\RoboticLimb.cpp"
#include "RoboticLimb.h"
#include <Arduino.h>      // For Serial
#include <cmath>          // For std::sqrt, std::atan2, etc.

// Default constructor
RoboticLimb::RoboticLimb()
    : activated(true), _name(""), _initialized(false), limbSegments() {}

// Parameterized constructor
RoboticLimb::RoboticLimb(const String& name, const std::vector<LimbSegment>& limbs)
    : activated(true), _name(name), limbSegments(limbs), _initialized(false) {}

// Destructor
RoboticLimb::~RoboticLimb() = default;

// Initialize the limb's segments (typically hip & knee)
void RoboticLimb::Initialize() {
    if (_initialized) {
        Serial.print("This Limb has already been initialized: ");
        Serial.println(_name);
        return;
    }

    Serial.print("Initializing Limb: ");
    Serial.println(_name);
    _initialized = true;

    for (size_t i = 1; i < limbSegments.size(); ++i) {
        limbSegments[i].Initialize();
    }
}

// Set servo angles for hip and knee
void RoboticLimb::SetLimbServos(int baseAngle, int hipAngle, int kneeAngle) {
    if (limbSegments.size() >= 3) {
        limbSegments[1].SetServoAngle(hipAngle);
        limbSegments[2].SetServoAngle(kneeAngle);
    }
}

// Serialize limb servo angles into a byte vector
void RoboticLimb::SerializeLimbData(std::vector<std::uint8_t>& message) {
    for (size_t i = 1; i <= 2 && i < limbSegments.size(); ++i) {
        int angle = limbSegments[i].GetServoAngle();
        std::uint8_t* bytes = reinterpret_cast<std::uint8_t*>(&angle);
        for (size_t b = 0; b < sizeof(int); ++b) {
            message.push_back(bytes[b]);
        }
    }
}

// Output servo angles into provided array
void RoboticLimb::GetServoValues(int servoValues[3]) {
    servoValues[0] = 0;
    servoValues[1] = limbSegments.size() > 1 ? limbSegments[1].GetServoAngle() : 0;
    servoValues[2] = limbSegments.size() > 2 ? limbSegments[2].GetServoAngle() : 0;
}

// Activate limb
void RoboticLimb::activate() {
    activated = true;
    Serial.println("Robotic limb activated.");
}

// Deactivate limb
void RoboticLimb::deactivate() {
    activated = false;
    Serial.println("Robotic limb deactivated.");
}

// Check if activated
bool RoboticLimb::isActivated() const {
    return activated;
}

// Convert radians to degrees
float RoboticLimb::RadToDegree(float rad) {
    return rad * (180.0f / M_PI);
}

// Placeholder: not yet implemented
void RoboticLimb::CalculateIK() {
    // Possibly use default target or previous input
}

// Perform simple IK calculation
void RoboticLimb::CalculateIK(double xPos, double yPos) {
    if (limbSegments.size() < 3) return;

    double distance = std::sqrt(xPos * xPos + yPos * yPos);

    float length1 = limbSegments[1].GetLength();
    float length2 = limbSegments[2].GetLength();

    float angle1 = 0.0f;
    float angle2 = 0.0f;

    if (distance > length1 + length2) {
        angle1 = 0.0f;
        angle2 = 0.0f;
    } else {
        double cosAngle2 = (distance * distance - length1 * length1 - length2 * length2) / (2.0 * length1 * length2);
        double sinAngle2 = std::sqrt(1.0 - cosAngle2 * cosAngle2);
        angle2 = std::atan2(sinAngle2, cosAngle2);

        double alpha = std::atan2(yPos, xPos);
        double beta = std::acos((distance * distance + length1 * length1 - length2 * length2) / (2.0 * distance * length1));
        angle1 = alpha - beta;
    }

    int deg1 = static_cast<int>(RadToDegree(angle1));
    int deg2 = static_cast<int>(RadToDegree(angle2));

    SetLimbServos(0, deg1, deg2);
}
