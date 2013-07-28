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
    PROHIBIT_COPY(AdvancedEntity); // constant UID, should be unique...

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

    /** Get the entity's pose. */
    uint16_t getPose() { return mPose; }

protected:
    /* constructor */
    AdvancedEntity(int32_t aUID);

protected:
    uint8_t mLevel; //!< Entity level

    uint16_t mCurHP; //!< Entity current HP
    uint16_t mMaxHP; //!< Entity max HP

    int32_t mMinAtk; //!< Entity minimum attack
    int32_t mMaxAtk; //!< Entity maximum attack
    int32_t mDefense; //!< Entity defense
    uint8_t mDexterity; //!< Entity dexterity
    uint8_t mDodge; //!< Entity dodge

    uint16_t mPose; //!< Entity pose
};

#endif // _FAITH_EMULATOR_ADVANCED_ENTITY_H
