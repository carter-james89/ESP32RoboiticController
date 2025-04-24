#ifndef NETWORKEVENTLISTENER_H
#define NETWORKEVENTLISTENER_H

#include <vector>

class NetworkEventListener {
public:
    virtual ~NetworkEventListener() = default;

    // Called when a message is received from the client
    virtual void OnMessageReceived(int messageType, const std::vector<unsigned char>& message) = 0;

    // Called when the connection times out
    virtual void OnConnectionTimeout() = 0;

    // 🔥 Called when the connection is successfully established
    virtual void OnConnectionEstablished() = 0;
};

#endif // NETWORKEVENTLISTENER_H
