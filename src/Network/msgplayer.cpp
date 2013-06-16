/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "msgplayer.h"
#include "stringpacker.h"
#include "player.h"
#include <string.h>

MsgPlayer :: MsgPlayer(Player& aPlayer)
    : Msg(sizeof(MsgInfo) +
          strlen(aPlayer.getName()) + 1 + 10)  // TODO: HACK
{
    mInfo = (MsgInfo*)mBuf;
    create(aPlayer);
}

MsgPlayer :: MsgPlayer(uint8_t** aBuf, size_t aLen)
    : Msg(aBuf, aLen)
{
    ASSERT(aLen >= sizeof(MsgInfo));

    mInfo = (MsgInfo*)mBuf;
    #if BYTE_ORDER == BIG_ENDIAN
    swap(mBuf);
    #endif
}

MsgPlayer :: ~MsgPlayer()
{

}

void
MsgPlayer :: create(Player& aPlayer)
{
    ASSERT(&aPlayer != nullptr);
    ASSERT(aPlayer.getName() != nullptr && aPlayer.getName()[0] != '\0');

    if (strlen(aPlayer.getName()) < MAX_NAMESIZE)
    {
        LOG("%d", mLen);
        memset(mInfo, 0, mLen);

        mInfo->Header.Length = mLen;
        mInfo->Header.Type = MSG_PLAYER;

//        mInfo->UniqId = 400002;
//        mInfo->Look = 116;

//        mInfo->Life = 100;
//        mInfo->Level = 12;



        // TODO... fill
//        mInfo->UniqId = aPlayer.getUniqId() + 10;
//        mInfo->Status = 0;//aPlayer.getEffect();
//        mInfo->Look = aPlayer.getLook();
//        mInfo->Hair = aPlayer.getHair();

//        //mInfo->Length = 0; // Unused by EoF
//        //mInfo->Fat = 0; // Unused by EoF

//        mInfo->WeaponRType = 510010;
//        mInfo->WeaponLType = 510010;
//        mInfo->MantleType = 101;
//        mInfo->MountType = 699101;

//        //mInfo->SynId_Rank = 132000;//(aPlayer.getSynRank() << MASK_RANK_SHIFT) | (aPlayer.getSynId() & MASK_SYNID);

        mInfo->PosX = 535;
        mInfo->PosY = 863;
        mInfo->Direction = aPlayer.getDirection();
        mInfo->Pose = 100; //aPlayer.getPose();

        StringPacker packer(mInfo->Buf);
        packer.addString("GhostSpider");

        Msg::dump(this);
    }
    else
    {
        LOG("Invalid length: name=%zu",
            strlen(aPlayer.getName()));
    }
}

void
MsgPlayer :: swap(uint8_t* aBuf)
{
    ASSERT(aBuf != nullptr);

    MsgInfo* info = (MsgInfo*)aBuf;

    // TODO: swap
}
