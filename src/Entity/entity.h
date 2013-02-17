/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_ENTITY_H
#define _FAITH_EMULATOR_ENTITY_H

#include "common.h"

class Entity
{
public:
    static const int32_t SCENEID_FIRST     = 1;
    static const int32_t SYSNPCID_FIRST    = 1;
    static const int32_t SYSNPCID_LAST     = 99999;
    static const int32_t DYNANPCID_FIRST   = 100001;
    static const int32_t DYNANPCID_LAST    = 199999;
    static const int32_t SCENEID_LAST      = 299999;

    static const int32_t NPCSERVERID_FIRST = 400001;
    static const int32_t MONSTERID_FIRST   = 400001;
    static const int32_t MONSTERID_LAST    = 499999;
    static const int32_t PETID_FIRST       = 500001;
    static const int32_t PETID_LAST        = 599999;
    static const int32_t NPCSERVERID_LAST  = 699999;

    static const int32_t CALLPETID_FIRST   = 700001;
    static const int32_t CALLPETID_LAST    = 799999;

    static const int32_t TRAPID_FIRST      = 900001;
    static const int32_t MAGICTRAPID_FIRST = 900001;
    static const int32_t MAGICTRAPID_LAST  = 989999;
    static const int32_t SYSTRAPID_FIRST   = 990001;
    static const int32_t SYSTRAPID_LAST    = 999999;
    static const int32_t TRAPID_LAST       = 999999;

    static const int32_t PLAYERID_FIRST    = 1000000;
    static const int32_t PLAYERID_LAST     = 1999999999;

    static const int32_t CLIENTID_FIRST    = 4000000000;

public:
    static const int32_t CELLS_PER_BLOCK = 18;
    static const int32_t CELLS_PER_VIEW = 18;

public:
    ~Entity();

public:
    int32_t getUniqId() { return mUniqId; }
    int32_t getLook() { return mLook; }
    int16_t getMapId() { return mMapId; }
    uint16_t getPosX() { return mPosX; }
    uint16_t getPosY() { return mPosY; }
    uint8_t getDirection() { return mDirection; }

protected:
    Entity(int32_t aUniqId);

protected:
    const int32_t mUniqId;
    int32_t mLook;
    int16_t mMapId;
    uint16_t mPosX;
    uint16_t mPosY;
    uint8_t mDirection;
};

#endif // _FAITH_EMULATOR_ENTITY_H
