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
void NetworkHandler::connectToWifi(){
       WiFi.begin(ssid, password);
    
  while (WiFi.status() != WL_CONNECTED) {
    delay(20000);
    Serial.print("Attempting to Connect to WIFI : ");
    Serial.println(ssid);
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void NetworkHandler::SendEmptyResponse(int header) {
    // Create a packet that contains only the header
    byte packet[sizeof(header)];
    memcpy(packet, &header, sizeof(header));

    // Send the packet
    connectionUDP.beginPacket(connectionUDP.remoteIP(), connectionPort);
    connectionUDP.write(packet, sizeof(packet));
    connectionUDP.endPacket();
    Serial.println("Sent empty response with header: " + String(header));
}

void NetworkHandler::setOnMessageReceivedCallback(void (*callback)(int, byte*, int)) {
    onMessageReceived = callback;
}

void NetworkHandler::setOnConnectionTimeoutCallback(void (*callback)()) {
    onConnectionTimeout = callback;
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
    // Combine the header and the message into one packet
    byte packet[sizeof(header) + messageSize];
    memcpy(packet, &header, sizeof(header));
    memcpy(packet + sizeof(header), message, messageSize);

    // Send the packet
    connectionUDP.beginPacket(connectionUDP.remoteIP(), connectionPort);
    connectionUDP.write(packet, sizeof(packet));
    connectionUDP.endPacket();
   // Serial.println("Send Message over connection");
}

void NetworkHandler::OnConnetionTimeout(){
     if(firstTimeout){
        Serial.println("tIMEOUT : Resend Message over connection");
       // sendMessage(previousMessage);
        firstTimeout = false;
            lastResponseTime = millis();
        return;
     }
     firstTimeout = true;
        broadcasting = true;
        // Reset the broadcast timer to immediately try broadcasting again
        _previousBroadcastMillis = millis() - 10000;
       if (onConnectionTimeout) {
            onConnectionTimeout(); // Call the timeout callback
        }
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

void NetworkHandler::checkForIncomingPackets() {
    int packetSize = connectionUDP.parsePacket();
    if (packetSize) {
        // Allocate a buffer to hold the incoming packet data.
        byte packetData[packetSize]; // No need for +1 since we're not working with strings here
        int bytesRead = connectionUDP.read(packetData, packetSize);
        if (bytesRead > 0) {
            // Check if the packet contains at least the size of the header
            if (bytesRead >= sizeof(int)) {
                // Extract the header from the packet
                int header;
                memcpy(&header, packetData, sizeof(header));

                // Calculate the size of the actual message
                int messageSize = bytesRead - sizeof(header);

                // Allocate a buffer for the message content
                byte* messageContent = new byte[messageSize];

                // Copy the message content from the packet, skipping the header
                memcpy(messageContent, packetData + sizeof(header), messageSize);

                // Stop broadcasting since we've received a message
                broadcasting = false;

                // We received a message, so update the last response time
                lastResponseTime = millis();
                firstTimeout = true;

                // Call the message received callback if it's set
                if (onMessageReceived) {
                    onMessageReceived(header, messageContent, messageSize);
                }

                // Clean up the allocated message content buffer
                delete[] messageContent;
            }
        }
    }
}

