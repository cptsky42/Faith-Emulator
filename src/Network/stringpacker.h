/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_STRINGPACKER_H_
#define _FAITH_EMULATOR_STRINGPACKER_H_

#include "common.h"

class StringPacker
{
public:
    StringPacker(uint8_t* aBuf);
    ~StringPacker();

    void addString(const char* aStr);

private:
    uint8_t* mBuf;
    uint8_t mStrCount;
};

#endif // _FAITH_EMULATOR_STRINGPACKER_H_
