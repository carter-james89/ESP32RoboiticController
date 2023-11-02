#ifndef DigitalServo_h
#define DigitalServo_h

#include "Arduino.h" 

class DigitalServo 
{
private :
  int _servoNumber;
  int _servoChannel;
  int _maxPWM;
  int _minPWM;
      int _homePWM;
      int _maxRange;
  int _minAngleLimit;
int _maxAngleLimit;
bool _flip;
//static int _servoChannel;


public : 
  DigitalServo(int servoNumber, int servoChannel, int homePWM, int minPWM, int MaxPWM, int servoRange, int minAngle, int maxAngle,  bool flip);
  void SetPosition(float angle);

};
#endif