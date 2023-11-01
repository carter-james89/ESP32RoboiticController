#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include "RoboticController.h"
#include "QuadrupedConfiguration.h"
#include "BittleQuadrupedConfiguration.h"


const char* ssid = "because-fi";
const char* password = "DaveReevis";
const int listenPort = 49512;
WiFiUDP udp;
String receivedMessage;


RoboticController _roboticController;

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
    delay(2000);
  Serial.println("Robot bootup");
  //return;
   
    WiFi.begin(ssid, password);
    
  while (WiFi.status() != WL_CONNECTED) {
    delay(10000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

 //  udp.begin(listenPort);

BittleQuadrupedConfiguration config; 
  _roboticController = RoboticController(&config); 

   Serial.println("Robot Configured");

 //   Serial.print("Listening on port: ");
 // Serial.println(listenPort);

    delay(5000);

    _roboticController.RunControllerLoop();
}
void loop() {
 // Serial.println("looping");
return;
  
    //Serial.print("Check UDP for Messages: ");
   int packetSize = udp.parsePacket();
  if (packetSize) {
    Serial.print("got packet: ");
    char packetData[255];
    int bytesRead = udp.read(packetData, sizeof(packetData) - 1);
    if (bytesRead > 0) {
      packetData[bytesRead] = '\0';
      receivedMessage += packetData;

      // Check if complete message received
      int endIndex = receivedMessage.indexOf(">");
      if (endIndex != -1) {
        int startIndex = receivedMessage.lastIndexOf("<", endIndex);
        if (startIndex != -1 && endIndex > startIndex + 1) {
          String messageContent = receivedMessage.substring(startIndex + 1, endIndex);
          Serial.print("Received message: ");
          Serial.println(messageContent);
          // Do something with the extracted message content here

          onMessageReceivedFromServer(messageContent);

          // Send response
          udp.beginPacket(udp.remoteIP(), udp.remotePort());
          udp.print("success");
          udp.endPacket();       

          // Cache the remaining message for the next loop
          receivedMessage = receivedMessage.substring(endIndex + 1);
        } else {
          // Invalid message format, clear the received message
          receivedMessage = "";
        }
      }
    }
  }
}

void onMessageReceivedFromServer(String message) {
  int key = message.toInt();
  Serial.println(message);
  switch (key) {
    case 0:  //shutdown with confirmaton
     // shutdown(true);
      break;
    case 1:  //return sensor data
      //runSensors();
      //sendSensorData();
      break;
    case 2:  //set motor values
     // setMotors(message);
      break;
    case 3:  //set motor values with responce
     // Serial.println(setMotors(message));
      break;
    default:
      break;
  }
}

