/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "npc.h"
#include "npctask.h"

Npc :: Npc(int32_t aUID, const char* aName,
           uint8_t aType, int16_t aLook,
           int16_t aMapId, uint16_t aPosX, uint16_t aPosY,
           uint8_t aBase, uint8_t aSort)
    : Entity(aUID)
{
    if (aName != nullptr)
    {
        mName = aName;
    }

    mType = aType;
    mLook = aLook;
    mDirection = aLook % 10;

    mMapId = aMapId;
    mPosX = aPosX;
    mPosY = aPosY;

    mBase = aBase;
    mSort = aSort;

    mTask = nullptr;
}

Npc :: ~Npc()
{

}
