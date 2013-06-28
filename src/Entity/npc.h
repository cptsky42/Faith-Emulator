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

class NpcTask;

class Npc : public Entity
{
    PROHIBIT_COPY(Npc); // constant UID, should be unique...

public:
    // type: 6, 9, 21, 22, 23, 24

public:
    /* constructor */
    Npc(int32_t aUID, const char* aName,
        uint8_t aType, int16_t aLook,
        int16_t aMapId, uint16_t aPosX, uint16_t aPosY,
        uint8_t aBase, uint8_t aSort);

    /* destructor */
    virtual ~Npc();

public:
    uint8_t getType() { return mType; }
    uint8_t getBase() { return mBase; }
    uint8_t getSort() { return mSort; }

    void linkTask(NpcTask* aTask) { mTask = aTask; }

private:
    uint8_t mType;
    uint8_t mBase;
    uint8_t mSort;

    NpcTask* mTask;
};

#endif // _FAITH_EMULATOR_NPC_H
