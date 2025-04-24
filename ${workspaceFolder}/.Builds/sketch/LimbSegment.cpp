#line 1 "C:\\Users\\carte\\Projects\\Robotics\\Quadruped\\ESP32 Robotic Controller\\ESP32RoboticController\\LimbSegment.cpp"
#include "LimbSegment.h"
#include <Arduino.h>

LimbSegment::LimbSegment(const String& name)
    : isActive(true), _initialized(false), _length(0.0), _name(name), _servo() {}

LimbSegment::LimbSegment(const String& name, float length, const DigitalServo& servo)
    : isActive(true), _initialized(false), _length(length), _name(name), _servo(servo) {}

LimbSegment::LimbSegment(const LimbSegment& other)
    : isActive(other.isActive),
      _initialized(false), // copied segments must re-init themselves
      _length(other._length),
      _name(other._name),
      _servo(other._servo) {}

LimbSegment::~LimbSegment() = default;

void LimbSegment::Initialize() {
    if (_initialized) {
        Serial.print("Segment already initialized: ");
        Serial.println(_name);
        return;
    }

    Serial.print("Initializing segment: ");
    Serial.println(_name);

    _initialized = true;
    _servo.Initialize();
}

void LimbSegment::SetServoAngle(int newAngle) {
    _servo.SetAngle(newAngle);
}

int LimbSegment::GetServoAngle() const {
    return _servo.GetAngle();
}

double LimbSegment::GetLength() const {
    return _length;
}

void LimbSegment::activate() {
    isActive = true;
}

void LimbSegment::deactivate() {
    isActive = false;
}
