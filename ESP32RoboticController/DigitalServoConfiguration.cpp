#include "DigitalServoConfiguration.h"

// Default constructor
DigitalServoConfiguration::DigitalServoConfiguration()
    : pin(1), angleOffset(0), pwmOffset(0), minPWM(0), maxPWM(0), minAngleLimit(0), maxAngleLimit(0), flip(false) {
}

// Parameterized constructor
DigitalServoConfiguration::DigitalServoConfiguration(int pin, int angleOffset, int pwmOffset, int minPWM, int maxPWM, int minAngleLimit, int maxAngleLimit, bool flip)
    : pin(pin), angleOffset(angleOffset), pwmOffset(pwmOffset), minPWM(minPWM), maxPWM(maxPWM), minAngleLimit(minAngleLimit), maxAngleLimit(maxAngleLimit), flip(flip) {
}

// Copy constructor
DigitalServoConfiguration::DigitalServoConfiguration(const DigitalServoConfiguration& other)
    : pin(other.pin), angleOffset(other.angleOffset), pwmOffset(other.pwmOffset), minPWM(other.minPWM), maxPWM(other.maxPWM), minAngleLimit(other.minAngleLimit), maxAngleLimit(other.maxAngleLimit), flip(other.flip) {
}

// Assignment operator
DigitalServoConfiguration& DigitalServoConfiguration::operator=(const DigitalServoConfiguration& other) {
    if (this != &other) {
        pin = other.pin;
        angleOffset = other.angleOffset;
        pwmOffset = other.pwmOffset;
        minPWM = other.minPWM;
        maxPWM = other.maxPWM;
        minAngleLimit = other.minAngleLimit;
        maxAngleLimit = other.maxAngleLimit;
        flip = other.flip;
    }
    return *this;
}
