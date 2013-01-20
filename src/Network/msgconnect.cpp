#include "msgconnect.h"
#include "client.h"
#include "msgtalk.h"
#include "msguserinfo.h"
#include "msguserattrib.h"
#include "msgiteminfo.h"

#include <QtCore/QCoreApplication>

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
        LOG("Invalid length: info=%zu", strlen(aInfo));
    }
}

void
MsgConnect :: process(Client* aClient)
{
    ASSERT(aClient != nullptr);

    Client::Status status = aClient->getStatus();
    switch (status)
    {
    case Client::NOT_AUTHENTICATED: // Sent to the AccServer
    {
        // TODO ?
        break;
    }
    case Client::NORMAL: // Sent to the MsgServer
    {
        // TODO: load character from DB()
        // TODO: if online, disconnect

        TqCipher& cipher = aClient->getCipher();
        cipher.generateKey(mInfo->Data, mInfo->AccountUID);

        Msg* msg= nullptr;
        if (false)
        {
            msg = new MsgTalk("SYSTEM", "ALLUSERS", "NEW_ROLE", MsgTalk::CHANNEL_ENTRANCE);
            aClient->send(msg);
            SAFE_DELETE(msg);
        }
        else
        {
            msg = new MsgTalk("SYSTEM", "ALLUSERS", "ANSWER_OK", MsgTalk::CHANNEL_ENTRANCE);
            aClient->send(msg);
            SAFE_DELETE(msg);

            msg = new MsgUserInfo(nullptr);
            aClient->send(msg);
            SAFE_DELETE(msg);

            // HACK !
            msg = new MsgUserAttrib(aClient, 100, MsgUserAttrib::USER_ATTRIB_ENERGY);
            aClient->send(msg);
            SAFE_DELETE(msg);

            // TODO... Clean the following code...
            msg = new MsgTalk("SYSTEM", "ALLUSERS", "Faith Emulator by CptSky...", MsgTalk::CHANNEL_TALK);
            aClient->send(msg);
            SAFE_DELETE(msg);

            char str[4096];
            sprintf(str, "Build for %s (%s), using Qt %s, the %s...\n",
                    TARGET_SYSTEM, TARGET_ARCH, QT_VERSION_STR, __TIMESTAMP__);
            msg = new MsgTalk("SYSTEM", "ALLUSERS", str, MsgTalk::CHANNEL_TALK);
            aClient->send(msg);
            SAFE_DELETE(msg);

            msg = new MsgItemInfo(nullptr, MsgItemInfo::ACTION_ADD_ITEM);
            aClient->send(msg);
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
