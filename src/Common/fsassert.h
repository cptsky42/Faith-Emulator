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

#ifndef _FAITH_EMULATOR_ASSERT_H_
#define _FAITH_EMULATOR_ASSERT_H_

// FIXME HACK! Remove on real release...
#define DEBUG

#include <assert.h>

/*
 *****************************************************
 * Assertion macros
 *****************************************************
 */

#ifdef DEBUG

// Assert an expression and might abort
#define ASSERT(exp)                          \
    assert(exp)

// Assert an expression and might abort
#define ASSERT_ERR(exp, err)                 \
    assert(exp)

#else

// Assert an expression and return if false
#define ASSERT(exp)                          \
    if (!(exp))                              \
    return

// Assert an expression and return the error if false
#define ASSERT_ERR(exp, err)                 \
    if (!(exp))                              \
    return err

#endif // DEBUG

#endif // _FAITH_EMULATOR_ASSERT_H_
