// BittleQuadrupedConstructor.h
#ifndef BITTLE_QUADRUPED_CONSTRUCTOR_H
#define BITTLE_QUADRUPED_CONSTRUCTOR_H

#include <vector>
#include <string>
#include "RoboticLimb.h"

/**
 * @class BittleQuadrupedConstructor
 * @brief Factory to construct and configure the four-legged robot's limbs.
 */
class BittleQuadrupedConstructor {
public:
    BittleQuadrupedConstructor() = default;
    ~BittleQuadrupedConstructor() = default;
    BittleQuadrupedConstructor(const BittleQuadrupedConstructor&) = delete;
    BittleQuadrupedConstructor& operator=(const BittleQuadrupedConstructor&) = delete;

    /**
     * @brief Populate the provided vector with fully configured limbs.
     * @param[out] limbs Receives the list of RoboticLimb instances.
     */
    void GetLimbs(std::vector<RoboticLimb>& limbs) const;

private:

// In BittleQuadrupedConstructor.h

struct LegConfig {
  const char* name;        // was std::string
  uint8_t    hipPin;
  int        hipAngleOffset;
  bool       hipFlip;
  uint8_t    kneePin;
  int        kneeAngleOffset;
  bool       kneeFlip;
};

// Now this is a literal type (all fields are literal), so constexpr works:
static constexpr LegConfig kLegConfigs[4] = {
  { "FL", 33, 53, false, 19, 43, true  },
  { "FR",  5, 45, true,  4, 45, false },
  { "BR", 15, -55, true, 2, 45, false },
  { "BL", 14, -42, false,27, 35, true  },
};


    /**
     * @brief Helper to create a standard ServoBuildData struct.
     * @param pin GPIO pin number.
     * @param angleOffset Mechanical zero offset.
     * @param flip Direction reversal flag.
     */
    static ServoBuildData MakeServoConfig(uint8_t pin,
      int     angleOffset,
      bool    flip);
};

#endif // BITTLE_QUADRUPED_CONSTRUCTOR_H