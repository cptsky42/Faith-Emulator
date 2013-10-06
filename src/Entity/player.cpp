/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "player.h"
#include "world.h"
#include "msgtalk.h"
#include "msgaction.h"
#include "msgnpcinfo.h"
#include <stdarg.h>
#include <map>

#include "npc.h"
#include "npctask.h"

using namespace std;

Player :: Player(Client& aClient, uint32_t aUID)
    : AdvancedEntity(aUID), mClient(aClient)
{
    mName = "Unknown";
    mMate = "None";
    mLook = 0;
    mHair = 0;

    mMoney = 0;

    mProfession = 0;
    mLevel = 0;
    mExp = 0;
    mMetempsychosis = 0;

    mForce = 0;
    mSpeed = 0;
    mHealth = 0;
    mSoul = 0;
    mAddPoints = 0;

    mCurHP = 0;
    mCurMP = 0;

    mPkPoints = 0;
    mVirtue = 0;

    mMapId = 0;
    mPosX = 0;
    mPosY = 0;
    mDirection = 1;

    mPrevMap = 0;
    mPrevX = 0;
    mPrevY = 0;

    mMercenaryExp = 0;
    mMercenaryLevel = 0;
}

Player :: ~Player()
{

}

void
Player :: enterMap()
{
//    SendLight();
//    int	nKeepSecs = 0;		// keep light

    MsgAction msg(this, 0xFFFFFF, MsgAction::ACTION_MAP_ARGB); // TODO : get map color
    send(&msg);

    // TODO: HACK!
//    World& world = World::getInstance();
//    NpcTask* task = new NpcTask(21, "/Users/jpboivin/Development/Faith Emulator/data/NPCs/21.lua");
//    for (map<int32_t, Npc*>::iterator
//            it = world.AllNPCs.begin(), end = world.AllNPCs.end();
//         it != end; ++it)
//    {
//        Npc* npc = it->second;

//        if (npc->getMapId() == mMapId)
//        {
//            npc->linkTask(task);

//            MsgNpcInfo info(*npc);
//            send(&info);
//        }
//    }

//	CMapPtr pMap = GetMap();
//	if(pMap)
//	{
//		UpdateBroadcastSet();

//		pMap->EnterRoom(this->QueryMapThing(), WITH_BLOCK);
//		pMap->SendRegionInfo(this);
//		pMap->SendMapInfo(this);
//	}

//	if (pMap && pMap->IsBoothEnable())
//		DetachStatus((IRole*)this, STATUS_XPFULL);

//	CRole::AttachStatus(this->QueryRole(), STATUS_PK_PROTECT, 0, CHGMAP_LOCK_SECS);
}

void
Player :: move(uint16_t aX, uint16_t aY, uint8_t aDir)
{
    mPrevX = mPosX;
    mPrevY = mPosY;

    mPosX = aX;
    mPosY = aY;
    mDirection = aDir;
    // mAction = Action.StandBy; // TODO

    // IsInBattle = false, MagicIntone = false, Mining = false
}

void
Player :: sendSysMsg(const char* aFmt, ...)
{
    va_list args;
    va_start(args, aFmt);

    char buf[MAX_WORDSSIZE];
    vsprintf(buf, aFmt, args);

    MsgTalk msg(STR_SYSTEM_NAME, STR_ALLUSERS_NAME, buf, MsgTalk::CHANNEL_SYSTEM, MsgTalk::COLOR_RED);
    send(&msg);

    va_end(args);
}
