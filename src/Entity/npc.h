/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_NPC_H
#define _FAITH_EMULATOR_NPC_H

#include "common.h"
#include "entity.h"
#include <string>

class Npc : public Entity
{
public:
    Npc(int32_t aUID, const char* aName,
        uint8_t aType, int16_t aLook,
        int16_t aMapId, uint16_t aPosX, uint16_t aPosY,
        uint8_t aBase, uint8_t aSort);
    virtual ~Npc();

public:
    const char* getName() { return (mName.empty() ? nullptr : mName.c_str()); }

    uint8_t getType() { return mType; }
    uint8_t getBase() { return mBase; }
    uint8_t getSort() { return mSort; }

private:
    std::string mName;
    uint8_t mType;
    uint8_t mBase;
    uint8_t mSort;
};

#endif // _FAITH_EMULATOR_NPC_H
