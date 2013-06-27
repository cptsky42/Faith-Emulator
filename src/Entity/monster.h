/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_MONSTER_H
#define _FAITH_EMULATOR_MONSTER_H

#include "common.h"
#include "advancedentity.h"
#include <string>

class Monster : public AdvancedEntity
{
    PROHIBIT_COPY(Monster); // constant UID, should be unique...

public:
    struct Info
    {
    public:
        int32_t Id;
        std::string Name;
        uint8_t Type;
        int32_t Look;
        uint8_t Level;
        uint16_t Life;
        uint16_t EscapeLife;
        int32_t MinAtk;
        int32_t MaxAtk;
        int32_t Defense;
        uint8_t Dexterity;
        uint8_t Dodge;
        uint8_t ViewRange;
        uint16_t AtkSpeed;
        uint16_t MoveSpeed;
        bool Defy;
    };

public:
    /* constructor */
    Monster(int32_t aUID, Monster::Info& aInfo);

    /* destructor */
    virtual ~Monster();

private:
    int32_t mId;
    uint8_t mType;
    uint16_t mEscapeLife;

    uint8_t mViewRange;
    uint16_t mAtkSpeed;
    uint16_t mMoveSpeed;

    bool mDefy;
};

#endif // _FAITH_EMULATOR_MONSTER_H
