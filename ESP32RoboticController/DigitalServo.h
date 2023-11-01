#ifndef DigitalServo_h
#define DigitalServo_h

#include "Arduino.h" 

class DigitalServo 
{
private :
  int m_servoNumber;
  int m_maxPWM;
  int m_minPWM;
      uint32_t m_homePWM;
  int m_minAngle;
int m_maxAngle;
bool m_flip;

public : 
  DigitalServo(int servoNumber, int homePWM, int minAngle, int maxAngle,  bool flip);
  void SetPosition(float angle);

};
#endif