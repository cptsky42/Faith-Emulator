/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "world.h"
#include "npc.h"
#include "npctask.h"

using namespace std;

/* static */
World* World::sInstance = nullptr;

/* static */
World&
World :: getInstance()
{
    // TODO? Thread-safe
    if (sInstance == nullptr)
    {
        sInstance = new World();
    }
    return *sInstance;
}

World :: World()
    : AllNPCs(mAllNPCs), AllTasks(mAllTasks)
{

}

World :: ~World()
{
    for (map<int32_t, Npc*>::iterator
            it = mAllNPCs.begin(), end = mAllNPCs.end();
         it != end; ++it)
    {
        Npc* npc = it->second;
        SAFE_DELETE(npc);
    }
    mAllNPCs.clear();

    for (map<int32_t, NpcTask*>::iterator
            it = mAllTasks.begin(), end = mAllTasks.end();
         it != end; ++it)
    {
        NpcTask* task = it->second;
        SAFE_DELETE(task);
    }
    mAllTasks.clear();
}
