#include "BittleQuadrupedConfiguration.h"
#include "LimbSegment.h"
#include "DigitalServo.h"
#include <vector>

BittleQuadrupedConfiguration::BittleQuadrupedConfiguration() {
    // Initialize your BittleQuadrupedConfiguration object here if needed
}

std::vector<QuadrupedLimbData*> BittleQuadrupedConfiguration::GetLimbData() {
    Serial.println("Build Bittle Data");

    // Dynamically allocate DigitalServoConfiguration objects
    auto flBaseConfig = new DigitalServoConfiguration(); // Populate with appropriate values for FL Base
    auto flHipConfig = new DigitalServoConfiguration(33, -45, 0, 500, 2500, 134, -134, false);
    auto flKneeConfig = new DigitalServoConfiguration(19, -45, 0, 500, 2500, 135, -135, false);

    auto frBaseConfig = new DigitalServoConfiguration(); // Populate with appropriate values for FR Base
    auto frHipConfig = new DigitalServoConfiguration(5, -45, 0, 500, 2500, 135, -135, true);
    auto frKneeConfig = new DigitalServoConfiguration(4, -45, 0, 500, 2500, 135, -135, false);

    auto brBaseConfig = new DigitalServoConfiguration(); // Populate with appropriate values for BR Base
    auto brHipConfig = new DigitalServoConfiguration(15, -45, 80, 500, 2500, 135, -135, false);
    auto brKneeConfig = new DigitalServoConfiguration(2, -45, 0, 500, 2500, 135, -135, false);

    auto blBaseConfig = new DigitalServoConfiguration(); // Populate with appropriate values for BL Base
    auto blHipConfig = new DigitalServoConfiguration(14, -45, 20, 500, 2500, 135, -135, true);
    auto blKneeConfig = new DigitalServoConfiguration(27, -45, 80, 500, 2500, 135, -135, true);

    // Create and allocate LimbSegmentData for each limb
    std::vector<LimbSegmentData*> flSegments{
        new LimbSegmentData(1, *flBaseConfig),
        new LimbSegmentData(1, *flHipConfig),
        new LimbSegmentData(1, *flKneeConfig)
    };
    auto flLimbData = new QuadrupedLimbData(flSegments);

    std::vector<LimbSegmentData*> frSegments{
        new LimbSegmentData(1, *frBaseConfig),
        new LimbSegmentData(1, *frHipConfig),
        new LimbSegmentData(1, *frKneeConfig)
    };
    auto frLimbData = new QuadrupedLimbData(frSegments);

    std::vector<LimbSegmentData*> brSegments{
        new LimbSegmentData(1, *brBaseConfig),
        new LimbSegmentData(1, *brHipConfig),
        new LimbSegmentData(1, *brKneeConfig)
    };
    auto brLimbData = new QuadrupedLimbData(brSegments);

    std::vector<LimbSegmentData*> blSegments{
        new LimbSegmentData(1, *blBaseConfig),
        new LimbSegmentData(1, *blHipConfig),
        new LimbSegmentData(1, *blKneeConfig)
    };
    auto blLimbData = new QuadrupedLimbData(blSegments);

    // Add all limb data pointers to the vector
    std::vector<QuadrupedLimbData*> limbs = {flLimbData, frLimbData, brLimbData, blLimbData};

    // Clean up DigitalServoConfiguration objects
    servoConfigs.push_back(flBaseConfig);
    servoConfigs.push_back(flHipConfig);
    servoConfigs.push_back(flKneeConfig);
    servoConfigs.push_back(frBaseConfig);
    servoConfigs.push_back(frHipConfig);
    servoConfigs.push_back(frKneeConfig);
    servoConfigs.push_back(brBaseConfig);
    servoConfigs.push_back(brHipConfig);
    servoConfigs.push_back(brKneeConfig);
    servoConfigs.push_back(blBaseConfig);
    servoConfigs.push_back(blHipConfig);
    servoConfigs.push_back(blKneeConfig);

     for (auto segment : flSegments) segmentData.push_back(segment);
    for (auto segment : frSegments) segmentData.push_back(segment);
      for (auto segment : brSegments) segmentData.push_back(segment);
        for (auto segment : blSegments) segmentData.push_back(segment);

 limbData.push_back(flLimbData);
    limbData.push_back(frLimbData);
    limbData.push_back(brLimbData);
    limbData.push_back(blLimbData);


    return limbs;
}
void BittleQuadrupedConfiguration::OnConstructionComplete() {
    // Delete QuadrupedLimbData objects
    for (auto limb : limbData) {
        delete limb;
    }
    limbData.clear();

    // Delete LimbSegmentData objects
    for (auto segment : segmentData) {
        delete segment;
    }
    segmentData.clear();

    // Delete DigitalServoConfiguration objects
    for (auto config : servoConfigs) {
        delete config;
    }
    servoConfigs.clear();
}