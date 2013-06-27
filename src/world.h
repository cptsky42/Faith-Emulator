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

class Npc;
class NpcTask;

class World : public Environment::Global
{
public:
    static World& getInstance();

public:
    /* destructor */
    virtual ~World();

public:
    std::map<int32_t, Npc*>& AllNPCs;
    std::map<int32_t, NpcTask*>& AllTasks;

private:
    /* constructor */
    World();

private:
    static World* sInstance; //!< static instance of the singleton

private:
    std::map<int32_t, Npc*> mAllNPCs;
    std::map<int32_t, NpcTask*> mAllTasks;
};

#endif // _FAITH_EMULATOR_WORLD_H_
