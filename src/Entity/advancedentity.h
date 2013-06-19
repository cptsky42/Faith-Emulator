/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_ADVANCED_ENTITY_H
#define _FAITH_EMULATOR_ADVANCED_ENTITY_H

#include "common.h"
#include "entity.h"

/**
 * Base class of all advanced entity on a map.
 * An advanced entity can be in a battle.
 */
class AdvancedEntity : public Entity
{
public:
    /* destructor */
    virtual ~AdvancedEntity();

public:
    /** Get the entity's level. */
    uint8_t getLevel() { return mLevel; }

    /** Get the entity's current hit points. */
    uint16_t getCurHP() { return mCurHP; }
    /** Get the entity's max hit points. */
    uint16_t getMaxHP() { return mMaxHP; }

protected:
    /* constructor */
    AdvancedEntity(int32_t aUID);

protected:
    uint8_t mLevel; //!< Entity level

    uint16_t mCurHP; //!< Entity current HP
    uint16_t mMaxHP; //!< Entity max HP

    int32_t mMinAtk;
    int32_t mMaxAtk;
    int32_t mDefense;
    uint8_t mDexterity;
    uint8_t mDodge;
};

#endif // _FAITH_EMULATOR_ADVANCED_ENTITY_H
