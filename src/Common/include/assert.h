/**
 * ****** Faith Emulator - Closed Source ******
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

#ifndef _FAITH_EMULATOR_ASSERT_H_
#define _FAITH_EMULATOR_ASSERT_H_

// FIXME HACK! Remove on real release...
#define DEBUG

#if !defined(DEBUG) && !defined(NDEBUG)
#define NDEBUG
#endif

#include <assert.h>

// FIXME HACK! For some reason... assert() not defined...
#define assert(exp)

#ifndef ASSERT
#define ASSERT(exp) assert(exp)
#endif // ASSERT

#endif // _FAITH_EMULATOR_ASSERT_H_
