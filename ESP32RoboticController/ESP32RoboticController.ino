#include <ArduinoJson.h>
#include "NetworkHandler.h"

#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include "Gyro.h"
#include <lwip/sockets.h>

#include "RoboticController.h"
#include "QuadrupedConfiguration.h"
#include "BittleQuadrupedConfiguration.h"

Gyro gyro;
RoboticController _roboticController;

unsigned long lastPrintTime = 0; // Last time the loops per second were printed
unsigned long loopCount = 0;     // Number of loops since last print


void onConnectionTimeout() {
    Serial.println("Connection timout, resuming broadcast");
}
  NetworkHandler networkHandler(8081,  10000);

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
    delay(2000);
  Serial.println("Robot bootup");

  BittleQuadrupedConfiguration config; 
  _roboticController = RoboticController(&config); 


 networkHandler.setOnMessageReceivedCallback(onMessageReceived);
    networkHandler.setOnConnectionTimeoutCallback(onConnectionTimeout);
    networkHandler.initialize();

      gyro.begin();
   Serial.println("Robot Configured");
}
void loop() {
 
 networkHandler.loop();
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

void onMessageReceived(int header, byte* message, int length) {
  switch (header) {
    case 0:  // Connection established, sync time
      EstablishConnection(message);
      break;
    case 1:  // Return sensor data
      RunSpeedTest();
      break;
    case 2:  // Set motor values
      runSensors();
      break;
    // ... other cases ...
  }
}

  void runSensors() {
 // calculateHeight();
  calculateRotation(false);
}
void calculateHeight() {
  //_groundHeight = sonar.ping_cm();
}

//unsigned long syncTimestamp = 0; // The Unix timestamp received from the PC
unsigned long syncMillis = 0;    // The millis() value when the timestamp was set

void EstablishConnection(byte* message) {
  Serial.print("Connection Request Received : ");

  syncMillis = millis();
  Serial.print("Received sync time: ");
   networkHandler.SendEmptyResponse(0);
}

void RunSpeedTest() {
    unsigned long currentMillis = millis();
    unsigned long timeSinceSync = currentMillis - syncMillis; // Time since synchronization in milliseconds
 // Serial.println(timeSinceSync);
    // Convert the timeSinceSync to a byte array
    byte timeByteArray[sizeof(timeSinceSync)];
    memcpy(timeByteArray, &timeSinceSync, sizeof(timeSinceSync));

    // Send the message with header 1
    networkHandler.sendMessage(1, timeByteArray, sizeof(timeSinceSync));
}

void calculateRotation(bool resetOffset) {
    // Assuming Gyro::GetSerializedGyroData has been updated to fill a byte array
    unsigned int length = 0;
    byte* gyroData = nullptr;

    // Get the serialized gyro data as a byte array
    gyro.GetSerializedGyroData(gyroData, length);

    // Send the message with the appropriate header
    networkHandler.sendMessage(2, gyroData, length);

    // Clean up the allocated gyroData after sending the message
    delete[] gyroData;
}
