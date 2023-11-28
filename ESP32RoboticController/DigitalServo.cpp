
#include "BittleQuadrupedConstructor.h"
#include "DigitalServo.h"
DigitalServo::DigitalServo():_angle(0), _initialized(false),attached(false) {}

DigitalServo::DigitalServo(String servoNam, ServoBuildData buildData)
    : servoName(servoNam), configData(buildData), _angle(0), _initialized(false),attached(false) {

//servoPin(pin), _angleOffset(angleOffset), _pwmOffset(pwmOffset),_minPulseWidth(minPWM), _maxPulseWidth(maxPWM), _minAngleLimit(minAngleLimit), _maxAngleLimit(maxAngleLimit), _flip(flip),_angle(0)

 //Serial.print("servo ");
// Serial.println(buildData.pin);
 //Pin = configData.pin;
   // this->Pin = buildData.pin;
 //attach();
  //  writeMicroseconds(homePWM); // Set servo to home position on startup
  //SetAngle(0);
}
// Implementation of the copy constructor
DigitalServo::DigitalServo(const DigitalServo& other)
    : configData(other.configData), _angle(other._angle), _initialized(false), servoName(other.servoName),attached(false) {
    // Since Servo class might not be copyable (depends on its implementation), we reattach it
    // if (other.attached) {
    //     _servo.attach(configData.pin, configData.minPWM, configData.maxPWM);
    // }
}

void DigitalServo::Initialize(){
    if(_initialized){
        Serial.print("This servo has already been initialized");
        Serial.println(servoName);
        return;
    }
     Serial.print("Initialize Servo at pin : ");
      Serial.println(servoName);
     Serial1.print(configData.pin);
    _initialized = true;
  attach();
}

void DigitalServo::attach() {
    // Allow allocation of all timers

//Serial.println(configData.maxPWM);
//Serial.print( "Attach servo : ");
//Serial.println(configData.pin);
attached = true;
    // Attach the servo to the specified pin with the min and max pulse widths
   _servo.setPeriodHertz(50); // Standard 50hz servo
  // delay(1000);
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
       // std::cout << "pwm " << value << std::endl;
       //Serial.println(value);
     
    value = constrain(value, configData.minPWM, configData.maxPWM);

        //  Serial.print("Is Attached : " );
 //Serial.println(attached);
 //Serial.print("pwm");
 //Serial.println(value);
  
    _servo.writeMicroseconds(value);//+configData.pwmOffset);
}

int DigitalServo::GetAngle() {
   // Serial.print("Angle at servo : ");// + _servo.read());
//Serial.println(_angle);
    // return  _servo.read();
    return _angle;
}

void DigitalServo::SetAngle(int angle) {
   ////   Serial.print("Is Attached : " );
// Serial.println(attached);
if(!attached){
    attach();
}
    //std::cout << "angle " << angle << std::endl;
      //Serial.print("Set ");// + angle);//
  //    Serial.print("Set angle on pin : " );
  //    Serial.print(configData.pin);
  //  Serial.print(" : ");
   // Serial.println(angle);
    _angle = angle;
 
    angle += configData.angleOffset;


         float desiredAngle = constrain(angle, configData.minAngleLimit,configData.maxAngleLimit);
   int pwmValue = map(angle, -135, 135, configData.minPWM, configData.maxPWM);
  
  if(configData.flip)
  {
    pwmValue = map(-angle, -135, 135, configData.minPWM, configData.maxPWM);
  }
  
writeMicroseconds(pwmValue);
}

int DigitalServo::Map(int x, int in_min, int in_max, int out_min, int out_max) 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

