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

#ifndef _FAITH_EMULATOR_BINARY_WRITER_H_
#define _FAITH_EMULATOR_BINARY_WRITER_H_

#include "common.h"
#include <string>

/**
  * Initializes a new instance of the BinaryWriter class based on the
  * specified stream.
  * On a Big-Endian architecture, all integers will be swapped.
  */
class BinaryWriter
{
public:
    /** The mode used to open the file. */
    enum FileMode
    {
        NORMAL, //!< Open a file with the position at the start
        APPEND, //!< Open a file with the position at the end
        CREATE  //!< Overwrite the file, else create it
    };

public:
    /**
      * Create a new BinaryWriter and open the underlying stream
      * based on the path and the mode.
      *
      * @param[in]    aPath   the path to the target file
      * @param[in]    aMode   the mode to use to open the file
      */
    BinaryWriter(const char* aPath, FileMode aMode = NORMAL);

    /**
      * Create a new BinaryWriter and open the underlying stream
      * based on the path and the mode.
      *
      * @param[in]    aPath   the path to the target file
      * @param[in]    aMode   the mode to use to open the file
      */
    BinaryWriter(const std::string& aPath, FileMode aMode = NORMAL);

    /* destructor */
    ~BinaryWriter();

    /**
      * Gets a pointer to the base stream used by the BinaryWriter.
      *
      * @returns a pointer to the base stream
      */
    const FILE* getBaseStream() { return mStream; }

    /**
      * Gets the current position of the stream used by the BinaryWriter.
      *
      * @returns the current position of the stream
      */
    int64_t tell();

    /**
      * Changes the current position of the stream based on the seeking
      * mode.
      *
      * @param[in]    aOffset     the relative offset to use
      * @param[in]    aWhence     the seeking mode
      *                           SEEK_SET based on the start of the file
      *                           SEEK_CUR based on the current position
      *                           SEEK_END based on the end of the file
      *
      * @retval BL_ERROR_SUCCESS on success
      * @retval BL_ERROR_FILE_SEEK on seeking error
      * @returns BL error code otherwise
      */
    err_t seek(int64_t aOffset, int aWhence);

    /**
      * Closes the current writer and the underlying stream.
      * All internal buffers associated with the stream are disassociated
      * from it and flushed
      */
    void close();

    /**
      * Gets an exclusive lock on the file.
      */
    err_t lock();

    /**
      * Releases the exclusive lock on the file.
      */
    err_t unlock();

    /**
      * Writes the specified number of bytes to the stream.
      *
      * @param[in]      aBuf    a pointer to the buffer to write
      * @param[in]      aLen    the number of bytes to write
      *
      * @retval BL_ERROR_SUCCESS on success
      * @retval BL_ERROR_FILE_WRITE on writing error
      * @returns BL error code otherwise
      */
    err_t write(const void* aBuf, size_t aLen);

    /**
      * Writes the specified number of bytes to the stream.
      *
      * @param[in]      aBuf    a pointer to the buffer to write
      * @param[in]      aLen    the number of bytes to write
      *
      * @retval BL_ERROR_SUCCESS on success
      * @retval BL_ERROR_FILE_WRITE on writing error
      * @returns BL error code otherwise
      */
    err_t write(void* aBuf, size_t aLen);

    /**
      * Writes a boolean value to the current stream and advances the
      * current position of the stream by one byte.
      *
      * @param[in]    aValue   the value to write
      *
      * @retval BL_ERROR_SUCCESS on success
      * @retval BL_ERROR_FILE_WRITE on writing error
      * @returns BL error code otherwise
      */
    err_t writeBoolean(bool aValue);

    /**
      * Writes a 8-bit unsigned integer value to the current stream and
      * advances the current position of the stream by one byte.
      *
      * @param[in]    aValue   the value to write
      *
      * @retval BL_ERROR_SUCCESS on success
      * @retval BL_ERROR_FILE_WRITE on writing error
      * @returns BL error code otherwise
      */
    err_t writeUInt8(uint8_t aValue);

    /**
      * Writes a 16-bit unsigned integer value to the current stream and
      * advances the current position of the stream by two bytes.
      *
      * @param[in]    aValue   the value to write
      *
      * @retval BL_ERROR_SUCCESS on success
      * @retval BL_ERROR_FILE_WRITE on writing error
      * @returns BL error code otherwise
      */
    err_t writeUInt16(uint16_t aValue);

    /**
      * Writes a 32-bit unsigned integer value to the current stream and
      * advances the current position of the stream by four bytes.
      *
      * @param[in]    aValue   the value to write
      *
      * @retval BL_ERROR_SUCCESS on success
      * @retval BL_ERROR_FILE_WRITE on writing error
      * @returns BL error code otherwise
      */
    err_t writeUInt32(uint32_t aValue);

    /**
      * Writes a 64-bit unsigned integer value to the current stream and
      * advances the current position of the stream by heigt bytes.
      *
      * @param[in]    aValue   the value to write
      *
      * @retval BL_ERROR_SUCCESS on success
      * @retval BL_ERROR_FILE_WRITE on writing error
      * @returns BL error code otherwise
      */
    err_t writeUInt64(uint64_t aValue);

    /**
      * Writes a 8-bit signed integer value to the current stream and
      * advances the current position of the stream by one byte.
      *
      * @param[in]    aValue   the value to write
      *
      * @retval BL_ERROR_SUCCESS on success
      * @retval BL_ERROR_FILE_WRITE on writing error
      * @returns BL error code otherwise
      */
    err_t writeInt8(int8_t aValue);

    /**
      * Writes a 16-bit signed integer value to the current stream and
      * advances the current position of the stream by two bytes.
      *
      * @param[in]    aValue   the value to write
      *
      * @retval BL_ERROR_SUCCESS on success
      * @retval BL_ERROR_FILE_WRITE on writing error
      * @returns BL error code otherwise
      */
    err_t writeInt16(int16_t aValue);

    /**
      * Writes a 32-bit signed integer value to the current stream and
      * advances the current position of the stream by four bytes.
      *
      * @param[in]    aValue   the value to write
      *
      * @retval BL_ERROR_SUCCESS on success
      * @retval BL_ERROR_FILE_WRITE on writing error
      * @returns BL error code otherwise
      */
    err_t writeInt32(int32_t aValue);

    /**
      * Writes a 64-bit signed integer value to the current stream and
      * advances the current position of the stream by heigt bytes.
      *
      * @param[in]    aValue   the value to write
      *
      * @retval BL_ERROR_SUCCESS on success
      * @retval BL_ERROR_FILE_WRITE on writing error
      * @returns BL error code otherwise
      */
    err_t writeInt64(int64_t aValue);

private:
    template<class T>
    err_t write(T aValue);

private:
    FILE* mStream; //!< the base stream of the reader
};

#endif /* _FAITH_EMULATOR_BINARY_WRITER_H_ */
