/**
 * ****** EoF Emulator - Closed Source ******
 * Copyright (C) 2012 CptSky
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _EOFEMU_NETWORK_CLIENT_H
#define _EOFEMU_NETWORK_CLIENT_H

#include "common.h"
#include <QObject>

class TcpServer;
class QTcpSocket;

/**
  * A network client connected to a tcp server.
  * It is a wrapper to a QTcpSocket.
  */
class NetworkClient : private QObject
{
public:
    /** The size in bytes of the receive buffer. */
    static const size_t BUFFER_SIZE = 4096; // 4 KiB

    Q_OBJECT
public:
    /**
      * Create a new NetworkClient linked to the specified TcpServer and
      * taking the specified TcpSocket.
      * The pointer to the socket will be took.
      *
      * @param[in]      aServer    a reference to the server
      * @param[in,out]  aSocket    a pointer to the socket object of the client
      * @param[in]      aParent    (Optional) the parent Qt object of the client
      *                            Default value is nullptr.
      */
    NetworkClient(TcpServer& aServer, QTcpSocket** aSocket, QObject* aParent = nullptr);

    /**
      * Destroy the client and close the connection.
      */
    ~NetworkClient();

    /**
      * Send the specified buffer to the client.
      *
      * @param[in]  aBuf   a pointer to the buffer containing all the data
      * @param[in]  aLen   the length of the buffer in bytes
      */
    void send(uint8_t* aBuf, size_t aLen);

public:
    /** Get the owner pointer. It may used by some programs. */
    const void* getOwner() { return mOwner; }
    /** Set the owner pointer. It may used by some programs. */
    void setOwner(void* aOwner) { mOwner = aOwner; }

    /** Get the server's pointer. It may be used by some programs. */
    const TcpServer* getServer() { return &mServer; }

private slots:
    /* Incoming data event. */
    void incomingData();
    /* Incoming disconnection event. */
    void incomingDisconnection();

private:
    TcpServer& mServer;   //!< a reference to the TcpServer
    QTcpSocket* mSocket;  //!< a pointer to the socket of the client

    void* mOwner; //!< a pointer to the owner.
};

#endif // _EOFEMU_NETWORK_CLIENT_H
