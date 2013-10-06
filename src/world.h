/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_WORLD_H_
#define _FAITH_EMULATOR_WORLD_H_

#include "common.h"
#include "env.h"
#include <map>

class Entity;
class AdvancedEntity;
class Player;
class Monster;
class Npc;
class NpcTask;

/**
 * Global world object containing all entities, tasks, etc.
 * It is a singleton and will be created when getting the instance.
 */
class World : public Environment::Global
{
    friend class Database; // loading entities, etc...

    PROHIBIT_COPY(World); // one world per server...

public:
    /**
     * Get the World singleton. If the object does not exist yet,
     * it will be created.
     *
     * @returns A reference to the singleton
     */
    static World& getInstance();

public:
    /* destructor */
    virtual ~World();

public:
    /**
     * Search an entity based on its UID. If the entity is not found,
     * the output entity will be null.
     *
     * @param[in,out]   aOutEntity   a pointer to the object receiving the entity
     * @param[in]       aUID         the UID of the entity
     *
     * @retval TRUE if the entity is found
     * @returns FALSE otherwise
     */
    bool queryEntity(Entity** aOutEntity, int32_t aUID);

    /**
     * Search a NPC based on its UID. If the NPC is not found,
     * the output NPC will be null.
     *
     * @param[in,out]   aOutNpc      a pointer to the object receiving the NPC
     * @param[in]       aUID         the UID of the NPC
     *
     * @retval TRUE if the NPC is found
     * @returns FALSE otherwise
     */
    bool queryNpc(Npc** aOutNpc, int32_t aUID);

private:
    /* constructor */
    World();

private:
    static World* sInstance; //!< static instance of the singleton

private: // aliases
    std::map<int32_t, Npc*>& AllNPCs;
    std::map<int32_t, NpcTask*>& AllTasks;

private:
    std::map<int32_t, Npc*> mAllNPCs; //!< internal map
    std::map<int32_t, NpcTask*> mAllTasks; //!< internal map
};

#endif // _FAITH_EMULATOR_WORLD_H_
