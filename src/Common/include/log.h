/**
 * ****** EoF Emulator - Closed Source ******
 * Copyright (C) 2012 CptSky
 *
 * Taken from :
 * ****** BARLab - Open Source ******
 * Copyright (C) 2012 BARLab
 * Copyright (C) 2012 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _EOFEMU_LOG_H_
#define _EOFEMU_LOG_H_

#include <stdio.h>

#define LOG(fmt, ...) \
    fprintf(stderr, fmt "\n", __VA_ARGS__)

#endif // _EOFEMU_LOG_H_
