/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "msgLoginreplyex.h"
#include "client.h"
#include "player.h"
#include "msgtalk.h"
#include "msguserinfo.h"
#include "msguserattrib.h"
#include "msgiteminfo.h"

MsgLoginReplyEx :: MsgLoginReplyEx(int32_t aAccUID, int32_t aData,
                                   const char* aInfo, int32_t aServerPort,
                                   uint32_t aUin)
    : Msg(sizeof(MsgInfo))
{
    mInfo = (MsgInfo*)mBuf;
    create(aAccUID, aData, aInfo, aServerPort, aUin);
}

MsgLoginReplyEx :: MsgLoginReplyEx(uint8_t** aBuf, size_t aLen)
    : Msg(aBuf, aLen)
{
    ASSERT(aLen >= sizeof(MsgInfo));

    mInfo = (MsgInfo*)mBuf;
    #if BYTE_ORDER == BIG_ENDIAN
    swap(mBuf);
    #endif
}


MsgLoginReplyEx :: ~MsgLoginReplyEx()
{

}

void
MsgLoginReplyEx :: create(int32_t aAccUID, int32_t aData,
                          const char* aInfo, int32_t aServerPort,
                          uint32_t aUin)
{
    ASSERT(aInfo != nullptr);

    if (strlen(aInfo) < MAX_NAMESIZE_CLI)
    {
        mInfo->Header.Length = mLen;
        mInfo->Header.Type = MSG_LOGINREPLYEX;

        mInfo->AccountUID = aAccUID;
        mInfo->Data = aData;
        mInfo->ServerPort = aServerPort;
        mInfo->Uin = aUin;
        strcpy(mInfo->Info, aInfo);
    }
    else
    {
        LOG(ERROR, "Invalid length: info=%zu", strlen(aInfo));
    }
}

void
MsgLoginReplyEx :: swap(uint8_t* aBuf)
{
    ASSERT(aBuf != nullptr);

    MsgInfo* info = (MsgInfo*)aBuf;

    info->AccountUID = bswap32(info->AccountUID);
    info->Data = bswap32(info->Data);
    info->ServerPort = bswap32(info->ServerPort);
    info->Uin = bswap32(info->Uin);
}
