
#include "DigitalServo.h"

#include <iostream>

DigitalServo::DigitalServo(int servoNumber, int homePWM, int minAngle,int maxAngle,  bool flip)
{
       
  m_servoNumber = 19;
 
  m_maxPWM = 2500;
  m_minPWM = 500;// homePWM - (servoRange/2);
   m_homePWM = (m_maxPWM + m_minPWM)/2;
  m_maxAngle = 90;
  m_minAngle = -90;
  m_flip = flip;

      // Initialize the servo PWM properties
    ledcSetup(0, 50, 16); // 50Hz for servo
    ledcAttachPin(m_servoNumber, 0);

     std::cout << "Servo Configured !" << std::endl;
     std::cout << "m_homePWM value: " << m_homePWM << std::endl;


 ledcWrite(0,  m_homePWM);
//SetPosition(m_homePWM);
}

long Map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void DigitalServo::SetPosition(float angle) {
    std::cout << "Set servo to angle: " << angle << std::endl;
   float desiredAngle = constrain(angle, m_minAngle, m_maxAngle);
   // std::cout << "Constrained angle: " << desiredAngle << std::endl;
   // std::cout << "Mapping with minAngle: " << m_minAngle << ", maxAngle: " << m_maxAngle << ", minPWM: " << m_minPWM << ", maxPWM: " << m_maxPWM << std::endl;

    int pwmValue = Map(static_cast<long>(angle), static_cast<long>(m_minAngle), static_cast<long>(m_maxAngle), static_cast<long>(m_minPWM), static_cast<long>(m_maxPWM));
  //  std::cout << "PWM Value: " << pwmValue << std::endl;

    // Write the PWM value to the servo
  //  std::cout << "m_homePWM value: " << m_homePWM << std::endl;
   // Serial.println(m_homePWM);
    ledcWrite(0,  pwmValue);

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