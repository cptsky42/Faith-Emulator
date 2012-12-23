#include "msguserinfo.h"
#include "stringpacker.h"
#include <string.h>

// HACK !
const char* name = "CptSky";
const char* mate = "Test";

MsgUserInfo :: MsgUserInfo(void* aEntity)
    : Msg(sizeof(MsgInfo) +
          (name != nullptr ? strlen(name) : 0)  + 1 +
          (mate != nullptr ? strlen(mate) : 0)  + 1)
{
    mInfo = (MsgInfo*)mBuf;
    create(aEntity);
}

MsgUserInfo :: MsgUserInfo(uint8_t** aBuf, size_t aLen)
    : Msg(aBuf, aLen)
{
    ASSERT(aLen >= sizeof(MsgInfo));

    mInfo = (MsgInfo*)mBuf;
    #if BYTE_ORDER == BIG_ENDIAN
    swap(mBuf);
    #endif
}


MsgUserInfo :: ~MsgUserInfo()
{

}

void
MsgUserInfo :: create(void* aEntity)
{
    //ASSERT(aEntity != nullptr);
    ASSERT(name != nullptr && name[0] != '\0');
    ASSERT(mate != nullptr && mate[0] != '\0');

    if (strlen(name) < MAX_NAMESIZE &&
        strlen(mate) < MAX_NAMESIZE)
    {
        mInfo->Header.Length = mLen;
        mInfo->Header.Type = MSG_USERINFO;

        mInfo->UniqId = 1000000;
        mInfo->Look = 1010005;
        mInfo->Hair = 101;
        mInfo->Length = 0;
        mInfo->Fat = 0;
        mInfo->Money = 20000;
        mInfo->Exp = 92134;
        mInfo->MercenaryExp = 10;
        mInfo->MercenaryLevel = 20;
        mInfo->Strength = 5;
        mInfo->Vitality = 7;
        mInfo->Agility = 9;
        mInfo->Spirit = 11;
        mInfo->AddPoints = 3;
        mInfo->CurHP = 150;
        mInfo->CurMP = 100;
        mInfo->PkPoints = 29; // ?
        mInfo->Level = 50;
        mInfo->Profession = 10;
        mInfo->AutoAllot = 1;
        mInfo->Metempsychosis = 1;
        mInfo->ShowName = 1;

        memset(mInfo->Padding1, 0, sizeof(mInfo->Padding1));
        memset(mInfo->Padding2, 0, sizeof(mInfo->Padding2));

        StringPacker packer(mInfo->Buf);
        packer.addString(name);
        packer.addString(mate);
    }
    else
    {
        LOG("Invalid length: name=%zu, mate=%zu",
            strlen(name), strlen(mate));
    }
}

void
MsgUserInfo :: swap(uint8_t* aBuf)
{
    ASSERT(aBuf != nullptr);

    MsgInfo* info = (MsgInfo*)aBuf;

    info->UniqId = bswap32(info->UniqId);
    info->Look = bswap32(info->Look);
    info->Hair = bswap16(info->Hair);
    info->Money = bswap32(info->Money);
    info->Exp = bswap32(info->Exp);
    info->MercenaryExp = bswap16(info->MercenaryExp);
    info->MercenaryLevel = bswap16(info->MercenaryLevel);
    info->Strength = bswap16(info->Strength);
    info->Vitality = bswap16(info->Vitality);
    info->Agility = bswap16(info->Agility);
    info->Spirit = bswap16(info->Spirit);
    info->AddPoints = bswap16(info->AddPoints);
    info->CurHP = bswap16(info->CurHP);
    info->CurMP = bswap16(info->CurMP);
    info->PkPoints = bswap16(info->PkPoints);
}
