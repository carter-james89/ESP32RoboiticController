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

void DigitalServo::Update()//called every esp32 loop
{

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

}

long Map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

