// BittleQuadrupedConstructor.cpp

#include "BittleQuadrupedConstructor.h"
#include "DigitalServo.h"    // brings in top‑level ServoBuildData
#include <string>

/**
 * @brief Helper to build a ServoBuildData struct.
 */
ServoBuildData BittleQuadrupedConstructor::MakeServoConfig(
    uint8_t pin,
    int     angleOffset,
    bool    flip
) {
    return {
        /* pin */           pin,
        /* angleOffset */   static_cast<float>(angleOffset),
        /* pwmOffset */     0.0f,
        /* minPWM */        500,
        /* maxPWM */        2500,
        /* minAngleLimit */ -134,
        /* maxAngleLimit */ 134,
        /* flip */          flip
    };
}

/**
 * @brief Populate the provided vector with fully configured limbs.
 */
void BittleQuadrupedConstructor::GetLimbs(std::vector<RoboticLimb>& limbs) const {
    limbs.clear();
    limbs.reserve(4);

    for (const auto& cfg : kLegConfigs) {
        // Now returns the global ServoBuildData, not DigitalServo::ServoBuildData
        auto hipCfg  = MakeServoConfig(cfg.hipPin,  cfg.hipAngleOffset, cfg.hipFlip);
        auto kneeCfg = MakeServoConfig(cfg.kneePin, cfg.kneeAngleOffset, cfg.kneeFlip);

        std::vector<LimbSegment> segments;
        segments.reserve(3);

        // Perform proper concatenation by converting cfg.name to std::string
        segments.emplace_back(std::string(cfg.name) + " Base (Disabled)");
        segments.emplace_back(
            std::string(cfg.name) + " Hip",
            1,
            DigitalServo(std::string(cfg.name) + " Hip", hipCfg)
        );
        segments.emplace_back(
            std::string(cfg.name) + " Knee",
            1,
            DigitalServo(std::string(cfg.name) + " Knee", kneeCfg)
        );

        limbs.emplace_back(
            std::string(cfg.name) + " Limb",
            std::move(segments)
        );
    }
}
