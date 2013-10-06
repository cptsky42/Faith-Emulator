/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "log.h"
#include "server.h"
#include "client.h"
#include "networkclient.h"
#include "msg.h"
#include "mapmanager.h"
#include "database.h"
#include "npctask.h"
#include <QSettings>
#include <QString>

#include "mapdata.h"

using namespace std;

/* static */
const uint16_t Server::ACCSERVER_PORT = 9958;
const uint16_t Server::MSGSERVER_PORT = 5816;

/* static */
Server* Server::sInstance = nullptr;

/* static */
Server&
Server :: getInstance()
{
    // TODO? Thread-safe
    if (sInstance == nullptr)
    {
        sInstance = new Server();
    }
    return *sInstance;
}

Server :: Server()
{
    err_t err = ERROR_SUCCESS;

    DOIF(err, Logger::init("./", "xyserv"));

    QSettings settings("./settings.cfg", QSettings::IniFormat);
    QString name = settings.value("FAITH_EMULATOR/NAME", "Faith").toString(); // TODO
    mServerIP = settings.value("FAITH_EMULATOR/SERVER_IP", "127.0.0.1").toString().toStdString();

    QString sql_host = settings.value("FAITH_EMULATOR/SQL_HOST", "localhost").toString();
    QString sql_db = settings.value("FAITH_EMULATOR/SQL_DB", "xyserver").toString();
    QString sql_user = settings.value("FAITH_EMULATOR/SQL_USER", "root").toString();
    QString sql_pwd = settings.value("FAITH_EMULATOR/SQL_PWD", "").toString();

    MapManager& mgr = MapManager::getInstance();
    //DOIF(err, mgr.loadData());

    Database& db = Database::getInstance();
    if (!db.connect(qPrintable(sql_host), qPrintable(sql_db),
                    qPrintable(sql_user), qPrintable(sql_pwd)))
    {
        LOG(ERROR, "Failed to connect to the database...");
        // failed to connect
    }

    // load Lua VM
    NpcTask::registerFunctions(); // TODO: Only one call for all ?

    // load database
    //DOIF(err, db.loadAllMaps());
    //DOIF(err, db.loadAllItems());
    //DOIF(err, db.loadAllNPCs());

    fprintf(stdout, "\n");

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

    ASSERT(err == ERROR_SUCCESS);
}

Server :: ~Server()
{

}

/* static */
void
Server :: connectionHandler(NetworkClient* aClient)
{
    LOG(DBG, "Incoming connection... %p\n", aClient);
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
    LOG(DBG, "Incoming disconnection... %p\n", aClient);
    if (aClient != nullptr)
    {
        // TODO? clean this line and add some checks
        Client* client = (Client*)aClient->getOwner();
        //client->save();

        SAFE_DELETE(client);
    }
}
