#include <ArduinoJson.h>

#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <lwip/sockets.h>

#include "RoboticController.h"
#include "QuadrupedConfiguration.h"
#include "RoboticController.h"
#include "BittleQuadrupedConstructor.h"

//RoboticController _roboticController;
unsigned long lastPrintTime = 0; // Last time the loops per second were printed
unsigned long loopCount = 0;     // Number of loops since last print

//BittleQuadrupedConfiguration config; 
RoboticController _roboticController;
BittleQuadrupedConstructor constructor;

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
    delay(2000);
  Serial.println("Robot bootup");

 

 // BittleQuadrupedConfiguration config; 
    //  delay(5000);
  // std::vector<RoboticLimb> limbs;
  // limbs.push_back(config.ConstructFrontLeftLimb());
  //    // delay(5000);
  // limbs.push_back(config.ConstructFrontRightLimb());
  //    //  delay(5000);
  //  limbs.push_back(config.ConstructBackRightLimb());
  //     //  delay(5000);
  //    limbs.push_back(config.ConstructBackLeftLimb());

  delay(5000);

 //  _roboticController = RoboticController(config); 
 _roboticController = RoboticController(constructor);

 delay(5000);
 //config.OnConstructionComplete();

}
void loop() {
  _roboticController.RunControllerLoop();
   delay(100000);



 return;
   // delay(100);

    loopCount++; // Increment the loop counter

    // Check if a second has passed (1000 milliseconds)
    if (millis() - lastPrintTime >= 1000) {
        // Reset the counter and the last print time
        loopCount = 0;
        lastPrintTime = millis();
    }
}