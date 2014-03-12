/*
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_NPC_H_
#define _FAITH_EMULATOR_NPC_H_

#include "common.h"
#include "entity.h"
#include <string>

class NpcTask;
class NpcShop;
class Client;
class Player;

/**
 * Base class of all NPC (but not monsters).
 */
class Npc : public Entity
{
    PROHIBIT_COPY(Npc); // constant UID, should be unique...

public:
    /** The type of the NPC. */
    enum Type
    {
        /** No type (invalid). */
        TYPE_NONE = 0,
        /** The NPC is a shop. */
        TYPE_SHOPKEEPER = 1,
        /** The NPC is a task NPC (normal). */
        TYPE_TASK = 2,
        /** The NPC is a storage NPC. */
        TYPE_STORAGE = 3,
        /** The NPC is a trunck NPC. */
        TYPE_TRUNCK = 4,
        /** The NPC can change the face. */
        TYPE_FACE = 5,
        /** The NPC can forge items. */
        TYPE_FORGE = 6, // only used by the client
        /** The NPC can embed gems in items. */
        TYPE_EMBED = 7,

        // type: 2, 6, 9, 21, 22, 23, 24
        _STATUARY_NPC			= 9,			// µñÏñNPC
        _SYNFLAG_NPC			= 10,			// °ïÅÉ±ê¼ÇNPC
        _ROLE_PLAYER			= 11,			// ÆäËûÍæ¼Ò		(only use for client)
        _ROLE_HERO				= 12,			// ×Ô¼º			(only use for client)
        _ROLE_MONSTER			= 13,			// ¹ÖÎï			(only use for client)
        _BOOTH_NPC				= 14,			// °ÚÌ¯NPC		(CBooth class)
        _SYNTRANS_NPC			= 15,			// °ïÅÉ´«ËÍNPC, ¹Ì¶¨ÄÇ¸ö²»ÒªÓÃ´ËÀàÐÍ! (ÓÃÓÚ00:00ÊÕ·Ñ)(LINKIDÎª¹Ì¶¨NPCµÄID£¬ÓëÆäËüÊ¹ÓÃLINKIDµÄ»¥³â)
        _ROLE_BOOTH_FLAG_NPC	= 16,			// Ì¯Î»±êÖ¾NPC	(only use for client)
        _ROLE_MOUSE_NPC			= 17,			// Êó±êÉÏµÄNPC	(only use for client)
        _ROLE_MAGICITEM			= 18,			// ÏÝÚå»ðÇ½		(only use for client)
        _ROLE_DICE_NPC			= 19,			// ÷»×ÓNPC
        _ROLE_SHELF_NPC			= 20,			// ÎïÆ·¼Ü
        _WEAPONGOAL_NPC			= 21,			// ÎäÆ÷°Ð×ÓNPC
        _MAGICGOAL_NPC			= 22,			// Ä§·¨°Ð×ÓNPC
        _BOWGOAL_NPC			= 23,			// ¹­¼ý°Ð×ÓNPC
        _ROLE_TARGET_NPC		= 24,			// °¤´ò£¬²»´¥·¢ÈÎÎñ	(only use for client)
        _ROLE_FURNITURE_NPC		= 25,			// ¼Ò¾ßNPC	(only use for client)
        _ROLE_CITY_GATE_NPC		= 26,			// ³ÇÃÅNPC	(only use for client)
        _ROLE_NEIGHBOR_DOOR		= 27,			// ÁÚ¾ÓµÄÃÅ
        _ROLE_CALL_PET			= 28,			// ÕÙ»½ÊÞ	(only use for client)
        _EUDEMON_TRAINPLACE_NPC	= 29,			// »ÃÊÞÑ±ÑøËù
         _AUCTION_NPC			= 30,			// ÅÄÂòNPC	ÎïÆ·ÁìÈ¡NPC  LW
         _ROLE_MINE_NPC			= 31,			// ¿óÊ¯NPC
    };

    /** The sort of the NPC. */
    enum Sort
    {
        SORT_NONE = 0,
        SORT_TASK = 1,
        SORT_RECYCLE = 2,
        SORT_SCENE = 4,
        SORT_LINKMAP = 8,
        SORT_DIEACTION = 16,
        SORT_DELENABLE = 32,
        SORT_EVENT = 64,
        SORT_TABLE = 128,

        SORT_USELINKID = SORT_LINKMAP | SORT_DIEACTION | SORT_EVENT
    };

    /** Position of the SQL data in the result set. */
    enum SqlData
    {
        SQLDATA_ID = 0,
        SQLDATA_NAME,
        SQLDATA_TYPE,
        SQLDATA_LOOKFACE,
        SQLDATA_MAPID,
        SQLDATA_CELLX,
        SQLDATA_CELLY,
        SQLDATA_LIFE,
        SQLDATA_MAX_LIFE,
        SQLDATA_BASE,
        SQLDATA_SORT
    };

public:
    /* constructor */
    Npc(uint32_t aUID, const char* aName,
        uint8_t aType, uint16_t aLook,
        uint32_t aMapId, uint16_t aPosX, uint16_t aPosY,
        uint8_t aBase, uint8_t aSort);

    /* destructor */
    virtual ~Npc();

public:
    /**
     * Link a task to the NPC.
     *
     * @param[in]    aTask    the new task of the NPC.
     */
    void linkTask(NpcTask* aTask) { ASSERT(aTask != nullptr); mTask = aTask; }

    /**
     * Try to active the NPC.
     *
     * @param[in]   aClient     the client requesting the activation
     * @param[in]   aAction     the action
     *
     * @retval TRUE on success
     * @returns FALSE otherwise
     */
    bool activateNpc(Client& aClient, int32_t aAction);

    /** Send the entity spawn msg. */
    virtual void sendShow(const Player& aPlayer) const;

    /** Called when the timer elapse. */
    virtual void timerElapsed(time_t aTime) { /* TODO npc timerElapsed */  }

public:
    /** Get the type of the NPC. */
    uint8_t getType() const { return mType; }
    /** Get the base of the NPC. */
    uint8_t getBase() const { return mBase; }
    /** Get the sort of the NPC. */
    uint8_t getSort() const { return mSort; }

public:
    /** Determine whether or not the NPC is a shop NPC. */
    bool isShopNpc() const { return mType == TYPE_SHOPKEEPER; }
    /** Get the shop linked to the NPC. */
    const NpcShop& queryShop() const;

    /** Determine whether or not the NPC is a task NPC. */
    bool isTaskNpc() const { return mType == TYPE_TASK || (mSort & SORT_TASK) != 0; }
    /** Get the task linked to the NPC. */
    const NpcTask& queryTask() const { ASSERT(mTask != nullptr); return *mTask; }

    /** Determine whether or not the NPC is a storage NPC. */
    bool isStorageNpc() const { return mType == TYPE_STORAGE; }
    // NpcStorage? queryStorage

private:
    uint8_t mType; //!< the type of the NPC
    uint8_t mBase; //!< the base of the NPC
    uint8_t mSort; //!< the sort of the NPC

    NpcTask* mTask; //!< the task of the NPC
};

#endif // _FAITH_EMULATOR_NPC_H_
