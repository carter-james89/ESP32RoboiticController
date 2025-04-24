#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <WiFiUdp.h>
#include <array>
#include <vector>
#include "NetworkEventListener.h"

    
class NetworkHandler {
public:
    bool broadcasting;
    void checkForIncomingPackets();
    NetworkHandler(int connectionPort, const String& broadcastIp, int broadcastPort, unsigned long timeout);

    void initialize(); 
    void loop();
    void sendMessage(int header, byte* message, int messageSize);
    void SendEmptyResponse(int header);
    void subscribeToEvents(NetworkEventListener* listener);
    void AttemptEstablishConnection();

    void SendConnectionBroadcast();

private:
    WiFiUDP broadcastUDP;
    WiFiUDP connectionUDP;

    unsigned long lastResponseTime;
    const unsigned long responseTimeout;

    std::vector<NetworkEventListener*> eventListeners;

    void NotifyListenersConnected();
    void NotifyListenersDisconnected();
    void NotifyListenersMessageRecieved(int messageType, const std::vector<unsigned char>& message);

    int broadcastPort;
    int connectionPort;
    String broadcastIP;

    static const int MAX_MESSAGE_SIZE = 96;
    std::array<byte, MAX_MESSAGE_SIZE> messageBuffer;

    unsigned long _previousBroadcastMillis;
    String connectionDataJson;
    bool firstTimeout;

    unsigned long syncMillis;

    void OnConnectionEstablished();
    void OnConnectionLost();
    void OnConnectionTimeout();

 

    void connectToWifi();
};

#endif // NETWORKHANDLER_H
