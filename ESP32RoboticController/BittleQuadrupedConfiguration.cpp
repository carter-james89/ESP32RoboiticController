#include "BittleQuadrupedConfiguration.h"
#include "LimbSegment.h"
#include "DigitalServo.h"
#include <vector>

BittleQuadrupedConfiguration::BittleQuadrupedConfiguration() {
    // Initialize your BittleQuadrupedConfiguration object here if needed
}

std::vector<QuadrupedLimbData> BittleQuadrupedConfiguration::GetLimbData() {
    Serial.println("Build Bittle Data");
    // FL Limb Servo Configurations
    DigitalServoConfiguration flBaseConfig; // Populate with appropriate values for FL Base
    DigitalServoConfiguration flHipConfig = {33, -45, 0, 500, 2500, 134, -134, false};
    DigitalServoConfiguration flKneeConfig = {19, -45, 0, 500, 2500, 135, -135, false};

    // FR Limb Servo Configurations
    DigitalServoConfiguration frBaseConfig; // Populate with appropriate values for FR Base
    DigitalServoConfiguration frHipConfig = {5, -45, 0, 500, 2500, 135, -135, true};
    DigitalServoConfiguration frKneeConfig = {4, -45, 0, 500, 2500, 135, -135, false};

    // BR Limb Servo Configurations
    DigitalServoConfiguration brBaseConfig; // Populate with appropriate values for BR Base
    DigitalServoConfiguration brHipConfig = {15, -45, 80, 500, 2500, 135, -135, false};
    DigitalServoConfiguration brKneeConfig = {2, -45, 0, 500, 2500, 135, -135, false};

    // BL Limb Servo Configurations
    DigitalServoConfiguration blBaseConfig; // Populate with appropriate values for BL Base
    DigitalServoConfiguration blHipConfig = {14, -45, 20, 500, 2500, 135, -135, true};
    DigitalServoConfiguration blKneeConfig = {27, -45, 80, 500, 2500, 135, -135, true};

    // Create LimbSegmentData for each limb
    std::vector<LimbSegmentData> flSegments = {
        LimbSegmentData(1, flBaseConfig),
        LimbSegmentData(1, flHipConfig),
        LimbSegmentData(1, flKneeConfig)
    };
    QuadrupedLimbData flLimbData(flSegments);

    std::vector<LimbSegmentData> frSegments = {
        LimbSegmentData(1, frBaseConfig),
        LimbSegmentData(1, frHipConfig),
        LimbSegmentData(1, frKneeConfig)
    };
    QuadrupedLimbData frLimbData(frSegments);

    std::vector<LimbSegmentData> brSegments = {
        LimbSegmentData(1, brBaseConfig),
        LimbSegmentData(1, brHipConfig),
        LimbSegmentData(1, brKneeConfig)
    };
    QuadrupedLimbData brLimbData(brSegments);

    std::vector<LimbSegmentData> blSegments = {
        LimbSegmentData(1, blBaseConfig),
        LimbSegmentData(1, blHipConfig),
        LimbSegmentData(1, blKneeConfig)
    };
    QuadrupedLimbData blLimbData(blSegments);

    // Add all limb data to the vector
    std::vector<QuadrupedLimbData> limbs = {flLimbData, frLimbData, brLimbData, blLimbData};

    return limbs;
}
