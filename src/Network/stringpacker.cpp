#include "stringpacker.h"
#include <string.h>

StringPacker :: StringPacker(uint8_t* aBuf)
{
    ASSERT(aBuf != nullptr);

    mBuf = aBuf;
    mStrCount = *aBuf;
}

StringPacker :: ~StringPacker()
{

}

void
StringPacker :: addString(const char* aStr)
{
    ASSERT(strlen(aStr) <= UINT8_MAX);

    char* ptr = (char*)(mBuf + 1);
    for (uint8_t i = 0; i < mStrCount; ++i)
    {
        ptr += (uint8_t)*(ptr++); //the length...
    }

    *((uint8_t*)ptr++) = (uint8_t)strlen(aStr);
    strcpy(ptr, aStr);

    *mBuf = ++mStrCount;
}
