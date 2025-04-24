#ifndef LIMBSEGMENT_H
#define LIMBSEGMENT_H

#include "DigitalServo.h"
#include <vector>

class LimbSegment {
public:
    explicit LimbSegment(const String& name);
    explicit LimbSegment(const String& name, float length, const DigitalServo& servo);
    LimbSegment(const LimbSegment& other);
    ~LimbSegment();

    void Initialize();

    void activate();
    void deactivate();

    double GetLength() const;
    int GetServoAngle() const;
    void SetServoAngle(int newAngle);

private:
    bool isActive = true;
    bool _initialized = false;
    double _length = 0.0;

    DigitalServo _servo;
    String _name;
};

#endif // LIMBSEGMENT_H
