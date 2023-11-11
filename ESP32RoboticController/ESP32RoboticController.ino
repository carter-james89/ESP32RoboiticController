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
  _roboticController = RoboticController(&config); 

}
void loop() {
 
_roboticController.RunControllerLoop();
    delay(10);


    loopCount++; // Increment the loop counter

    // Check if a second has passed (1000 milliseconds)
    if (millis() - lastPrintTime >= 1000) {
      //  Serial.print("Loops per second: ");
      //  Serial.println(loopCount);

        // Reset the counter and the last print time
        loopCount = 0;
        lastPrintTime = millis();
    }
}