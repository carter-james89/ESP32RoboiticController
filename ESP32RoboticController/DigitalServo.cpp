#include "DigitalServo.h"
#include <iostream>

DigitalServo:: DigitalServo(DigitalServoConfiguration configData)
    : configData(configData) {
    attach();
  //  writeMicroseconds(homePWM); // Set servo to home position on startup
  SetAngle(0);
}

void DigitalServo::attach() {
    // Allow allocation of all timers

    // Attach the servo to the specified pin with the min and max pulse widths
    _servo.setPeriodHertz(50); // Standard 50hz servo
    _servo.attach(configData.pin, configData.minPWM, configData.maxPWM);
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
    value = constrain(value, configData.minPWM, configData.maxPWM);
    _servo.writeMicroseconds(value+configData.pwmOffset);
}

int DigitalServo::GetAngle() {
     Serial.print("Angle at Servo : " + _angle);
    return _angle;
}

void DigitalServo::SetAngle(int angle) {

    std::cout << "angle " << angle << std::endl;
    _angle = angle;
    angle += configData.angleOffset;
        float desiredAngle = constrain(angle, configData.minAngleLimit,configData.maxAngleLimit);


  int pwmValue = map(desiredAngle, -135, 135, configData.maxPWM, configData.minPWM);
  if(configData.flip)
  {
pwmValue = map(desiredAngle, 135, -135, configData.maxPWM, configData.minPWM);
  }
writeMicroseconds(pwmValue);

}

long Map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

