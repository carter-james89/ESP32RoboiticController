#ifndef DIGITALSERVO_H
#define DIGITALSERVO_H

#include <ESP32Servo.h>

  class DigitalServoConfiguration{
    public:
    int pin;
     int angleOffset;
     int pwmOffset;
      int minPWM;
       int maxPWM;
        int minAngleLimit;
        int maxAngleLimit;
          bool flip;
          };

class DigitalServo {
public:


          DigitalServo();

    DigitalServo(DigitalServoConfiguration buildData);
    void writeMicroseconds(int value);
    void SetAngle(int position);
    void Update();
    int GetAngle();

private:
DigitalServoConfiguration configData;
int _angle;
    Servo _servo;
       int _minPWM;
    void attach();
    void detach();

    int Map(int x, int in_min, int in_max, int out_min, int out_max) ;
};

#endif // DIGITALSERVO_H


// #ifndef DigitalServo_h
// #define DigitalServo_h

// #include "Arduino.h" 
// #include <ESP32Servo.h>

// class DigitalServo 
// {
// private :
//   int _servoNumber;
//   int _servoChannel;
//   int _maxPWM;
//   int _minPWM;
//       int _homePWM;
//       int _maxRange;
//   int _minAngleLimit;
// int _maxAngleLimit;
// bool _flip;
// //static int _servoChannel;


// public : 
//   DigitalServo(int servoNumber, int servoChannel, int homePWM, int minPWM, int MaxPWM, int servoRange, int minAngle, int maxAngle,  bool flip);
//   void SetPosition(float angle);

// };
// #endif