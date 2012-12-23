#include "MsgItemInfo.h"

MsgItemInfo :: MsgItemInfo(void* aItem, Action aAction)
    : Msg(sizeof(MsgInfo))
{
    mInfo = (MsgInfo*)mBuf;
    create(aItem, aAction);
}

MsgItemInfo :: MsgItemInfo(uint8_t** aBuf, size_t aLen)
    : Msg(aBuf, aLen)
{
    ASSERT(aLen >= sizeof(MsgInfo));

    mInfo = (MsgInfo*)mBuf;
    #if BYTE_ORDER == BIG_ENDIAN
    swap(mBuf);
    #endif
}


MsgItemInfo :: ~MsgItemInfo()
{

}

void
MsgItemInfo :: create(void* aItem, Action aAction)
{
    //ASSERT(aItem != nullptr);

    mInfo->Header.Length = mLen;
    mInfo->Header.Type = MSG_ITEMINFO;

    mInfo->UniqId = 1000000;
    mInfo->Type = 132000;
    mInfo->Amount = 10099;
    mInfo->AmountLimit = 10099;
    mInfo->Action = (uint8_t)aAction;
    mInfo->Ident = 0;
    mInfo->Position = 3;
    mInfo->Gem1 = 1;
    mInfo->Gem2 = 1;
    mInfo->Magic1 = 2;
    mInfo->Magic2 = 0;
    mInfo->Magic3 = 9;
}

void
MsgItemInfo :: swap(uint8_t* aBuf)
{
    ASSERT(aBuf != nullptr);

    MsgInfo* info = (MsgInfo*)aBuf;

    info->UniqId = bswap32(info->UniqId);
    info->Type = bswap32(info->Type);
    info->Amount = bswap16(info->Amount);
    info->AmountLimit = bswap16(info->AmountLimit);
}
