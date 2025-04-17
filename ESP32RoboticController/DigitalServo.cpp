
// DigitalServo.cpp
#include "DigitalServo.h"
#include <Arduino.h>

DigitalServo::DigitalServo(const std::string& name, const ServoBuildData& config)
    : name_(name), config_(config) {}

DigitalServo::~DigitalServo() {
    if (initialized_) detach();
}

void DigitalServo::initialize() {
    if (initialized_) {
        Serial.printf("Servo '%s' already initialized\n", name_.c_str());
        return;
    }
    attach();
    initialized_ = true;
}

void DigitalServo::attach() {
    servo_.setPeriodHertz(50);
    servo_.attach(config_.pin, config_.minPWM, config_.maxPWM);
}

void DigitalServo::detach() {
    servo_.detach();
    initialized_ = false;
}

void DigitalServo::setAngle(int angle) {
    if (!initialized_) initialize();
    currentAngle_ = angle;

    int adjusted = angle + static_cast<int>(config_.angleOffset);
    adjusted = constrain(adjusted, config_.minAngleLimit, config_.maxAngleLimit);

    int pwm = mapValue(
        config_.flip ? -adjusted : adjusted,
        config_.minAngleLimit, config_.maxAngleLimit,
        config_.minPWM, config_.maxPWM
    );
    pwm += static_cast<int>(config_.pwmOffset);

    writeMicroseconds(pwm);
}

int DigitalServo::getAngle() const noexcept {
    return currentAngle_;
}

void DigitalServo::update() {
    // Empty by default; hook for future extensions
}

void DigitalServo::writeMicroseconds(int us) {
    us = constrain(us, config_.minPWM, config_.maxPWM);
    servo_.writeMicroseconds(us);
}

int DigitalServo::mapValue(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
