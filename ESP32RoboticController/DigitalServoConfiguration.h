#ifndef DIGITALSERVOCONFIGURATION_H
#define DIGITALSERVOCONFIGURATION_H

class DigitalServoConfiguration {
public:
    int pin;
    int angleOffset;
    int pwmOffset;
    int minPWM;
    int maxPWM;
    int minAngleLimit;
    int maxAngleLimit;
    bool flip;

    // Constructors
    DigitalServoConfiguration();
    DigitalServoConfiguration(int pin, int angleOffset, int pwmOffset, int minPWM, int maxPWM, int minAngleLimit, int maxAngleLimit, bool flip);

    // Copy constructor and assignment operator
    DigitalServoConfiguration(const DigitalServoConfiguration& other);
    DigitalServoConfiguration& operator=(const DigitalServoConfiguration& other);
};

#endif // DIGITALSERVOCONFIGURATION_H
