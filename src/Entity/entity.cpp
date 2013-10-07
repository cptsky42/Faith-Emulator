/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "entity.h"

Entity :: Entity(int32_t aUID)
    : mUID(aUID)
{
    mLook = 0;
    mMapId = 0;
    mPosX = 0;
    mPosY = 0;
    mDirection = 0;
}

Entity :: ~Entity()
{

}
