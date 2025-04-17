#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <WiFiUdp.h>
#include <array>
#include <vector>
#include "INetworkHandlerEventListener.h"
#include "RoboticController.h"

class NetworkHandler {
public:
    bool broadcasting;

    NetworkHandler(int connectionPort, const String& broadcastIp, int broadcastPort, unsigned long timeout);

    void initialize(); 
    void loop();
    void sendMessage(int header, byte* message, int messageSize);
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

    static const int MAX_MESSAGE_SIZE = 96;
    std::array<byte, MAX_MESSAGE_SIZE> messageBuffer;

    unsigned long _previousBroadcastMillis;
    String connectionDataJson;
    bool firstTimeout;

    unsigned long syncMillis;
    RoboticController* roboticControler;

    void OnConnectionEstablished();
    void OnConnectionLost();
    void OnConnectionTimeout();

    void sendBroadcast();
    void checkForIncomingPackets();
    void connectToWifi();

    std::vector<INetworkHandlerEventListener*> eventListeners;
};

#endif // NETWORKHANDLER_H
