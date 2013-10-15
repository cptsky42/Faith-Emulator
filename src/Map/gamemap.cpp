/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "gamemap.h"
#include "entity.h"

GameMap :: GameMap(int32_t aUID, Info** aInfo, MapData& aData)
    : mUID(aUID), mInfo(*aInfo), mData(aData)
{
    ASSERT(aInfo != nullptr && *aInfo != nullptr);
    *aInfo = nullptr;
}

GameMap :: ~GameMap()
{
    SAFE_DELETE(mInfo);
}

bool
GameMap :: getFloorAccess(uint16_t aPosX, uint16_t aPosY) const
{
    const Cell& cell = mData.getCell(aPosX, aPosY);
    return cell.Accessible;
}

int16_t
GameMap :: getFloorAlt(uint16_t aPosX, uint16_t aPosY) const
{
    const Cell& cell = mData.getCell(aPosX, aPosY);
    return cell.Altitude;
}


void
GameMap :: enterRoom(Entity& aEntity)
{
    // activate the map...
    if (mEntities.size() == 0)
    {
        mData.unpack();
    }

    //TODO
    mEntities[aEntity.getUID()] = &aEntity;
}

void
GameMap :: leaveRoom(Entity& aEntity)
{
    // TODO

    // desactivate the map...
    if (mEntities.size() == 0)
    {
        mData.pack();
    }
}
