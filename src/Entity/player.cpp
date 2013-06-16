/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "player.h"
#include "msgtalk.h"
#include "msgaction.h"
#include <stdarg.h>

Player :: Player(Client& aClient)
    : Entity(1000000), mClient(aClient)
{
    mName = "CptSky[PM]";
    mMate = "None";

    mLook = 1010005;
    mHair = 101;
    mMoney = 20000;
    mExp = 92134;
    mMercenaryExp = 10;
    mMercenaryLevel = 20;
    mStrength = 5;
    mVitality = 7;
    mAgility = 9;
    mSpirit = 11;
    mAddPoints = 3;
    mCurHP = 150;
    mCurMP = 100;
    mPkPoints = 120; // ?
    mLevel = 50;
    mProfession = 10;
    mMetempsychosis = 2;

    mPosX = 530;
    mPosY = 860;
    mMapId = 1000;
    mDirection = 1;

    mPrevMap = mMapId;
    mPrevX = mPosX;
    mPrevY = mPosY;
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
