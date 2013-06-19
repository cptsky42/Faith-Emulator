/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_PLAYER_H
#define _FAITH_EMULATOR_PLAYER_H

#include "common.h"
#include "advancedentity.h"
#include "client.h"
#include <string>

class Player : public AdvancedEntity
{
public:
    Player(Client& aClient);
    virtual ~Player();

    void enterMap();
    void move(uint16_t aX, uint16_t aY, uint8_t);

    void sendSysMsg(const char* aFmt, ...);

    inline void send(Msg* aMsg) { mClient.send(aMsg); }
    inline void send(uint8_t* aBuf, size_t aLen) { mClient.send(aBuf, aLen); }

public:
    const char* getMate() { return mMate.c_str(); }

    int16_t getHair() { return mHair; }

    uint8_t getProfession() { return mProfession; }
    uint8_t getMetempsychosis() { return mMetempsychosis; }
    int32_t getExp() { return mExp; }

    uint16_t getStrength() { return mStrength; }
    uint16_t getAgility() { return mAgility; }
    uint16_t getVitality() { return mVitality; }
    uint16_t getSpirit() { return mSpirit; }
    uint16_t getAddPoints() { return mAddPoints; }

    uint16_t getCurMP() { return mCurMP; }
    uint16_t getMaxMP() { return mMaxMP; }

    int32_t getMoney() { return mMoney; }
    int16_t getPkPoints() { return mPkPoints; }
    int32_t getVirtue() { return mVirtue; }

    uint8_t getEnergy() { return mEnergy; }
    uint8_t getXP() { return mXP; }

    uint16_t getMercenaryExp() { return mMercenaryExp; }
    uint16_t getMercenaryLevel() { return mMercenaryLevel; }

private:
    Client& mClient;

    std::string mMate;

    int16_t mHair;

    uint8_t mProfession;
    uint8_t mMetempsychosis;
    int32_t mExp;

    uint16_t mStrength;
    uint16_t mAgility;
    uint16_t mVitality;
    uint16_t mSpirit;
    uint16_t mAddPoints;

    uint16_t mCurMP;
    uint16_t mMaxMP;

    int32_t mMoney;
    int16_t mPkPoints;
    int32_t mVirtue;

    uint8_t mEnergy;
    uint8_t mXP;

    uint16_t mMercenaryExp;
    uint16_t mMercenaryLevel;

    uint16_t mPrevMap;
    uint16_t mPrevX;
    uint16_t mPrevY;
};

#endif // _FAITH_EMULATOR_PLAYER_H
