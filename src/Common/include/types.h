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

#ifndef _FAITH_EMULATOR_TYPES_H_
#define _FAITH_EMULATOR_TYPES_H_

#include <stddef.h> // Define NULL, size_t
#include <limits.h> // Define UCHAR_MAX, etc

#ifdef HAVE_STDINT_H
#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS
#include <stdint.h> // Will define intN_t
#endif

/*
 *****************************************************
 * nullptr definition
 ****************************************************
 */

#if !defined(nullptr) // C++11 defines nullptr
#define nullptr NULL
#endif // !defined(nullptr)

/*
 *****************************************************
 * Fixed-width integer definitions
 ****************************************************
 */

#if !defined(HAVE_STDINT_H)

#if _MSC_VER >= 1400 // MSVS 2005 and higher have fixed-width integers

typedef __int8            int8_t;
typedef unsigned __int8   uint8_t;
typedef __int16           int16_t;
typedef unsigned __int16  uint16_t;
typedef __int32           int32_t;
typedef unsigned __int32  uint32_t;
typedef __int64           int64_t;
typedef unsigned __int64  uint64_t;

#else

// char          is 8-bit
// short int     is at least 16-bit
// int           is at least 16-bit
// long int      is at least 32-bit
// long long int is at least 64-bit (C++11)

#if UCHAR_MAX == 0xFF
typedef signed char             int8_t;
typedef unsigned char           uint8_t;
#else
#error "8-bit integers not found!"
#endif // UCHAR_MAX == 0xFF

#if USHRT_MAX == 0xFFFF // At least 16-bit
typedef signed short int        int16_t;
typedef unsigned short int      uint16_t;
#elif UINT_MAX == 0xFFFFU // At least 16-bit
typedef signed int              int16_t;
typedef unsigned int            uint16_t;
#else
#error "16-bit integers not found!"
#endif // USHRT_MAX == 0xFFFF

#if UINT_MAX == 0xFFFFFFFFU // At least 16-bit
typedef signed int              int32_t;
typedef unsigned int            uint32_t;
#elif ULONG_MAX == 0xFFFFFFFFUL // At least 32-bit
typedef signed long int         int32_t;
typedef unsigned long int       uint32_t;
#else
#error "32-bit integers not found!"
#endif // UINT_MAX == 0xFFFFFFFFU

#if ULONG_MAX == 0xFFFFFFFFFFFFFFFFUL // At least 32-bit
typedef signed long int         int64_t;
typedef unsigned long int       uint64_t;
#elif ULLONG_MAX == 0xFFFFFFFFFFFFFFFFULL // At least 64-bit
typedef signed long long int    int64_t;
typedef unsigned long long int  uint64_t;
#else
#error "64-bit integers not found!"
#endif // ULONG_MAX == 0xFFFFFFFFFFFFFFFFUL

#endif // _MSC_VER >= 1400

#endif // !BL_HAS_STDINT_H

#endif // _FAITH_EMULATOR_TYPES_H
