#ifndef DIGITALSERVO_H
#define DIGITALSERVO_H

#include <ESP32Servo.h>

class DigitalServo {
public:
    struct ServoBuildData {
        int  pin            = 0;
        int  angleOffset    = 0;
        int  pwmOffset      = 0;
        int  minPWM         = 0;
        int  maxPWM         = 0;
        int  minAngleLimit  = 0;
        int  maxAngleLimit  = 0;
        bool flip           = false;

        ServoBuildData() = default;
        ServoBuildData(const ServoBuildData&) = default;
        ServoBuildData& operator=(const ServoBuildData&) = default;
    };

    DigitalServo();
    DigitalServo(String servoName, ServoBuildData buildData);
    DigitalServo::DigitalServo(const String& name, const ServoBuildData& buildData);
    DigitalServo(const DigitalServo& other);

    void Initialize();
    void writeMicroseconds(int value);
    void SetAngle(int position);
    void Update();
    int  GetAngle() const;

private:
    ServoBuildData configData;
    int            _angle;
    bool           _initialized;
    bool           attached;
    Servo          _servo;
    String         servoName;

    void attach();
    void detach();
    int  Map(int x, int in_min, int in_max, int out_min, int out_max);
};

#endif // DIGITALSERVO_H
