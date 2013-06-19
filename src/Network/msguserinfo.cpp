/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "msguserinfo.h"
#include "stringpacker.h"
#include "player.h"
#include <string.h>

MsgUserInfo :: MsgUserInfo(Player& aPlayer)
    : Msg(sizeof(MsgInfo) +
          strlen(aPlayer.getName()) + 1 +
          strlen(aPlayer.getMate()) + 1)
{
    mInfo = (MsgInfo*)mBuf;
    create(aPlayer);
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
MsgUserInfo :: create(Player& aPlayer)
{
    ASSERT(&aPlayer != nullptr);
    ASSERT(aPlayer.getName() != nullptr && aPlayer.getName()[0] != '\0');
    ASSERT(aPlayer.getMate() != nullptr && aPlayer.getMate()[0] != '\0');

    if (strlen(aPlayer.getName()) < MAX_NAMESIZE &&
        strlen(aPlayer.getMate()) < MAX_NAMESIZE)
    {
        mInfo->Header.Length = mLen;
        mInfo->Header.Type = MSG_USERINFO;

        mInfo->UniqId = aPlayer.getUID();
        mInfo->Look = aPlayer.getLook();
        mInfo->Hair = aPlayer.getHair();
        mInfo->Length = 0; // unused by EoF
        mInfo->Fat = 0; // unused by EoF
        mInfo->Money = aPlayer.getMoney();
        mInfo->Exp = aPlayer.getExp();
        mInfo->MercenaryExp = aPlayer.getMercenaryExp();
        mInfo->MercenaryLevel = aPlayer.getMercenaryLevel();
        mInfo->Strength = aPlayer.getStrength();
        mInfo->Vitality = aPlayer.getVitality();
        mInfo->Agility = aPlayer.getAgility();
        mInfo->Spirit = aPlayer.getSpirit();
        mInfo->AddPoints = aPlayer.getAddPoints();
        mInfo->CurHP = aPlayer.getCurHP();
        mInfo->CurMP = aPlayer.getCurMP();
        mInfo->PkPoints = aPlayer.getPkPoints(); // ?
        mInfo->Level = aPlayer.getLevel();
        mInfo->Profession = aPlayer.getProfession();
        mInfo->AutoAllot = 1; // not really used by the client...
        mInfo->Metempsychosis = aPlayer.getMetempsychosis();
        mInfo->ShowName = 1;

        memset(mInfo->Padding1, 0, sizeof(mInfo->Padding1));
        memset(mInfo->Padding2, 0, sizeof(mInfo->Padding2));

        StringPacker packer(mInfo->Buf);
        packer.addString(aPlayer.getName());
        packer.addString(aPlayer.getMate());
    }
    else
    {
        LOG("Invalid length: name=%zu, mate=%zu",
            strlen(aPlayer.getName()), strlen(aPlayer.getMate()));
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
