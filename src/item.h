/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_ITEM_H_
#define _FAITH_EMULATOR_ITEM_H_

#include "common.h"

class Item
{
public:
    struct Info
    {
    public:
        int32_t Id;
    };

public:
    Item(int32_t aUID, Item::Info& aInfo);
    ~Item();

private:
    const int32_t mUID;
    Item::Info& mInfo;
};

#endif // _FAITH_EMULATOR_ITEM_H_
