#include <ArduinoJson.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include "Gyro.h"

#include "RoboticController.h"
#include "QuadrupedConfiguration.h"
#include "BittleQuadrupedConfiguration.h"

class ConnectionData {
  public:
    String BoardType;
    String Name;
    IPAddress IP;
    unsigned int Port;

    // Serialize the ConnectionData to a JSON string
    String serialize() {
      StaticJsonDocument<200> doc;
      doc["Type"] = BoardType;
      doc["Name"] = Name;
      doc["IP"] = IP.toString();
      doc["Port"] = Port;
      
      String output;
      serializeJson(doc, output);
      return output;
    }
};


const char* ssid = "because-fi";
const char* password = "DaveReevis";
const int localUDPPort = 49512; // Local port to listen for incoming UDP packets
const int broadcastPort = 8081; // Port to send UDP packets to
const char* broadcastIP = "255.255.255.255"; // Broadcast IP for the local network
WiFiUDP udp;
String receivedMessage;
bool responseReceived = false;

unsigned long lastResponseTime = 0; // Variable to store the last response time
const unsigned long responseTimeout = 10000; // 10 seconds timeout

long _yaw = 0;
long _pitch = 0;
long _roll = 0;
long _yawOffset = 0;
long _pitchOffset = 0;
long _rollOffset = 0;
double _quatW = 0;
double _quatX = 0;
double _quatY = 0;
double _quatZ = 0;

Gyro gyro;

ConnectionData connectionData;
String connectionDataJson;

RoboticController _roboticController;

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
    delay(2000);
  Serial.println("Robot bootup");
  //return;
      gyro.begin();
   
    WiFi.begin(ssid, password);
    
  while (WiFi.status() != WL_CONNECTED) {
    delay(10000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Initialize mDNS


 //  udp.begin(listenPort);

BittleQuadrupedConfiguration config; 
  _roboticController = RoboticController(&config); 

   Serial.println("Robot Configured");

 //   Serial.print("Listening on port: ");
 // Serial.println(listenPort);

    delay(5000);
 udp.begin(localUDPPort);
  Serial.println("UDP started");
  delay(1000);

  connectionData.BoardType = "esp32";
  connectionData.Name = "bittle";
  connectionData.IP = WiFi.localIP();
  connectionData.Port = 8081;

  connectionDataJson = connectionData.serialize();
 // connectionData.type
 // connData.ip = IPAddress(192, 168, 1, 10);
  //connData.port = 8080;
    _roboticController.RunControllerLoop();
}
void loop() {
   //gyro.update();
   // gyro.printData();
    //delay(500);
    return;
 // Serial.println("looping");
 if (!responseReceived) {
    // Broadcast a message every 10 seconds  
    udp.beginPacket(broadcastIP, broadcastPort);
    udp.print(connectionDataJson);
    udp.endPacket();
    Serial.println("Broadcast message sent");

    delay(5000); // Wait for 10 seconds

    // Check for a response
    int packetSize = udp.parsePacket();
    if (packetSize) {
      // Read the packet, process it, and check for a valid response
      char packetBuffer[255];
      int len = udp.read(packetBuffer, 255);
      if (len > 0) {
        packetBuffer[len] = 0; // Null-terminate the string
        receivedMessage = packetBuffer;
        Serial.print("Received response: ");
        Serial.println(receivedMessage);
        responseReceived = true; // Stop broadcasting since we got a response
      }
    }
  } else {


   int packetSize = udp.parsePacket();
  if (packetSize) {
    Serial.print("got packet: ");
    char packetData[255];
    int bytesRead = udp.read(packetData, sizeof(packetData) - 1);
    if (bytesRead > 0) {

lastResponseTime = millis();
      
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
  
  
    if (millis() - lastResponseTime > responseTimeout) {
      OnConnectionTimeout();
      // Reset the timer
      lastResponseTime = millis();
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
      runSensors();
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
  void runSensors() {
 // calculateHeight();
  calculateRotation(false);
}
void calculateHeight() {
  //_groundHeight = sonar.ping_cm();
}

void OnConnectionTimeout() {
  // This function will be called once the timeout occurs
  Serial.println("Connection timeout occurred!");
  // Add any additional logic you need to handle the timeout here
}


void calculateRotation(bool resetOffset) {
 // displayCalStatus();
  // sensors_event_t event;
  // bno.getEvent(&event);
  // if (resetOffset) {
  //   _yawOffset = event.orientation.z;
  //   _rollOffset = event.orientation.x;
  //   _pitchOffset = event.orientation.y;
  // }
  // _yaw = event.orientation.z - m_yawOffset;
  // _roll = event.orientation.x - m_rollOffset;
  // _pitch = event.orientation.y - m_pitchOffset;

  // imu::Quaternion quat = bno.getQuat();

  // _quatW = quat.w();
  // _quatX = quat.x();
  // _quatY = quat.y();
  // _quatZ = quat.z();

}

