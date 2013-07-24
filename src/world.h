/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_WORLD_H_
#define _FAITH_EMULATOR_WORLD_H_

#include "fscommon.h"
#include "fsenv.h"
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
    bool queryEntity(Entity** aOutEntity, int32_t aUID);
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
