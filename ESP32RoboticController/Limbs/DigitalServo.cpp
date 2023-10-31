
#include "DigitalServo.h"

DigitalServo::DigitalServo(int servoNumber, int homePWM, int servoRange, int minAngle,int maxAngle,  bool flip)
{
  m_servoNumber = servoNumber;
  m_homePWM = homePWM;
  m_maxPWM = 580;// homePWM + (servoRange/2);
  m_minPWM = 120;// homePWM - (servoRange/2);
  m_maxAngle = maxAngle;
  m_minAngle = minAngle;
  m_flip = flip;

      // Initialize the servo PWM properties
//    ledcSetup(m_servoNumber, 50, 16); // 50Hz for servo
  //  ledcAttachPin(m_servoNumber, m_servoNumber);
}

void DigitalServo::SetDigitalServo(float angle)
{
float desiredAngle = constrain(angle, m_minAngle, m_maxAngle);
 int pwmValue;

    if (m_flip) {
        pwmValue = map(desiredAngle, m_minAngle, m_maxAngle, m_maxPWM, m_minPWM);
    } else {
        pwmValue = map(desiredAngle, m_minAngle, m_maxAngle, m_minPWM, m_maxPWM);
    }

    ledcWrite(m_servoNumber, pwmValue);
}