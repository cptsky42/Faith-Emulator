#ifndef _FAITH_EMULATOR_SERVER_H
#define _FAITH_EMULATOR_SERVER_H

#include "common.h"
#include "tcpserver.h"
#include "rc5.h"

class NetworkClient;

class Server
{
public:
    static const uint16_t ACCSERVER_PORT;
    static const uint16_t MSGSERVER_PORT;
    static const char* SERVER_IP;

public:
    Server();
    ~Server();

public:
    static void connectionHandler(NetworkClient* aClient);
    static void receiveHandler(NetworkClient* aClient, uint8_t* aBuf, size_t aLen);
    static void disconnectionHandler(NetworkClient* aClient);

private:
    TcpServer mAccServer;
    TcpServer mMsgServer;
};

#endif // _FAITH_EMULATOR_SERVER_H
