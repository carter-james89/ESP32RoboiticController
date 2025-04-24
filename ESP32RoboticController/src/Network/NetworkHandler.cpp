// NetworkHandler.cpp
#include "NetworkEventListener.h"
#include "NetworkHandler.h"  // <-- this must be here!
#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>



const char* ssid = "because-fi";
const char* password = "DaveReevis";

NetworkHandler::NetworkHandler(int cPort, const String& bIp, int bPort, unsigned long timeout)
    : connectionPort(cPort), broadcastIP(bIp), broadcastPort(bPort), responseTimeout(timeout),
      broadcasting(true), lastResponseTime(0), _previousBroadcastMillis(0), firstTimeout(true) {}

void NetworkHandler::initialize() {
    connectToWifi();

    StaticJsonDocument<200> doc;
    doc["BoardType"] = "esp32";
    doc["Name"] = "bittle";
    doc["IP"] = WiFi.localIP();
    doc["Port"] = connectionPort;
    serializeJson(doc, connectionDataJson);

    broadcastUDP.begin(broadcastPort);
    connectionUDP.begin(connectionPort);
}

void NetworkHandler::subscribeToEvents(NetworkEventListener* listener) {
    eventListeners.push_back(listener);
}

void NetworkHandler::NotifyListenersConnected(){
    for (auto* listener : eventListeners) {
        if (listener) {
            listener->OnConnectionEstablished();
        }
    }
    
}


void NetworkHandler::connectToWifi() {
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
    byte dummy[1] = {0};
    sendMessage(header, dummy, 0);
}

void NetworkHandler::sendBroadcast() {
    broadcastUDP.beginPacket(broadcastIP.c_str(), broadcastPort);
    broadcastUDP.print(connectionDataJson);
    broadcastUDP.endPacket();
    Serial.print("Broadcast message sent ");
    Serial.println(broadcastPort);
    _previousBroadcastMillis = millis();
}

void NetworkHandler::sendMessage(int header, byte* message, int messageSize) {
    unsigned long currentMillis = millis();
    unsigned long timeSinceSync = currentMillis - syncMillis;

    byte timeByteArray[sizeof(timeSinceSync)];
    memcpy(timeByteArray, &timeSinceSync, sizeof(timeSinceSync));

    int totalPacketSize = sizeof(header) + sizeof(timeSinceSync) + messageSize;
    std::vector<byte> packet(totalPacketSize);

    memcpy(packet.data(), &header, sizeof(header));
    memcpy(packet.data() + sizeof(header), timeByteArray, sizeof(timeSinceSync));
    memcpy(packet.data() + sizeof(header) + sizeof(timeSinceSync), message, messageSize);

    connectionUDP.beginPacket(connectionUDP.remoteIP(), connectionPort);
    connectionUDP.write(packet.data(), totalPacketSize);
    connectionUDP.endPacket();
}

void NetworkHandler::OnConnectionTimeout() {
    Serial.println("Connection timeout");
    firstTimeout = true;
    OnConnectionLost();
}

void NetworkHandler::loop() {
// QuadrupedData data = roboticControler->GetQuadrupedData();
//     uint8_t buffer[sizeof(QuadrupedData)];
    // memcpy(buffer, &data, sizeof(QuadrupedData));
    // sendMessage(1, buffer, sizeof(QuadrupedData));
    
    checkForIncomingPackets();

    if (broadcasting && (millis() - _previousBroadcastMillis >= 10000)) {
        sendBroadcast();
    } else if (!broadcasting && (millis() - lastResponseTime > responseTimeout)) {
        OnConnectionTimeout();
    }
}

void NetworkHandler::AttemptEstablishConnection() {
    Serial.println("Attempt establish connection");
    syncMillis = millis();
    SendEmptyResponse(0);
    OnConnectionEstablished();
}

void NetworkHandler::OnConnectionEstablished() {
    Serial.println("OnConnectionEstablished");
    broadcasting = false;
    lastResponseTime = millis();
    firstTimeout = true;
    NotifyListenersConnected();
}

void NetworkHandler::OnConnectionLost() {
    broadcasting = true;
    _previousBroadcastMillis = millis() - 10000;
    NotifyListenersDisconnected();
}

void NetworkHandler::checkForIncomingPackets() {
    int packetSize = connectionUDP.parsePacket();
    if (packetSize) {
        int bytesRead = connectionUDP.read(messageBuffer.data(), std::min(packetSize, MAX_MESSAGE_SIZE));
        if (bytesRead > 0 && bytesRead >= sizeof(int)) {
            lastResponseTime = millis();
            int header;
            memcpy(&header, messageBuffer.data(), sizeof(header));

            if (broadcasting && header != 0) {
                Serial.println("Got header that isn't connection while broadcasting");
                return;
            }

            int messageSize = bytesRead - sizeof(header);
            std::vector<unsigned char> messageVector;

            if (messageSize > 0) {
                messageVector.assign(messageBuffer.begin() + sizeof(header), messageBuffer.begin() + sizeof(header) + messageSize);
            }

            if(header == 0){
                AttemptEstablishConnection();
            }
            else{
                NotifyListenersMessageRecieved(header,messageVector);
            }


        }
    }
}
