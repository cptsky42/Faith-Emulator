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

#include "binarywriter.h"
#include "finder.h"
#include <stdio.h>

using namespace std;

BinaryWriter :: BinaryWriter(const char* aPath, FileMode aMode)
{
    mStream = nullptr;
    ASSERT(aPath != nullptr && aPath[0] != '\0');

    switch (aMode)
    {
        case NORMAL:
            ASSERT(ERROR_SUCCESS == Finder::fileOpen(&mStream, aPath, "r+"));
            break;
        case APPEND:
            ASSERT(ERROR_SUCCESS == Finder::fileOpen(&mStream, aPath, "a"));
            break;
        case CREATE:
            ASSERT(ERROR_SUCCESS == Finder::fileOpen(&mStream, aPath, "w"));
            break;
        default:
            ASSERT(false);
            break;
    }
}

BinaryWriter :: BinaryWriter(const string& aPath, FileMode aMode)
{
    mStream = nullptr;
    ASSERT(&aPath != nullptr);
    ASSERT(!aPath.empty());

    switch (aMode)
    {
        case NORMAL:
            ASSERT(ERROR_SUCCESS == Finder::fileOpen(&mStream, aPath.c_str(), "r+"));
            break;
        case APPEND:
            ASSERT(ERROR_SUCCESS == Finder::fileOpen(&mStream, aPath.c_str(), "a"));
            break;
        case CREATE:
            ASSERT(ERROR_SUCCESS == Finder::fileOpen(&mStream, aPath.c_str(), "w"));
            break;
        default:
            ASSERT(false);
            break;
    }
}

BinaryWriter :: ~BinaryWriter()
{
    close();
}

int64_t
BinaryWriter :: tell()
{
    ASSERT_ERR(mStream != nullptr, ERROR_BAD_STATE);

    return Finder::fileTell(mStream);
}


err_t
BinaryWriter :: seek(int64_t aOffset, int aWhence)
{
    ASSERT_ERR(mStream != nullptr, ERROR_BAD_STATE);

    return Finder::fileSeek(mStream, aOffset, aWhence);
}


void
BinaryWriter :: close()
{
    if (mStream != nullptr)
    {
        fclose(mStream);
        mStream = nullptr;
    }
}

err_t
BinaryWriter :: lock()
{
    ASSERT_ERR(mStream != nullptr, ERROR_BAD_STATE);

    return Finder::fileLock(mStream);
}

err_t
BinaryWriter :: unlock()
{
    ASSERT_ERR(mStream != nullptr, ERROR_BAD_STATE);

    return Finder::fileUnlock(mStream);
}

err_t
BinaryWriter :: writeUInt8(uint8_t aValue)
{
    return writeInt8((int8_t)aValue);
}

err_t
BinaryWriter :: writeUInt16(uint16_t aValue)
{
    return writeInt16((int16_t)aValue);
}

err_t
BinaryWriter :: writeUInt32(uint32_t aValue)
{
    return writeInt32((int32_t)aValue);
}

err_t
BinaryWriter :: writeUInt64(uint64_t aValue)
{
    return writeInt64((int64_t)aValue);
}

err_t
BinaryWriter :: write(const void* aBuf, size_t aLen)
{
    return write((void*)aBuf, aLen);
}

template<class T>
err_t
BinaryWriter :: write(T aValue)
{
    err_t err = ERROR_SUCCESS;

    if (fwrite(&aValue, sizeof(aValue), 1, mStream) != 1)
    {
        err = ERROR_WRITE_FAULT;
    }

    return err;
}

template err_t BinaryWriter :: write<int8_t>(int8_t aValue);
template err_t BinaryWriter :: write<int16_t>(int16_t aValue);
template err_t BinaryWriter :: write<int32_t>(int32_t aValue);
template err_t BinaryWriter :: write<int64_t>(int64_t aValue);

template<class T>
err_t
BinaryWriter :: writePckInt(T aValue)
{
    err_t err = ERROR_SUCCESS;

    while (ERROR_SUCCESS == err &&
           aValue >= (T)128)
    {
        err = writeUInt8((uint8_t)(aValue | (T)128));
        aValue >>= 7;
    }
    DOIF(err, writeUInt8((uint8_t)aValue));

    return err;
}

template err_t BinaryWriter :: writePckInt<uint8_t>(uint8_t aValue);
template err_t BinaryWriter :: writePckInt<uint16_t>(uint16_t aValue);
template err_t BinaryWriter :: writePckInt<uint32_t>(uint32_t aValue);
template err_t BinaryWriter :: writePckInt<uint64_t>(uint64_t aValue);


err_t
BinaryWriter :: write(void* aBuf, size_t aLen)
{
    ASSERT_ERR(aBuf != nullptr, ERROR_BAD_PARAMS);
    ASSERT_ERR(mStream != nullptr, ERROR_BAD_STATE);
    ASSERT_ERR(feof(mStream) == 0, ERROR_BAD_STATE);

    err_t err = ERROR_SUCCESS;

    if (fwrite(aBuf, sizeof(uint8_t), aLen, mStream) != aLen)
    {
        err = ERROR_WRITE_FAULT;
    }

    return err;
}


err_t
BinaryWriter :: writeBoolean(bool aValue)
{
    ASSERT_ERR(mStream != nullptr, ERROR_BAD_STATE);
    ASSERT_ERR(feof(mStream) == 0, ERROR_BAD_STATE);

    err_t err = ERROR_SUCCESS;

    int8_t val = aValue ? 1 : 0;
    DOIF(err, write<int8_t>(val));

    return err;
}

err_t
BinaryWriter :: writeInt8(int8_t aValue)
{
    ASSERT_ERR(mStream != nullptr, ERROR_BAD_STATE);
    ASSERT_ERR(feof(mStream) == 0, ERROR_BAD_STATE);

    err_t err = ERROR_SUCCESS;

    DOIF(err, write<int8_t>(aValue));

    return err;
}

err_t
BinaryWriter :: writeInt16(int16_t aValue)
{
    ASSERT_ERR(mStream != nullptr, ERROR_BAD_STATE);
    ASSERT_ERR(feof(mStream) == 0, ERROR_BAD_STATE);

    err_t err = ERROR_SUCCESS;

    #if BYTE_ORDER == BIG_ENDIAN
    aValue = bswap16(aValue);
    #endif
    DOIF(err, write<int16_t>(aValue));

    return err;
}

err_t
BinaryWriter :: writeInt32(int32_t aValue)
{
    ASSERT_ERR(mStream != nullptr, ERROR_BAD_STATE);
    ASSERT_ERR(feof(mStream) == 0, ERROR_BAD_STATE);

    err_t err = ERROR_SUCCESS;

    #if BYTE_ORDER == BIG_ENDIAN
    aValue = bswap32(aValue);
    #endif
    DOIF(err, write<int32_t>(aValue));

    return err;
}

err_t
BinaryWriter :: writeInt64(int64_t aValue)
{
    ASSERT_ERR(mStream != nullptr, ERROR_BAD_STATE);
    ASSERT_ERR(feof(mStream) == 0, ERROR_BAD_STATE);

    err_t err = ERROR_SUCCESS;

    #if BYTE_ORDER == BIG_ENDIAN
    aValue = bswap64(aValue);
    #endif
    DOIF(err, write<int64_t>(aValue));

    return err;
}
