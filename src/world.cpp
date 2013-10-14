/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "world.h"
#include "player.h"
#include "npc.h"
#include "npctask.h"
#include <QThread>

using namespace std;

class Worker : public QThread
{
public:
    Worker() : mTerminate(false) { }
    virtual ~Worker() { }

public slots:
    virtual void terminate()
    {
        mTerminate = true;
        QThread::terminate();
    }

private:
    virtual void run()
    {
        World& world = World::getInstance();

        // TODO: with all entities... maps, items, magics
//        while (!mTerminate)
//        {
//            for (map<int32_t, Player*>::const_iterator
//                    it = world.AllPlayers.begin(), end = world.AllPlayers.end();
//                 !mTerminate && it != end; ++it)
//            {
//                Player* player = it->second;
//                player->timerElapsed(0); // TODO pass time ?

//                yieldCurrentThread();
//            }

//            usleep(250);
//        }
    }

private:
    bool mTerminate;
};

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
    : AllPlayers(mAllPlayers), AllNPCs(mAllNPCs), AllTasks(mAllTasks)
{
    mWorker = new Worker();
    mWorker->start(QThread::LowPriority);
}

World :: ~World()
{
    mWorker->terminate();
    mWorker->wait(10000); // wait 10s...
    SAFE_DELETE(mWorker);

    // clients will free the players...
    mAllPlayers.clear();

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

bool
World :: queryNpc(Npc** aOutNpc, int32_t aUID) const
{
    ASSERT_ERR(aOutNpc != nullptr && *aOutNpc == nullptr, false);
    ASSERT_ERR(Entity::isNpc(aUID), false);

    // TODO: Thread-safe ?

    bool found = false;
    map<int32_t, Npc*>::const_iterator it;

    if ((it = mAllNPCs.find(aUID)) != mAllNPCs.end())
    {
        *aOutNpc = it->second;
        found = true;
    }

    return found;
}
