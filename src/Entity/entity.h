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

/**
 * Base class of all entity on a map.
 */
class Entity
{
    PROHIBIT_COPY(Entity); // constant UID, should be unique...

public:
    /** First valid UID for a NPC. */
    static const int32_t SCENEID_FIRST     = 1;
    /** First valid UID for a system NPC. */
    static const int32_t SYSNPCID_FIRST    = 1;
    /** Last valid UID for a system NPC. */
    static const int32_t SYSNPCID_LAST     = 99999;
    /** First valid UID for a user/dynamic NPC. */
    static const int32_t DYNANPCID_FIRST   = 100001;
    /** Last valid UID for a user/dynamic NPC. */
    static const int32_t DYNANPCID_LAST    = 199999;
    /** Last valid UID for a NPC. */
    static const int32_t SCENEID_LAST      = 299999;

    /** First valid UID for an advanced NPC. */
    static const int32_t NPCSERVERID_FIRST = 400001;
    /** First valid UID for a monster. */
    static const int32_t MONSTERID_FIRST   = 400001;
    /** Last valid UID for a monster. */
    static const int32_t MONSTERID_LAST    = 499999;
    /** First valid UID for a pet. */
    static const int32_t PETID_FIRST       = 500001;
    /** Last valid UID for a pet. */
    static const int32_t PETID_LAST        = 599999;
    /** Last valid UID for an advanced NPC. */
    static const int32_t NPCSERVERID_LAST  = 699999;

    /** First valid UID for a called pet. */
    static const int32_t CALLPETID_FIRST   = 700001;
    /** Last valid UID for a called pet. */
    static const int32_t CALLPETID_LAST    = 799999;

    // unused for the moment ?
    static const int32_t TRAPID_FIRST      = 900001;
    static const int32_t MAGICTRAPID_FIRST = 900001;
    static const int32_t MAGICTRAPID_LAST  = 989999;
    static const int32_t SYSTRAPID_FIRST   = 990001;
    static const int32_t SYSTRAPID_LAST    = 999999;
    static const int32_t TRAPID_LAST       = 999999;

    /** First valid UID for a player. */
    static const int32_t PLAYERID_FIRST    = 1000000;
    /** Last valid UID for a player. */
    static const int32_t PLAYERID_LAST     = 1999999999;

public:
    /** Number of cells per block. */
    static const int32_t CELLS_PER_BLOCK = 18;
    /** Number of cells per view. */
    static const int32_t CELLS_PER_VIEW = 18;

public:
    /** Determine wheter or not the entity linked to the UID is a NPC. */
    static bool isNpc(int32_t aUID) { return aUID >= SCENEID_FIRST && aUID <= SCENEID_LAST; }
    /** Determine wheter or not the entity linked to the UID is a system NPC. */
    static bool isSysNpc(int32_t aUID) { return aUID >= SYSNPCID_FIRST && aUID <= SYSNPCID_LAST; }
    /** Determine wheter or not the entity linked to the UID is a user/dynamic NPC. */
    static bool isDynNpc(int32_t aUID) { return aUID >= DYNANPCID_FIRST && aUID <= DYNANPCID_LAST; }
    /** Determine wheter or not the entity linked to the UID is a monster. */
    static bool isMonster(int32_t aUID) { return aUID >= MONSTERID_FIRST && aUID <= MONSTERID_LAST; }
    /** Determine wheter or not the entity linked to the UID is a pet. */
    static bool isPet(int32_t aUID) { return aUID >= PETID_FIRST && aUID <= PETID_LAST; }
    /** Determine wheter or not the entity linked to the UID is a called pet. */
    static bool isCallPet(int32_t aUID) { return aUID >= CALLPETID_FIRST && aUID <= CALLPETID_LAST; }
    /** Determine wheter or not the entity linked to the UID is a player. */
    static bool isPlayer(int32_t aUID) { return aUID >= PLAYERID_FIRST && aUID <= PLAYERID_LAST; }

public:
    /** Determine wheter or not the entity is a NPC. */
    bool isNpc() { return isNpc(mUID); }
    /** Determine wheter or not the entity is a system NPC. */
    bool isSysNpc() { return isSysNpc(mUID); }
    /** Determine wheter or not the entity is a user/dynamic NPC. */
    bool isDynNpc() { return isDynNpc(mUID); }
    /** Determine wheter or not the entity is a monster. */
    bool isMonster() { return isMonster(mUID); }
    /** Determine wheter or not the entity is a pet. */
    bool isPet() { return isPet(mUID); }
    /** Determine wheter or not the entity is a called pet. */
    bool isCallPet() { return isCallPet(mUID); }
    /** Determine wheter or not the entity is a player. */
    bool isPlayer() { return isPlayer(mUID); }

public:
    /* destructor */
    virtual ~Entity();

public:
    /** Get the entity's UID. */
    int32_t getUID() { return mUID; }

    /** Get the entity's name. */
    const char* getName() { return (mName.empty() ? nullptr : mName.c_str());  }
    /** Get the entity's look/face. */
    int32_t getLook() { return mLook; }

    /** Get the entity's map UID. */
    int16_t getMapId() { return mMapId; }
    /** Get the entity's X coord. */
    uint16_t getPosX() { return mPosX; }
    /** Get the entity's Y coord. */
    uint16_t getPosY() { return mPosY; }
    /** Get the cardinal direction of the entity. */
    uint8_t getDirection() { return mDirection; }

    /** Set the map UID of the entity. */
    void setMapId(int16_t aMapId) { mMapId = aMapId; }
    /** Set the position on the map of the entity. */
    void setPosition(uint16_t aPosX, uint16_t aPosY) { mPosX = aPosX; mPosY = aPosY; }
    /** Set the cardinal direction of the entity. */
    void setDirection(uint8_t aDirection) { mDirection = aDirection; }

protected:
    /* constructor */
    Entity(int32_t aUID);

protected:
    const int32_t mUID; //!< Entity UID

    std::string mName; //!< Entity name
    int32_t mLook; //!< Entity look/face

    int16_t mMapId; //!< Entity map UID
    uint16_t mPosX; //!< Entity X coord.
    uint16_t mPosY; //!< Entity Y coord.
    uint8_t mDirection; //!< Entity cardinal direction
};

#endif // _FAITH_EMULATOR_ENTITY_H
