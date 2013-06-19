/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Taken from :
 * ****** BARLab - Open Source ******
 * Copyright (C) 2012 BARLab
 * Copyright (C) 2012 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_ENVIRONMENT_H_
#define _FAITH_EMULATOR_ENVIRONMENT_H_

#include "common.h"
#include <vector>

class Environment
{
public:
    class Global
    {
        friend class Environment;

        PROHIBIT_COPY(Global);

    public:
        virtual ~Global()
        {
            Environment& env = Environment::getInstance();
            env.unregisterObj(this);
        }

    protected:
        Global()
        {
            Environment& env = Environment::getInstance();
            env.registerObj(this);
        }
    };

public:
    static Environment& getInstance();

public:
    ~Environment();

private:
    static void destroy();

private:
    Environment();
    void registerObj(Global* aObj);
    void unregisterObj(Global* aObj);

private:
    static Environment* sInstance;

private:
    std::vector<Global*> mObjects;
    bool mIsDestroying;
};

#endif // _FAITH_EMULATOR_ENVIRONMENT_H_
