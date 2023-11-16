#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <WiFiUdp.h>
#include "INetworkHandlerEventListener.h"
#include "RoboticController.h"

class NetworkHandler {
public:
  bool broadcasting;
    NetworkHandler(int cPort, unsigned long timeout);
    void initialize(); 
    void loop();
    void sendMessage(int header, byte* message, int messageSize); // Updated signature
    void SendEmptyResponse(int header);
       void subscribeToEvents(INetworkHandlerEventListener* listener);
        void SetRoboticController(RoboticController* rc);
      void AttemptEstablishConnection();

private:
    WiFiUDP broadcastUDP;
    WiFiUDP connectionUDP;
    unsigned long lastResponseTime;
    const unsigned long responseTimeout;
    int broadcastPort;
    int connectionPort;
    String broadcastIP;
  
    unsigned long _previousBroadcastMillis; // Changed type to unsigned long
    String connectionDataJson;
    bool firstTimeout;
    byte* previousMessage; // Changed type to byte array
    int previousMessageSize; // Added to store the size of the previous message
unsigned long syncMillis;    // The millis() value when the timestamp was set
   RoboticController* roboticControler;

void OnConnectionEstablished();
void OnConnectionLost();
    void OnConnetionTimeout();

    void sendBroadcast();
    void checkForIncomingPackets();
    void connectToWifi();

      std::vector<INetworkHandlerEventListener*> eventListeners; // List of event listeners

};

#endif // NETWORKHANDLER_H
