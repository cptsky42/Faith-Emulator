/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_NPC_TASK_H_
#define _FAITH_EMULATOR_NPC_TASK_H_

#include "common.h"
#include "script.h"
#include <string>

class Client;
struct lua_State;

class NpcTask : public Script
{
public:
    static err_t registerFunctions();

public:
    NpcTask(int32_t aUID, const char* aPath);
    virtual ~NpcTask();

    virtual err_t execute(Client& aClient, int32_t aParam);

private:
    // MsgDialog Lua methods
    static int text(lua_State* aState);
    static int link(lua_State* aState);
    static int pic(lua_State* aState);
    static int create(lua_State* aState);

    // Getters / Setters Lua methods
    static int getMoney(lua_State* aState);

private:
    std::string mFct;
};

#endif // _FAITH_EMULATOR_NPC_TASK_H_