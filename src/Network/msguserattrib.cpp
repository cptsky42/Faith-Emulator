#include "msguserattrib.h"
#include "client.h"

MsgUserAttrib :: MsgUserAttrib(void* aEntity, int32_t aData, UserAttrType aType)
    : Msg(sizeof(MsgInfo))
{
    mInfo = (MsgInfo*)mBuf;
    create(aEntity, aData, aType);
}

MsgUserAttrib :: MsgUserAttrib(uint8_t** aBuf, size_t aLen)
    : Msg(aBuf, aLen)
{
    ASSERT(aLen >= sizeof(MsgInfo));

    mInfo = (MsgInfo*)mBuf;
    #if BYTE_ORDER == BIG_ENDIAN
    swap(mBuf);
    #endif
}


MsgUserAttrib :: ~MsgUserAttrib()
{

}

void
MsgUserAttrib :: create(void* aEntity, int32_t aData, UserAttrType aType)
{
    ASSERT(aEntity != nullptr);

    mInfo->Header.Length = mLen;
    mInfo->Header.Type = MSG_USERATTRIB;

    mInfo->UniqId = 1000000;
    mInfo->Amount = 1;

    mInfo->Attrib[0].Type = (int32_t)aType;
    mInfo->Attrib[0].Data = aData;
}

void
MsgUserAttrib :: swap(uint8_t* aBuf)
{
    ASSERT(aBuf != nullptr);

    MsgInfo* info = (MsgInfo*)aBuf;

    for (int i = 0; i < info->Amount; ++i)
    {
        info->Attrib[i].Type = bswap32(info->Attrib[i].Type);
        info->Attrib[i].Data = bswap32(info->Attrib[i].Data);
    }
    info->UniqId = bswap32(info->UniqId);
    info->Amount = bswap32(info->Amount);
}
