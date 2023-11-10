#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <WiFiUdp.h>

class NetworkHandler {
public:
    NetworkHandler(int cPort, unsigned long timeout);
    void initialize(); 
    void setOnMessageReceivedCallback(void (*callback)(int header, byte* message, int messageSize));
    void setOnConnectionTimeoutCallback(void (*callback)());
    void loop();
    void sendMessage(int header, byte* message, int messageSize); // Updated signature
    void SendEmptyResponse(int header);

private:
    WiFiUDP broadcastUDP;
    WiFiUDP connectionUDP;
    unsigned long lastResponseTime;
    const unsigned long responseTimeout;
    int broadcastPort;
    int connectionPort;
    String broadcastIP;
    bool broadcasting;
    unsigned long _previousBroadcastMillis; // Changed type to unsigned long
    String connectionDataJson;
    bool firstTimeout;
    byte* previousMessage; // Changed type to byte array
    int previousMessageSize; // Added to store the size of the previous message

    void (*onMessageReceived)(int header, byte* message, int messageSize); // Updated signature

    void (*onConnectionTimeout)();

    void OnConnetionTimeout();

    void sendBroadcast();
    void checkForIncomingPackets();
    void connectToWifi();
};

#endif // NETWORKHANDLER_H
