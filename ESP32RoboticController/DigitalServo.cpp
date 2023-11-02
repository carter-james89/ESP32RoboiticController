
#include "DigitalServo.h"

#include <iostream>

//int DigitalServo::_servoChannel = 0;

DigitalServo::DigitalServo(int servoNumber, int servoChannel, int homePWM, int minPWM, int maxPWM, int servoRange, int minAngleLimit,int maxAngleLimit,  bool flip)
{
       
  _servoNumber = servoNumber;
  _servoChannel = servoChannel;
 _homePWM = homePWM;
 _maxRange = servoRange;
  _maxPWM = maxPWM;
  _minPWM = minPWM;// homePWM - (servoRange/2);
  
  _maxAngleLimit = maxAngleLimit;
  _minAngleLimit = minAngleLimit;
  _flip = flip;

      // Initialize the servo PWM properties
    ledcSetup(0, 50, 16); // 50Hz for servo
    ledcAttachPin(_servoNumber, _servoChannel);
   // _servoChannel++;

     std::cout << "Servo Configured !" << std::endl;
     std::cout << "m_homePWM value: " << _homePWM << std::endl;


 ledcWrite(0,  _homePWM);
//SetPosition(m_homePWM);
}

long Map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void DigitalServo::SetPosition(float angle) {
   
   float desiredAngle = constrain(angle, _minAngleLimit,_maxAngleLimit);
    std::cout << "Set servo to angle: " << desiredAngle << std::endl;
   // std::cout << "Constrained angle: " << desiredAngle << std::endl;
   // std::cout << "Mapping with minAngle: " << m_minAngle << ", maxAngle: " << m_maxAngle << ", minPWM: " << m_minPWM << ", maxPWM: " << m_maxPWM << std::endl;

    int pwmValue = Map(static_cast<long>(desiredAngle), static_cast<long>(-(_maxRange/2)), static_cast<long>(_maxRange/2), static_cast<long>(_minPWM), static_cast<long>(_maxPWM));
  //  std::cout << "PWM Value: " << pwmValue << std::endl;
 std::cout <<_servoNumber << " : " <<_servoChannel << " Set servo PWM " << pwmValue << std::endl;
    // Write the PWM value to the servo
  //  std::cout << "m_homePWM value: " << m_homePWM << std::endl;
   // Serial.println(m_homePWM);
    ledcWrite(_servoChannel,  pwmValue);

}
// void DigitalServo::SetPosition(float angle)
// {
//      std::cout << "Set servo to !" << std::endl;
// float desiredAngle = constrain(angle, m_minAngle, m_maxAngle);
//   int pwmValue;

// //     if (m_flip) {
// //         pwmValue = map(desiredAngle, m_minAngle, m_maxAngle, m_maxPWM, m_minPWM);
// //     } else {
//          pwmValue = Map(desiredAngle, m_minAngle, m_maxAngle, m_minPWM, m_maxPWM);
// //     }
//  //    std::cout << "PWMValue !" << std::endl;
//  //         std::cout << pwmValue << std::endl;
//  //std::cout << "PWM Value: " << pwmValue << std::endl;
//     ledcWrite(0, 3000);
// }