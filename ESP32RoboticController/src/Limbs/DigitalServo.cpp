#include "DigitalServo.h"
#include <Arduino.h>

// Default constructor
DigitalServo::DigitalServo()
    : configData(), _angle(0), _initialized(false), attached(false), servoName("") {}

// Named constructor
DigitalServo::DigitalServo(const String& name, const ServoBuildData& buildData)
    : configData(buildData),
      _angle(0),
      _initialized(false),
      attached(false),
      servoName(name) {}

      DigitalServo::DigitalServo(const DigitalServo& other)
    : configData(other.configData),
      _angle(other._angle),
      _initialized(false),
      attached(false),
      servoName(other.servoName) {
    // Do NOT copy _servo directly — re-attach in Initialize if needed
}



// Initialize and attach the servo (only once)
void DigitalServo::Initialize() {
    if (_initialized) {
        Serial.print(F("Servo already initialized: "));
        Serial.println(servoName);
        return;
    }
    Serial.print(F("Initializing servo: "));
    Serial.println(servoName);
    _initialized = true;
    attach();
}

// Attach servo to pin with configured pulse widths
void DigitalServo::attach() {
    if (attached) return;
    _servo.setPeriodHertz(50);  // Standard 50 Hz
    _servo.attach(configData.pin, configData.minPWM, configData.maxPWM);
    attached = true;
}

// Detach servo
void DigitalServo::detach() {
    if (!attached) return;
    _servo.detach();
    attached = false;
}

// Hook for per‑loop updates (unused for now)
void DigitalServo::Update() {
    // No periodic update logic yet
}

// Write a raw microsecond pulse to the servo
void DigitalServo::writeMicroseconds(int value) {
    value = constrain(value, configData.minPWM, configData.maxPWM);
    _servo.writeMicroseconds(value);
}

// Return the last set angle (degrees)
int DigitalServo::GetAngle() const {
    return _angle;
}

// Set a new target angle, applying offset, limits, mapping, and flip
void DigitalServo::SetAngle(int angle) {
    if (!attached) attach();

    _angle = angle;
    int adjusted = angle + configData.angleOffset;
    adjusted = constrain(adjusted, configData.minAngleLimit, configData.maxAngleLimit);

    int pwm = Map(
        adjusted,
        -configData.maxAngleLimit, configData.maxAngleLimit,
         configData.minPWM,         configData.maxPWM
    );

    if (configData.flip) {
        pwm = Map(
            -adjusted,
            -configData.maxAngleLimit, configData.maxAngleLimit,
             configData.minPWM,         configData.maxPWM
        );
    }

    writeMicroseconds(pwm);
}

// Simple linear mapping helper
int DigitalServo::Map(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
