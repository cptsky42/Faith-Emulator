/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "msgaccount.h"
#include "client.h"
#include "server.h"
#include "database.h"
#include "msgconnect.h"
#include <string>
#include <string.h>
#include "rc5.h"

using namespace std;

MsgAccount :: MsgAccount(uint8_t** aBuf, size_t aLen)
    : Msg(aBuf, aLen)
{
    ASSERT(aLen >= sizeof(MsgInfo));

    mInfo = (MsgInfo*)mBuf;
    #if BYTE_ORDER == BIG_ENDIAN
    swap(mBuf);
    #endif
}


MsgAccount :: ~MsgAccount()
{

}

void
MsgAccount :: process(Client* aClient)
{
    ASSERT(aClient != nullptr);

    Client& client = *aClient;
    Database& db = Database::getInstance();

    client.setAccount(mInfo->Account);

    uint8_t seed[RC5::KEY_SIZE] =
            { 0x3C, 0xDC, 0xFE, 0xE8, 0xC4, 0x54, 0xD6, 0x7E, 0x16, 0xA6, 0xF8, 0x1A, 0xE8, 0xD0, 0x38, 0xBE };

    RC5 cipher;
    cipher.generateKey(seed);
    cipher.decrypt((uint8_t*)mInfo->Password, sizeof(mInfo->Password));

    if (IS_SUCCESS(db.authenticate(mInfo->Account, mInfo->Password)))
    {
        fprintf(stdout, "Connection of %s on %s...\n",
                mInfo->Account, mInfo->Server);

        int32_t token = timeGetTime();

        MsgConnect msg(client.getAccUID(), token, Server::getServerIP());
        client.send(&msg);
    }
    else
    {
        // TODO: Bruteforce protection
        // TODO: send bad password packet
    }
}
