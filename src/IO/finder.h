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


#ifndef _FAITH_EMULATOR_FINDER_H_
#define _FAITH_EMULATOR_FINDER_H_

#include "common.h"
#include <stdio.h>

/**
  *
  */
class Finder
{
public:
    /**
      * Open the file pointed by the path with the "C" mode. The file
      * descriptor is returned.
      *
      * @param[out] aOutFile   a pointer to the object that will receive
      *                        the file descriptor
      * @param[in]  aPath      the path of the file to open
      * @param[in]  aMode      the "C" mode to use to open the file (e.g. w)
      *
      * @retval ERROR_SUCCESS on success
      * @retval ERROR_OPEN_FAILED on failure
      * @returns Error code otherwise
      */
    static err_t fileOpen(FILE** aOutFile,
                            const char* aPath, const char* aMode);

    /**
      * Get the file handle from the specified file descriptor.
      *
      * @param[in]  aFile   the file descriptor
      *
      * @returns The handle of the specified file
      */
    static int fileHandle(FILE* aFile);

    /**
      * Get an exclusive lock on the file pointed by the file descriptor.
      *
      * @param[in]  aFile   the file descriptor
      *
      * @retval ERROR_SUCCESS on success
      * @returns Error code otherwise
      */
    static err_t fileLock(FILE* aFile);

    /**
      * Release the exclusive lock on the file pointed by the file
      * descriptor.
      *
      * @param[in]  aFile   the file descriptor
      *
      * @retval ERROR_SUCCESS on success
      * @returns Error code otherwise
      */
    static err_t fileUnlock(FILE* aFile);

    static int64_t fileTell(FILE* aFile);
    static err_t fileSeek(FILE* aFile, int64_t aOffset, int aWhence);

    static bool fileExists(const char* aPath);

    static FILE* getTempFile();
};

#endif /* _FAITH_EMULATOR_FINDER_H_ */
