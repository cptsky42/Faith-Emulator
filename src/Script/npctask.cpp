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
    err_t err = ERROR_SUCCESS;

    lua_State* state = Script::getState();

    // MsgDialog Lua methods
    lua_register(state, "text", NpcTask::text);
    lua_register(state, "link", NpcTask::link);
    lua_register(state, "pic", NpcTask::pic);
    lua_register(state, "create", NpcTask::create);

    // Getters / Setters Lua methods
    lua_register(state, "getName", NpcTask::getName);
    lua_register(state, "getLook", NpcTask::getLook);
    lua_register(state, "getHair", NpcTask::getHair);
    lua_register(state, "getMoney", NpcTask::getMoney);
    lua_register(state, "getExp", NpcTask::getExp);
    lua_register(state, "getForce", NpcTask::getForce);
    lua_register(state, "getHealth", NpcTask::getHealth);
    lua_register(state, "getSpeed", NpcTask::getSpeed);
    lua_register(state, "getSoul", NpcTask::getSoul);
    lua_register(state, "getAddPoints", NpcTask::getAddPoints);
    lua_register(state, "getCurHP", NpcTask::getCurHP);
    lua_register(state, "getMaxHP", NpcTask::getMaxHP);
    lua_register(state, "getCurMP", NpcTask::getCurMP);
    lua_register(state, "getMaxMP", NpcTask::getMaxMP);
    lua_register(state, "getPkPoints", NpcTask::getPkPoints);
    lua_register(state, "getLevel", NpcTask::getLevel);
    lua_register(state, "getProfession", NpcTask::getProfession);

    return err;
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
NpcTask :: execute(Client& aClient, int32_t aParam) const
{
    err_t err = ERROR_SUCCESS;

    lua_State* state = Script::getState();

    LOG(INFO, "Executing npc task %d with client=%p, param=%d.",
        mUID, &aClient, aParam);

    lua_getglobal(state, mFct.c_str());
    lua_pushinteger(state, (ptrdiff_t)&aClient);
    lua_pushinteger(state, aParam);
    LOG(DBG, "Calling function %s", mFct.c_str());

    int luaerr = lua_pcall(state, 2, 0, 0); // state, nargs, nret, err_fct
    if (LUA_OK != luaerr)
    {
        LOG(ERROR, "Lua error %d calling %s:\n %s",
              luaerr, mFct.c_str(), lua_tostring(state, -1));
        err = ERROR_EXEC_FAILED;
    }

    return err;
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
NpcTask :: getName(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    Player& player = *client.getPlayer();
    ASSERT(&player != nullptr);

    lua_pushstring(aState, player.getName());
    return 1;
}

/* static */
int
NpcTask :: getLook(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    Player& player = *client.getPlayer();
    ASSERT(&player != nullptr);

    lua_pushinteger(aState, player.getLook());
    return 1;
}

/* static */
int
NpcTask :: getHair(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    Player& player = *client.getPlayer();
    ASSERT(&player != nullptr);

    lua_pushinteger(aState, player.getHair());
    return 1;
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

/* static */
int
NpcTask :: getExp(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    Player& player = *client.getPlayer();
    ASSERT(&player != nullptr);

    lua_pushinteger(aState, player.getExp());
    return 1;
}

/* static */
int
NpcTask :: getForce(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    Player& player = *client.getPlayer();
    ASSERT(&player != nullptr);

    lua_pushinteger(aState, player.getForce());
    return 1;
}

/* static */
int
NpcTask :: getHealth(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    Player& player = *client.getPlayer();
    ASSERT(&player != nullptr);

    lua_pushinteger(aState, player.getHealth());
    return 1;
}

/* static */
int
NpcTask :: getSpeed(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    Player& player = *client.getPlayer();
    ASSERT(&player != nullptr);

    lua_pushinteger(aState, player.getSpeed());
    return 1;
}

/* static */
int
NpcTask :: getSoul(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    Player& player = *client.getPlayer();
    ASSERT(&player != nullptr);

    lua_pushinteger(aState, player.getSoul());
    return 1;
}

/* static */
int
NpcTask :: getAddPoints(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    Player& player = *client.getPlayer();
    ASSERT(&player != nullptr);

    lua_pushinteger(aState, player.getAddPoints());
    return 1;
}

/* static */
int
NpcTask :: getCurHP(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    Player& player = *client.getPlayer();
    ASSERT(&player != nullptr);

    lua_pushinteger(aState, player.getCurHP());
    return 1;
}

/* static */
int
NpcTask :: getMaxHP(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    Player& player = *client.getPlayer();
    ASSERT(&player != nullptr);

    lua_pushinteger(aState, player.getMaxHP());
    return 1;
}

/* static */
int
NpcTask :: getCurMP(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    Player& player = *client.getPlayer();
    ASSERT(&player != nullptr);

    lua_pushinteger(aState, player.getCurMP());
    return 1;
}

/* static */
int
NpcTask :: getMaxMP(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    Player& player = *client.getPlayer();
    ASSERT(&player != nullptr);

    lua_pushinteger(aState, player.getMaxMP());
    return 1;
}

/* static */
int
NpcTask :: getPkPoints(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    Player& player = *client.getPlayer();
    ASSERT(&player != nullptr);

    lua_pushinteger(aState, player.getPkPoints());
    return 1;
}

/* static */
int
NpcTask :: getLevel(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    Player& player = *client.getPlayer();
    ASSERT(&player != nullptr);

    lua_pushinteger(aState, player.getLevel());
    return 1;
}

/* static */
int
NpcTask :: getProfession(lua_State* aState)
{
    Client& client = *((Client*)lua_tointeger(aState, 1));
    ASSERT(&client != nullptr);

    Player& player = *client.getPlayer();
    ASSERT(&player != nullptr);

    lua_pushinteger(aState, player.getProfession());
    return 1;
}
