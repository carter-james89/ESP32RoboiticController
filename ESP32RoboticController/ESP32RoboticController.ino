#include <ArduinoJson.h>

#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <lwip/sockets.h>

#include "RoboticController.h"
#include "QuadrupedConfiguration.h"
#include "BittleQuadrupedConfiguration.h"
#include "RoboticController.h"

//RoboticController _roboticController;
unsigned long lastPrintTime = 0; // Last time the loops per second were printed
unsigned long loopCount = 0;     // Number of loops since last print

//BittleQuadrupedConfiguration config; 
RoboticController _roboticController;

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
    delay(2000);
  Serial.println("Robot bootup");

 

  BittleQuadrupedConfiguration config; 
      delay(1000);
  std::vector<RoboticLimb> limbs;
  limbs.push_back(config.ConstructFrontLeftLimb());
      delay(1000);
  limbs.push_back(config.ConstructFrontRightLimb());
       delay(1000);
   limbs.push_back(config.ConstructBackRightLimb());
        delay(1000);
     limbs.push_back(config.ConstructBackLeftLimb());

  delay(1000);

  _roboticController = RoboticController(limbs); 



}
void loop() {
   delay(100);

// return;
_roboticController.RunControllerLoop();
   // delay(100);

    loopCount++; // Increment the loop counter

    // Check if a second has passed (1000 milliseconds)
    if (millis() - lastPrintTime >= 1000) {
        // Reset the counter and the last print time
        loopCount = 0;
        lastPrintTime = millis();
    }
}