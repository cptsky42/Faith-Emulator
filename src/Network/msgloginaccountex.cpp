/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "msgloginaccountex.h"
#include "client.h"
#include "server.h"
#include "database.h"
#include "msgloginreplyex.h"
#include <string>
#include <string.h>
#include "rc5.h"

using namespace std;

MsgLoginAccountEx :: MsgLoginAccountEx(const char* aAccount, const char* aPassword,
                                       const char* aServer, const char* aInfo)
    : Msg(sizeof(MsgInfo)), mInfo((MsgInfo*)mBuf)
{
    create(aAccount, aPassword, aServer, aInfo);
}

MsgLoginAccountEx :: MsgLoginAccountEx(uint8_t** aBuf, size_t aLen)
    : Msg(aBuf, aLen), mInfo((MsgInfo*)mBuf)
{
    ASSERT(aLen >= sizeof(MsgInfo));

    #if BYTE_ORDER == BIG_ENDIAN
    swap(mBuf);
    #endif
}


MsgLoginAccountEx :: ~MsgLoginAccountEx()
{

}

void
MsgLoginAccountEx :: create(const char* aAccount, const char* aPassword,
                            const char* aServer, const char* aInfo)
{
    ASSERT(aAccount != nullptr && aAccount[0] != '\0');
    ASSERT(aPassword != nullptr && aPassword[0] != '\0');
    ASSERT(aServer != nullptr && aServer[0] != '\0');
    ASSERT(aInfo != nullptr && aInfo[0] != '\0');

    if (strlen(aAccount) < MAX_NAMESIZE_CLI &&
        strlen(aPassword) < MAX_NAMESIZE_CLI &&
        strlen(aServer) < MAX_NAMESIZE_CLI &&
        strlen(aInfo) < MAX_NAMESIZE_CLI)
    {
        mInfo->Header.Length = mLen;
        mInfo->Header.Type = MSG_LOGINACCOUNTEX;

        mInfo->Type = 0; // TODO: set a good value

        strcpy(mInfo->Account, aAccount);
        // TODO: Encrypt password
        strcpy(mInfo->Password, aPassword);
        strcpy(mInfo->Server, aServer);
        strcpy(mInfo->Info, aInfo);
    }
    else
    {
        LOG(ERROR, "Invalid length: account=%zu, password=%zu, server=%zu, info=%zu",
            strlen(aAccount), strlen(aPassword), strlen(aServer), strlen(aInfo));
    }
}

void
MsgLoginAccountEx :: process(Client* aClient)
{
    ASSERT(aClient != nullptr);

    static const Database& db = Database::getInstance(); // singleton

    Client& client = *aClient;
    client.setAccount(mInfo->Account);

    uint8_t seed[RC5::KEY_SIZE] =
            { 0x3C, 0xDC, 0xFE, 0xE8, 0xC4, 0x54, 0xD6, 0x7E, 0x16, 0xA6, 0xF8, 0x1A, 0xE8, 0xD0, 0x38, 0xBE };

    RC5 cipher;
    cipher.generateKey(seed);
    cipher.decrypt((uint8_t*)mInfo->Password, sizeof(mInfo->Password));

    if (isValidString(mInfo->Account) && isValidString(mInfo->Password))
    {
        if (IS_SUCCESS(db.authenticate(client, mInfo->Account, mInfo->Password)))
        {
            fprintf(stdout, "Connection of %s on %s...\n",
                    mInfo->Account, mInfo->Server);

            int32_t token = random(10000, INT32_MAX);

            MsgLoginReplyEx msg(client.getAccountID(), token, Server::getServerIP());
            client.send(&msg);
        }
        else
        {
            // TODO: send bad password packet
            // TODO: Bruteforce protection
        }
    }
    else
    {
        client.disconnect();
    }
}

void
MsgLoginAccountEx :: swap(uint8_t* aBuf)
{
    ASSERT(aBuf != nullptr);

    MsgInfo* info = (MsgInfo*)aBuf;

    info->Type = bswap32(info->Type);
}
