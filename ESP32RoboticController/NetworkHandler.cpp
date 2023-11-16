#include "NetworkHandler.h"
#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>

const char* ssid = "because-fi";
const char* password = "DaveReevis";

//const char* ssid = "iPhone (7)";
//const char* password = "DaveReevis";

String connectionDataJson;
const int broadcastPort = 5501; // Local port to listen for incoming UDP packets
const String broadcastIP = "255.255.255.255"; // Broadcast IP for the local network

NetworkHandler::NetworkHandler(int cPort,  unsigned long timeout)
    : connectionPort(cPort),responseTimeout(timeout), broadcasting(true),
      lastResponseTime(0), _previousBroadcastMillis(0) ,broadcastPort(5501) 
      ,broadcastIP("255.255.255.255"),firstTimeout(true){
      
}
void NetworkHandler::initialize(){
      // xTaskCreate(this->Task, "ClassBTask", 10000, this, 1, NULL);
  connectToWifi();

     StaticJsonDocument<200> doc;
      doc["BoardType"] = "esp32";
      doc["Name"] = "bittle";
      doc["IP"] = WiFi.localIP();
      doc["Port"] = 8081;
      
      serializeJson(doc, connectionDataJson);

    broadcastUDP.begin(broadcastPort);
    connectionUDP.begin(connectionPort);
}
void NetworkHandler::subscribeToEvents(INetworkHandlerEventListener* listener) {
    eventListeners.push_back(listener);
}

void NetworkHandler::SetRoboticController(RoboticController* rc){
    roboticControler = rc;
}



void NetworkHandler::connectToWifi(){
       WiFi.begin(ssid, password);
    
  while (WiFi.status() != WL_CONNECTED) {
      Serial.print("Attempting to Connect to WIFI : ");
    Serial.println(ssid);
    delay(10000);
  
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void NetworkHandler::SendEmptyResponse(int header) {
    // Create a packet that contains only the header
    byte packet[0];
    memcpy(packet, &header, sizeof(header));

    sendMessage(header,packet, sizeof(packet));

    // Send the packet
    // connectionUDP.beginPacket(connectionUDP.remoteIP(), connectionPort);
    // connectionUDP.write(packet, sizeof(packet));
    // connectionUDP.endPacket();
  //  Serial.println("Sent empty response with header: " + String(header));
}

void NetworkHandler::sendBroadcast() {
    broadcastUDP.beginPacket("255.255.255.255", broadcastPort);
    broadcastUDP.print(connectionDataJson);
    broadcastUDP.endPacket();
    Serial.print("Broadcast message sent ");
    Serial.println(broadcastPort);
       _previousBroadcastMillis = millis();
}

void NetworkHandler::sendMessage(int header, byte* message, int messageSize) {
    // Get the current time since synchronization in milliseconds
    unsigned long currentMillis = millis();
    unsigned long timeSinceSync = currentMillis - syncMillis;
    // Convert the timeSinceSync to a byte array
    byte timeByteArray[sizeof(timeSinceSync)];
    memcpy(timeByteArray, &timeSinceSync, sizeof(timeSinceSync));

    // Calculate the total packet size (header + time + message)
    int totalPacketSize = sizeof(header) + sizeof(timeSinceSync) + messageSize;

    // Allocate a buffer for the combined packet
    byte packet[totalPacketSize];

    // Copy the header, time, and message into the packet
    memcpy(packet, &header, sizeof(header));
    memcpy(packet + sizeof(header), timeByteArray, sizeof(timeSinceSync));
    memcpy(packet + sizeof(header) + sizeof(timeSinceSync), message, messageSize);

//Serial.println("send packet");
    // Send the packet
    connectionUDP.beginPacket(connectionUDP.remoteIP(), connectionPort);
    connectionUDP.write(packet, totalPacketSize);
    connectionUDP.endPacket();
}

void NetworkHandler::OnConnetionTimeout(){
    //  if(firstTimeout){
    //     Serial.println("tIMEOUT : Resend Message over connection");
    //    // sendMessage(previousMessage);
    //     firstTimeout = false;
    //         lastResponseTime = millis();
    //     return;
    //  }
        Serial.println("Connection timeout");
     firstTimeout = true;
       

        roboticControler->OnConnectionTimeout1();

        OnConnectionLost();
    //    for (auto& listener : eventListeners) {
    // if (listener != nullptr) {
    //     listener->OnConnectionTimeout();
    // }
}

void NetworkHandler::loop() {
    // Check for any incoming UDP packets
    checkForIncomingPackets();

    // If we have not received a response, handle broadcast timing
    if (broadcasting && (millis() - _previousBroadcastMillis >= 10000)) {
        sendBroadcast();     
    }
    // If we are expecting a response, check if the response timeout has been exceeded
   else  if (!broadcasting && (millis() - lastResponseTime > responseTimeout)) {
        // Timeout logic
    OnConnetionTimeout();
    }
}

void NetworkHandler::AttemptEstablishConnection(){
      Serial.println("Attempt establish connection");
      syncMillis = millis();
 // Serial.println("Set sync time: " + syncMillis);
   SendEmptyResponse(0);
   OnConnectionEstablished();
}

void NetworkHandler:: OnConnectionEstablished(){
    Serial.println("OnConnectionEstablished");
                // Stop broadcasting since we've received a message
                broadcasting = false;

                // We received a message, so update the last response time
                lastResponseTime = millis();
                firstTimeout = true;
}
void NetworkHandler::OnConnectionLost(){
 broadcasting = true;
        // Reset the broadcast timer to immediately try broadcasting again
        _previousBroadcastMillis = millis() - 10000;
}
void NetworkHandler::checkForIncomingPackets() {
    int packetSize = connectionUDP.parsePacket();
    if (packetSize) {
        // Allocate a buffer to hold the incoming packet data.
        byte packetData[packetSize]; // No need for +1 since we're not working with strings here
        int bytesRead = connectionUDP.read(packetData, packetSize);
        if (bytesRead > 0) {
           // Serial.print("got message");
            // Check if the packet contains at least the size of the header
            if (bytesRead >= sizeof(int)) {
                  lastResponseTime = millis();
                // Extract the header from the packet
                int header;
                memcpy(&header, packetData, sizeof(header));

                if(broadcasting && header !=0){
                       Serial.println("Got header that isnt connection while broadcasting");
                       return;
                }

                // Calculate the size of the actual message
                int messageSize = bytesRead - sizeof(header);

                // Allocate a buffer for the message content
                byte* messageContent = new byte[messageSize];

                // Copy the message content from the packet, skipping the header
                memcpy(messageContent, packetData + sizeof(header), messageSize);

             
std::vector<unsigned char> messageVector;
// Only fill the vector if there is actual content
if (messageContent && messageSize > 0) {
    messageVector.assign(messageContent, messageContent + messageSize);
}
else{
   //   Serial.print("empty message");
}
if (roboticControler != nullptr) {
    roboticControler->OnMessageReceived1(header, messageVector);
} else {
    Serial.println("roboticControler is null!");
}


//Something is wrong with this
// for (INetworkHandlerEventListener* listener : eventListeners) {
//     if (listener != nullptr) {
//          //Serial.print("send event");
//         // Call a method on the listener
//         // For example, if you have a method like OnEventOccurred()
//          listener->OnMessageReceived(header, messageVector);
//     }
// }


                // Clean up the allocated message content buffer
                delete[] messageContent;
            }
        }
    }
}

