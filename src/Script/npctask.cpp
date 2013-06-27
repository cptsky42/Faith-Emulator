/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "npctask.h"
#include "client.h"
#include "player.h"
#include "msgdialog.h"
#include "lua.hpp"

/* static */
err_t
NpcTask :: registerFunctions()
{
    lua_State* state = Script::getState();

    // MsgDialog Lua methods
    lua_register(state, "text", NpcTask::text);
    lua_register(state, "link", NpcTask::link);
    lua_register(state, "pic", NpcTask::pic);
    lua_register(state, "create", NpcTask::create);

    // Getters / Setters Lua methods
    lua_register(state, "getMoney", NpcTask::getMoney);
}

NpcTask :: NpcTask(int32_t aUID, const char* aPath)
    : Script(aUID, aPath)
{
    char fct[128];
    snprintf(fct, sizeof(fct), "processTask%d", aUID);

    mFct = fct;
}

NpcTask :: ~NpcTask()
{

}

err_t
NpcTask :: execute(Client& aClient, int32_t aParam)
{
    lua_State* state = Script::getState();

    lua_getglobal(state, mFct.c_str());
    lua_pushinteger(state, (ptrdiff_t)&aClient);
    lua_pushinteger(state, aParam);
    lua_call(state, 2, 0);  /* call Lua function */
}




/* static */
int
NpcTask :: text(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    const char* text = lua_tolstring(aState, 2, nullptr);

    MsgDialog msg(text, 0, 0, MsgDialog::ACTION_TEXT);
    client.send(&msg);

    return 0;
}

/* static */
int
NpcTask :: link(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    const char* text = lua_tolstring(aState, 2, nullptr);
    int idx = lua_tointeger(aState, 3);

    MsgDialog msg(text, 0, idx, MsgDialog::ACTION_LINK);
    client.send(&msg);

    return 0;
}

/* static */
int
NpcTask :: pic(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    int pic = lua_tointeger(aState, 2);

    MsgDialog msg(0, 0, pic, 0, MsgDialog::ACTION_PIC);
    client.send(&msg);

    return 0;
}

/* static */
int
NpcTask :: create(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    MsgDialog msg(0xFF, MsgDialog::ACTION_CREATE);
    client.send(&msg);

    return 0;
}

/* static */
int
NpcTask :: getMoney(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    Player& player = *client.getPlayer();
    ASSERT(&player != nullptr);

    lua_pushinteger(aState, player.getMoney());
    return 1;
}
