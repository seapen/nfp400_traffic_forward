/*
 * Copyright (C) 2014 Netronome Systems, Inc.  All rights reserved.
 */


#ifndef __NFP_MATH_H__
#define __NFP_MATH_H__

#ifndef NFP_LIB_ANY_NFCC_VERSION
    #if (!defined(__NFP_TOOL_NFCC) ||                       \
        (__NFP_TOOL_NFCC < NFP_SW_VERSION(5, 0, 0, 0)) ||   \
        (__NFP_TOOL_NFCC > NFP_SW_VERSION(6, 0, 2, 255)))
        #error "This standard library is not supported for the version of the SDK currently in use."
    #endif
#endif

#include <stdint.h>

/** @file nfp_math.h
 * @addtogroup Math MATH Intrinsics
 * @{
 */


/** @name General functions for Math
 *  @{
 */
/** Calculate the log2 of a 32-bit value.
 *
 * @param value     The unsigned 32-bit word to do the log2 on.
 *
 * @return         The result of the log2 value.
 */
__intrinsic
unsigned int log2(uint32_t value);


/**
 *  @}
 * @}
 */


#endif

