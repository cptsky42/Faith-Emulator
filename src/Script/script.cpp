/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "script.h"
#include "lua.hpp"

/* static */
Script::State* Script::State::sState = nullptr;

/* static */
lua_State&
Script::State :: getState()
{
    // TODO? Thread-safe
    if (sState == nullptr)
    {
        sState = new State();
    }
    return *(sState->mState);
}

Script::State :: State()
{
    mState = luaL_newstate();
    ASSERT(mState != nullptr);
}

Script::State :: ~State()
{
    lua_close(mState);
}





Script :: Script(int32_t aUID, const char* aPath)
    : mUID(aUID)
{
    ASSERT(aPath != nullptr && aPath[0] != '\0');

    lua_State* state = Script::getState();
    luaL_loadfile(state, aPath);
}

Script :: ~Script()
{

}

