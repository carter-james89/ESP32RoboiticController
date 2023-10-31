#ifndef DigitalServo_h
#define DigitalServo_h

#include "Arduino.h" 

class DigitalServo 
{
private :
  int m_servoNumber;
  int m_maxPWM;
  int m_minPWM;
  int m_homePWM;
  int m_minAngle;
int m_maxAngle;
bool m_flip;

public : 
  DigitalServo(int servoNumber, int homePWM, int range, int minAngle, int maxAngle,  bool flip);
  void SetDigitalServo(float angle);

};
#endif