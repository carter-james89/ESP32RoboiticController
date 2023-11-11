#ifndef INETWORKHANDLEREVENTLISTENER_H
#define INETWORKHANDLEREVENTLISTENER_H

#include <vector>

class INetworkHandlerEventListener {
public:
    virtual ~INetworkHandlerEventListener() {}

    // Called when a message is received.
    // The first parameter is an integer, and the second is a byte array.
    virtual void OnMessageReceived(int messageType, const std::vector<unsigned char>& message) = 0;

    // Called when a connection timeout occurs.
    virtual void OnConnectionTimeout() = 0;
};

#endif // INETWORKHANDLEREVENTLISTENER_H
