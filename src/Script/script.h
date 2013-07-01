/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_SCRIPT_H_
#define _FAITH_EMULATOR_SCRIPT_H_

#include "common.h"
#include "env.h"

class Client;
struct lua_State;

class Script
{
public:
    /**
     * Get the Lua VM singleton. If the object does not exist yet,
     * it will be created.
     *
     * @returns A reference to the singleton
     */
    static lua_State* getState() { return &State::getState(); }

public:
    /* destructor */
    virtual ~Script();

    /**
     * Execute the function of the script for the specified client
     * and parameter.
     *
     * @param aClient[in]   the client
     * @param aParam[in]    the param
     *
     * @return
     */
    virtual err_t execute(Client& aClient, int32_t aParam) const = 0;

public:
    int32_t getUID() const { return mUID; }

protected:
    /* constructor */
    Script(int32_t aUID, const char* aPath);

protected:
    const int32_t mUID; //!< The unique ID of the script owner.

private:
    /**
     * The global Lua VM wrapper.
     * It is a singleton and will be created when getting the instance.
     */
    class State : public Environment::Global
    {
    public:
        /**
         * Get the Lua VM singleton. If the object does not exist yet,
         * it will be created.
         *
         * @returns A reference to the singleton
         */
        static lua_State& getState();

    public:
        /* destructor */
        virtual ~State();

    private:
        /* destructor */
        State();

    private:
        static State* sState; //!< static instance of the singleton

    private:
        lua_State* mState; //!< Lua VM state (global due to wrapper)
    };
};

#endif // _FAITH_EMULATOR_SCRIPT_H_
