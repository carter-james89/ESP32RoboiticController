#include "DigitalServo.h"


#include <iostream>

DigitalServo::DigitalServo(int pin, int angleOffset,int pwmOffset, int minPWM, int maxPWM, int minAngleLimit, int maxAngleLimit, bool flip)
    : _servoPin(pin), _angleOffset(angleOffset), _pwmOffset(pwmOffset),_minPulseWidth(minPWM), _maxPulseWidth(maxPWM), _minAngleLimit(minAngleLimit), _maxAngleLimit(maxAngleLimit), _flip(flip) {
    attach();
  //  writeMicroseconds(homePWM); // Set servo to home position on startup
  SetAngle(0);
}

void DigitalServo::attach() {
    // Allow allocation of all timers

    // Attach the servo to the specified pin with the min and max pulse widths
    _servo.setPeriodHertz(50); // Standard 50hz servo
    _servo.attach(_servoPin, _minPulseWidth, _maxPulseWidth);
}

void DigitalServo::detach() {
    _servo.detach();
}

void DigitalServo::writeMicroseconds(int value) {
    // Ensure the value is within the pulse width range
        std::cout << "pwm " << value << std::endl;
    value = constrain(value, _minPulseWidth, _maxPulseWidth);
    _servo.writeMicroseconds(value+_pwmOffset);
}

void DigitalServo::SetAngle(double angle) {

    std::cout << "angle " << angle << std::endl;
    angle += _angleOffset;
        float desiredAngle = constrain(angle, _minAngleLimit,_maxAngleLimit);


  int pwmValue = map(desiredAngle, -135, 135, _maxPulseWidth, _minPulseWidth);
  if(_flip)
  {
pwmValue = map(desiredAngle, 135, -135, _maxPulseWidth, _minPulseWidth);
  }
writeMicroseconds(pwmValue);
//     // Ensure the angle is within the servo's range
//     angle = constrain(angle, _minAngleLimit, _maxAngleLimit);

//     // Map the angle to a pulse width within the min and max range
//    // double range = _maxAngleLimit - _minAngleLimit;
//     double normalizedAngle = (angle - 135) / 270; // Normalize angle to 0.0 - 1.0

//     // Now map the normalized angle to the pulse width
//     int pulseWidth = _minPulseWidth + static_cast<int>(normalizedAngle * (_maxPulseWidth - _minPulseWidth));
//     writeMicroseconds(pulseWidth);
}





// #include "DigitalServo.h"
// #include <ESP32Servo.h>
// #include <iostream>

// //int DigitalServo::_servoChannel = 0;

// DigitalServo::DigitalServo(int servoNumber, int servoChannel, int homePWM, int minPWM, int maxPWM, int servoRange, int minAngleLimit,int maxAngleLimit,  bool flip)
// {
       
//   _servoNumber = servoNumber;
//   _servoChannel = servoChannel;
//  _homePWM = homePWM;
//  _maxRange = servoRange;
//   _maxPWM = maxPWM;
//   _minPWM = minPWM;// homePWM - (servoRange/2);
  
//   _maxAngleLimit = maxAngleLimit;
//   _minAngleLimit = minAngleLimit;
//   _flip = flip;

//       // Initialize the servo PWM properties
//     ledcSetup(0, 50, 16); // 50Hz for servo
//     ledcAttachPin(_servoNumber, _servoChannel);
//    // _servoChannel++;

//      std::cout << "Servo Configured !" << std::endl;
//      std::cout << "m_homePWM value: " << _homePWM << std::endl;


//  ledcWrite(0,  _homePWM);
// //SetPosition(m_homePWM);
// }

long Map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


// void DigitalServo::SetPosition(float angle) {
   
//    float desiredAngle = constrain(angle, _minAngleLimit,_maxAngleLimit);
//     std::cout << "Set servo to angle: " << desiredAngle << std::endl;
//    // std::cout << "Constrained angle: " << desiredAngle << std::endl;
//    // std::cout << "Mapping with minAngle: " << m_minAngle << ", maxAngle: " << m_maxAngle << ", minPWM: " << m_minPWM << ", maxPWM: " << m_maxPWM << std::endl;

//     int pwmValue = Map(static_cast<long>(desiredAngle), static_cast<long>(-(_maxRange/2)), static_cast<long>(_maxRange/2), static_cast<long>(_minPWM), static_cast<long>(_maxPWM));
//   //  std::cout << "PWM Value: " << pwmValue << std::endl;
//  std::cout <<_servoNumber << " : " <<_servoChannel << " Set servo PWM " << pwmValue << std::endl;
//     // Write the PWM value to the servo
//   //  std::cout << "m_homePWM value: " << m_homePWM << std::endl;
//    // Serial.println(m_homePWM);
//     ledcWrite(_servoChannel,  pwmValue);

// }
// // void DigitalServo::SetPosition(float angle)
// // {
// //      std::cout << "Set servo to !" << std::endl;
// // float desiredAngle = constrain(angle, m_minAngle, m_maxAngle);
// //   int pwmValue;

// // //     if (m_flip) {
// // //         pwmValue = map(desiredAngle, m_minAngle, m_maxAngle, m_maxPWM, m_minPWM);
// // //     } else {
// //          pwmValue = Map(desiredAngle, m_minAngle, m_maxAngle, m_minPWM, m_maxPWM);
// // //     }
// //  //    std::cout << "PWMValue !" << std::endl;
// //  //         std::cout << pwmValue << std::endl;
// //  //std::cout << "PWM Value: " << pwmValue << std::endl;
// //     ledcWrite(0, 3000);
// // }