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

#ifndef _FAITH_EMULATOR_LOG_H_
#define _FAITH_EMULATOR_LOG_H_

#include <stdio.h>

#define LOG(fmt, ...) \
    fprintf(stderr, fmt "\n", ## __VA_ARGS__)

#endif // _FAITH_EMULATOR_LOG_H_
