#ifndef DIGITALSERVO_H
#define DIGITALSERVO_H

#include <ESP32Servo.h>

class DigitalServo {
public:
struct ServoBuildData {
  //  String Name;
    int pin;
    int angleOffset;
    int pwmOffset;
    int minPWM;
    int maxPWM;
    int minAngleLimit;
    int maxAngleLimit;
    bool flip;

       // Default constructor
    ServoBuildData() : pin(0), angleOffset(0), pwmOffset(0), minPWM(0), maxPWM(0), minAngleLimit(0), maxAngleLimit(0), flip(false) {}


        // Custom copy constructor
    ServoBuildData(const ServoBuildData& other)
        : pin(other.pin),
          angleOffset(other.angleOffset),
          pwmOffset(other.pwmOffset),
          minPWM(other.minPWM),
          maxPWM(other.maxPWM),
          minAngleLimit(other.minAngleLimit),
          maxAngleLimit(other.maxAngleLimit),
          flip(other.flip) {}

    // Assignment operator
    ServoBuildData& operator=(const ServoBuildData& other) {
        if (this != &other) {
            pin = other.pin;
            angleOffset = other.angleOffset;
            pwmOffset = other.pwmOffset;
            minPWM = other.minPWM;
            maxPWM = other.maxPWM;
            minAngleLimit = other.minAngleLimit;
            maxAngleLimit = other.maxAngleLimit;
            flip = other.flip;
        }
        return *this;
    }
};



          DigitalServo();
void Initialize();
    DigitalServo(String servoName, ServoBuildData buildData);
    void writeMicroseconds(int value);
    void SetAngle(int position);
    void Update();
    int GetAngle();

     DigitalServo(const DigitalServo& other);

private:
ServoBuildData configData;
int _angle;
bool _initialized;
    Servo _servo;
       int _minPWM;
    void attach();
    void detach();
String servoName;
int Pin;
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