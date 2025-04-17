// DigitalServo.h
#pragma once

#include <ESP32Servo.h>
#include <string>

/**
 * @struct ServoBuildData
 * @brief Configuration parameters for a PWM-controlled servo.
 */
struct ServoBuildData {
    uint8_t pin = 0;              ///< GPIO pin number.
    float   angleOffset = 0.0f;   ///< Mechanical zero offset (degrees).
    float   pwmOffset = 0.0f;     ///< Additional PWM offset (µs).
    int     minPWM = 500;         ///< Min pulse width (µs).
    int     maxPWM = 2500;        ///< Max pulse width (µs).
    int     minAngleLimit = -135; ///< Min allowed angle (degrees).
    int     maxAngleLimit = 135;  ///< Max allowed angle (degrees).
    bool    flip = false;         ///< Reverse movement direction.
};

/**
 * @class DigitalServo
 * @brief Wraps ESP32Servo for safe, configurable servo control on ESP32.
 */
class DigitalServo {
public:
    /**
     * @brief Default-constructs an uninitialized servo.
     */
    DigitalServo() = default;

    /**
     * @brief Constructs and configures a servo instance.
     * @param name Informative name for debugging.
     * @param config Build parameters for servo operation.
     */
    DigitalServo(const std::string& name, const ServoBuildData& config);

    DigitalServo(const DigitalServo&) = delete;            ///< non-copyable
    DigitalServo& operator=(const DigitalServo&) = delete; ///< non-assignable

    ~DigitalServo(); ///< Detaches if initialized

    /**
     * @brief Initializes hardware and attaches PWM channel.
     */
    void initialize();

    /**
     * @brief Set servo to target angle (degrees).
     * @param angle Desired angle.
     */
    void setAngle(int angle);

    /**
     * @brief Retrieve the last commanded angle.
     * @return Current commanded angle.
     */
    int getAngle() const noexcept;

    /**
     * @brief Periodic update hook (optional).
     */
    void update();

private:
    void attach();
    void detach();
    void writeMicroseconds(int us);
    static int mapValue(int x, int in_min, int in_max, int out_min, int out_max);

    std::string   name_;          ///< Debug name
    ServoBuildData config_;       ///< Build-time parameters
    Servo         servo_;         ///< Underlying servo object
    bool          initialized_{}; ///< True after attach()
    int           currentAngle_{};///< Last commanded angle
};