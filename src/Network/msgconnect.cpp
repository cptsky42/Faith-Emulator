/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "msgconnect.h"
#include "client.h"
#include "player.h"
#include "database.h"
#include "msgtalk.h"
#include "msguserinfo.h"
#include "msguserattrib.h"
#include "msgiteminfo.h"

MsgConnect :: MsgConnect(int32_t aAccUID, int32_t aData, const char* aInfo)
    : Msg(sizeof(MsgInfo))
{
    mInfo = (MsgInfo*)mBuf;
    create(aAccUID, aData, aInfo);
}

MsgConnect :: MsgConnect(uint8_t** aBuf, size_t aLen)
    : Msg(aBuf, aLen)
{
    ASSERT(aLen >= sizeof(MsgInfo));

    mInfo = (MsgInfo*)mBuf;
    #if BYTE_ORDER == BIG_ENDIAN
    swap(mBuf);
    #endif
}


MsgConnect :: ~MsgConnect()
{

}

void
MsgConnect :: create(int32_t aAccUID, int32_t aData, const char* aInfo)
{
    ASSERT(aInfo != nullptr);

    if (strlen(aInfo) < MAX_NAMESIZE)
    {
        mInfo->Header.Length = mLen;
        mInfo->Header.Type = MSG_CONNECT;

        mInfo->AccountUID = aAccUID;
        mInfo->Data = aData;
        strcpy(mInfo->Info, aInfo);
    }
    else
    {
        LOG(ERROR, "Invalid length: info=%zu", strlen(aInfo));
    }
}

void
MsgConnect :: process(Client* aClient)
{
    ASSERT(aClient != nullptr);

    Client& client = *aClient;
    Client::Status status = client.getStatus();
    Database& db = Database::getInstance();

    // set the account UID
    client.setAccountID(mInfo->AccountUID);

    switch (status)
    {
        case Client::NOT_AUTHENTICATED: // Sent to the AccServer
        {
            fprintf(stderr, "MsgConnect::process() [AccServer]\n");
            client.disconnect();
            break;
        }
        case Client::NORMAL: // Sent to the MsgServer
        {
            // TODO: load character from DB()
            // TODO: if online, disconnect

            TqCipher& cipher = client.getCipher();
            cipher.generateKey(mInfo->Data, mInfo->AccountUID);

            if (!IS_SUCCESS(db.getPlayerInfo(client)))
            {
                client.disconnect();
                break;
            }

            Msg* msg = nullptr;
            if (client.getPlayer() == nullptr)
            {
                msg = new MsgTalk(STR_SYSTEM_NAME, STR_ALLUSERS_NAME, STR_REPLY_NEW_ROLE, MsgTalk::CHANNEL_ENTRANCE);
                client.send(msg);
                SAFE_DELETE(msg);
            }
            else
            {
                Player& player = *client.getPlayer();

                msg = new MsgTalk(STR_SYSTEM_NAME, STR_ALLUSERS_NAME, STR_REPLY_OK, MsgTalk::CHANNEL_ENTRANCE);
                client.send(msg);
                SAFE_DELETE(msg);

                msg = new MsgUserInfo(player);
                client.send(msg);
                SAFE_DELETE(msg);

                // HACK !
                msg = new MsgUserAttrib(&player, 100, MsgUserAttrib::USER_ATTRIB_ENERGY);
                client.send(msg);
                SAFE_DELETE(msg);

                msg = new MsgTalk("SYSTEM", "ALLUSERS", STR_CREATOR_INFO, MsgTalk::CHANNEL_TALK);
                client.send(msg);
                SAFE_DELETE(msg);

                msg = new MsgTalk("SYSTEM", "ALLUSERS", STR_BUILD_INFO, MsgTalk::CHANNEL_TALK);
                client.send(msg);
                SAFE_DELETE(msg);
            }

            break;
        }
        default: // FIXME !
            ASSERT(false);
            break;
    }
}

void
MsgConnect :: swap(uint8_t* aBuf)
{
    ASSERT(aBuf != nullptr);

    MsgInfo* info = (MsgInfo*)aBuf;

    info->AccountUID = bswap32(info->AccountUID);
    info->Data = bswap32(info->Data);
}
