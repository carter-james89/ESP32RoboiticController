#ifndef ROBOTICLIMB_H
#define ROBOTICLIMB_H

#include "LimbSegment.h"
#include <vector>

class RoboticLimb {
public:
    explicit RoboticLimb();
    explicit RoboticLimb(const String& name, const std::vector<LimbSegment>& limbSegments);
    ~RoboticLimb();

    void Initialize();
    void activate();
    void deactivate();
    bool isActivated() const;

    void CalculateIK();
    void CalculateIK(double xPos, double yPos);
    void SetLimbServos(int baseAngle, int hipAngle, int kneeAngle);
    void SerializeLimbData(std::vector<std::uint8_t>& message);
    void GetServoValues(int servoValues[3]);

private:
    float RadToDegree(float rad);  // ✅ declared properly here

    bool activated = true;
    bool _initialized = false;
    String _name;
    std::vector<LimbSegment> limbSegments;
};

#endif // ROBOTICLIMB_H
