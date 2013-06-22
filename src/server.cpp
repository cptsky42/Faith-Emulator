/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "server.h"
#include "client.h"
#include "networkclient.h"
#include "msg.h"
#include "database.h"
#include <string>

using namespace std;

/* static */
const uint16_t Server::ACCSERVER_PORT = 9958;
const uint16_t Server::MSGSERVER_PORT = 5816;
const char* Server::SERVER_IP = "172.16.104.1";

Server :: Server()
{
    Database& db = Database::getInstance();
    if (!db.connect("localhost", "xyserver", "root", "s0cac3r3b0rn"))
    {
        LOG("Failed to connect to the database...");
        // failed to connect
    }

    db.loadAllNPCs();

    mAccServer.listen(ACCSERVER_PORT);
    mAccServer.onConnect = &Server::connectionHandler;
    mAccServer.onReceive = &Server::receiveHandler;
    mAccServer.onDisconnect = &Server::disconnectionHandler;
    mAccServer.accept();
    fprintf(stdout, "AccServer listening on port %u...\n", ACCSERVER_PORT);

    mMsgServer.listen(MSGSERVER_PORT);
    mMsgServer.onConnect = &Server::connectionHandler;
    mMsgServer.onReceive = &Server::receiveHandler;
    mMsgServer.onDisconnect = &Server::disconnectionHandler;
    mMsgServer.accept();
    fprintf(stdout, "MsgServer listening on port %u...\n", MSGSERVER_PORT);

    fprintf(stdout, "Waiting for connections...\n");
}

Server :: ~Server()
{

}

/* static */
void
Server :: connectionHandler(NetworkClient* aClient)
{
    fprintf(stdout, "Incoming connection... %p\n", aClient);
    if (aClient != nullptr)
    {
        uint16_t port = ((TcpServer*)aClient->getServer())->getPort();

        Client* client = new Client(aClient);
        client->setStatus(port == MSGSERVER_PORT ? Client::NORMAL : Client::NOT_AUTHENTICATED);

        aClient->setOwner(client);
    }
}

/* static */
void
Server :: receiveHandler(NetworkClient* aClient, uint8_t* aBuf, size_t aLen)
{
    if (aClient != nullptr && aBuf != nullptr)
    {
        if (aLen < sizeof(Msg::Header))
            return;

        uint8_t* received = new uint8_t[aLen];
        memcpy(received, aBuf, aLen);

        // TODO? clean this line and add some checks
        Client* client = (Client*)aClient->getOwner();
        client->getCipher().decrypt(received, aLen);

        size_t size = 0;
        for (size_t i = 0; i < aLen; i += size)
        {
            #if BYTE_ORDER == BIG_ENDIAN
            size = bswap16(((Msg::Header*)(received + i))->Length);
            #else
            size = ((Msg::Header*)(received + i))->Length;
            #endif

            if (size < aLen)
            {
                uint8_t* packet = new uint8_t[size];
                memcpy(packet, received, size);

                #if BYTE_ORDER == BIG_ENDIAN
                Msg::Header* header = (Msg::Header*)packet;
                header->Length = bswap16(header->Length);
                header->Type = bswap16(header->Type);
                #endif

                Msg* msg = nullptr;
                Msg::create(&msg, &packet, size);
                msg->process(client);

                SAFE_DELETE(msg);
                SAFE_DELETE_ARRAY(packet);
            }
            else
            {
                #if BYTE_ORDER == BIG_ENDIAN
                Msg::Header* header = (Msg::Header*)received;
                header->Length = bswap16(header->Length);
                header->Type = bswap16(header->Type);
                #endif

                Msg* msg = nullptr;
                Msg::create(&msg, &received, size);
                msg->process(client);

                SAFE_DELETE(msg);
            }
        }

        SAFE_DELETE_ARRAY(received);
    }
}

/* static */
void
Server :: disconnectionHandler(NetworkClient* aClient)
{
    fprintf(stdout, "Incoming disconnection... %p\n", aClient);
    if (aClient != nullptr)
    {
        // TODO? clean this line and add some checks
        Client* client = (Client*)aClient->getOwner();
        //client->save();

        SAFE_DELETE(client);
    }
}
