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
    friend class Database; // the database can manipulate the Player data...

    PROHIBIT_COPY(Player); // constant UID, should be unique...

public:
    static const uint16_t LOOK_HUMAN_MALE       = 1;
    static const uint16_t LOOK_HUMAN_FEMALE     = 2;
    static const uint16_t LOOK_ELF_MALE         = 3;
    static const uint16_t LOOK_ELF_FEMALE       = 4;
    static const uint16_t LOOK_DARKELF_MALE     = 5;
    static const uint16_t LOOK_DARKELF_FEMALE   = 6;

    static const uint16_t FACE_INTERN   = 1;
    static const uint16_t FACE_NORMAL   = 101;
    static const uint16_t FACE_VETERAN  = 201;

    static const uint16_t HAIR_FIRST     = 101;
    static const uint16_t HAIR_LAST      = 101; // 107 (XY)

    static const uint8_t PROFESSION_MAGE    = 10;
    static const uint8_t PROFESSION_WARRIOR = 20;
    static const uint8_t PROFESSION_ARCHER  = 30;

public:
    Player(Client& aClient, uint32_t aUID);
    virtual ~Player();

    void enterMap();
    void move(uint16_t aX, uint16_t aY, uint8_t);

    void sendSysMsg(const char* aFmt, ...);

    inline void send(Msg* aMsg) { mClient.send(aMsg); }
    inline void send(uint8_t* aBuf, size_t aLen) { mClient.send(aBuf, aLen); }

public:
    const char* getMate() { return mMate.c_str(); }

    uint16_t getHair() { return mHair; }

    uint8_t getProfession() { return mProfession; }
    uint8_t getMetempsychosis() { return mMetempsychosis; }
    int32_t getExp() { return mExp; }

    uint16_t getForce() { return mForce; }
    uint16_t getSpeed() { return mSpeed; }
    uint16_t getHealth() { return mHealth; }
    uint16_t getSoul() { return mSoul; }
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

    uint16_t mHair;

    uint8_t mProfession;
    uint8_t mMetempsychosis;
    uint32_t mExp;

    uint16_t mForce;
    uint16_t mSpeed;
    uint16_t mHealth;
    uint16_t mSoul;
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
