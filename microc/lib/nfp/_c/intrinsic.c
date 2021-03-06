/*
 * Copyright (C) 2008-2014 Netronome Systems, Inc.  All rights reserved.
 */

#ifndef __INTRINSIC_C__
#define __INTRINSIC_C__
#if (defined(NFP_STDLIB_ENABLE_CMD_INTRINSICS) || defined(NFP_STDLIB_LEGACY))

#ifndef NFP_LIB_ANY_NFCC_VERSION
    #if (!defined(__NFP_TOOL_NFCC) ||                       \
        (__NFP_TOOL_NFCC < NFP_SW_VERSION(5, 0, 0, 0)) ||   \
        (__NFP_TOOL_NFCC > NFP_SW_VERSION(6, 0, 2, 255)))
        #error "This standard library is not supported for the version of the SDK currently in use."
    #endif
#endif

#include <nfp.h>
#include <nfp_intrinsic.h>

/*
 * NOTE: When writing inline-asm, it's important not to use reserved words
 *       for variables.  Common ones are 'a','b', 'csr', 'state', and
 *       'inp_state'.
 */

/* get current Microengine number and island/cluster id */
__intrinsic
unsigned int __ME(void)
{
    unsigned current_me;
    unsigned current_island;
    _INTRINSIC_BEGIN;
    {
        /* Address encoding for Active Context Status
        *          bit[31]     = Context running flag
        *          bits[30:25] = Island Id
        *          bits[24:8]  = Active Context PC
        *          bit[7]      = Reserved
        *          bits[6:3]   = ME Number
        *          bits[2:0]   = Active Context Number
        */
        current_island = local_csr_read(local_csr_active_ctx_sts);
        current_me = (current_island >> 3) & 0xf;
        current_island = (current_island >> 25) & 0x3f;
        current_me = (current_island << 4) + current_me;
    }
    _INTRINSIC_END;
    return current_me;
}


/* get current island number */
__intrinsic
unsigned int __island(void)
{
    unsigned current_me;
    unsigned current_island;
    _INTRINSIC_BEGIN;
    {
        /* Address encoding for Active Context Status
        *          bit[31]     = Context running flag
        *          bits[30:25] = Island Id
        *          bits[24:8]  = Active Context PC
        *          bit[7]      = Reserved
        *          bits[6:3]   = ME Number
        *          bits[2:0]   = Active Context Number
        */
        current_island = (local_csr_read(local_csr_active_ctx_sts) >> 25) & 0x3f;
    }
    _INTRINSIC_END;
    return current_island;
}


__intrinsic
void assert_range(unsigned int value, unsigned int min_value, unsigned int max_value)
{
    _INTRINSIC_BEGIN;
    {
        if (__is_ct_const(value) && __is_ct_const(min_value) && __is_ct_const(max_value))
        {
            CT_ASSERT(value >= min_value && value <= max_value);
        }
        else
        {
            RT_ASSERT(value >= min_value && value <= max_value);
        }
    }
    _INTRINSIC_END;
}


/* crc_iscsi little-endian */

__intrinsic
unsigned int crc_iscsi_le(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_le[crc_iscsi, result, data], bytes_0_3
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_le[crc_iscsi, result, data], bytes_0_2
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_le[crc_iscsi, result, data], bytes_0_1
        }
        else if (bspec == byte_0)
        {
            __asm crc_le[crc_iscsi, result, data], byte_0
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_le[crc_iscsi, result, data], bytes_1_3
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_le[crc_iscsi, result, data], bytes_2_3
        }
        else // if (bspec == byte_3)
        {
            __asm crc_le[crc_iscsi, result, data], byte_3
        }
    }
    _INTRINSIC_END;
    return result;
}


/* crc_iscsi big-endian */

__intrinsic
unsigned int crc_iscsi_be(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_be[crc_iscsi, result, data], bytes_0_3
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_be[crc_iscsi, result, data], bytes_0_2
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_be[crc_iscsi, result, data], bytes_0_1
        }
        else if (bspec == byte_0)
        {
            __asm crc_be[crc_iscsi, result, data], byte_0
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_be[crc_iscsi, result, data], bytes_1_3
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_be[crc_iscsi, result, data], bytes_2_3
        }
        else // if (bspec == byte_3)
        {
            __asm crc_be[crc_iscsi, result, data], byte_3
        }
    }
    _INTRINSIC_END;
    return result;
}


/* crc_10 little-endian */

__intrinsic
unsigned int crc_10_le(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_le[crc_10, result, data], bytes_0_3
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_le[crc_10, result, data], bytes_0_2
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_le[crc_10, result, data], bytes_0_1
        }
        else if (bspec == byte_0)
        {
            __asm crc_le[crc_10, result, data], byte_0
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_le[crc_10, result, data], bytes_1_3
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_le[crc_10, result, data], bytes_2_3
        }
        else // if (bspec == byte_3)
        {
            __asm crc_le[crc_10, result, data], byte_3
        }
    }
    _INTRINSIC_END;
    return result;
}


/* crc_10 big-endian */

__intrinsic
unsigned int crc_10_be(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_be[crc_10, result, data], bytes_0_3
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_be[crc_10, result, data], bytes_0_2
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_be[crc_10, result, data], bytes_0_1
        }
        else if (bspec == byte_0)
        {
            __asm crc_be[crc_10, result, data], byte_0
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_be[crc_10, result, data], bytes_1_3
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_be[crc_10, result, data], bytes_2_3
        }
        else // if (bspec == byte_3)
        {
            __asm crc_be[crc_10, result, data], byte_3
        }
    }
    _INTRINSIC_END;
    return result;
}


/* crc_5 little-endian */

__intrinsic
unsigned int crc_5_le(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_le[crc_5, result, data], bytes_0_3
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_le[crc_5, result, data], bytes_0_2
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_le[crc_5, result, data], bytes_0_1
        }
        else if (bspec == byte_0)
        {
            __asm crc_le[crc_5, result, data], byte_0
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_le[crc_5, result, data], bytes_1_3
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_le[crc_5, result, data], bytes_2_3
        }
        else // if (bspec == byte_3)
        {
            __asm crc_le[crc_5, result, data], byte_3
        }
    }
    _INTRINSIC_END;
    return result;
}


/* crc_5 big-endian */

__intrinsic
unsigned int crc_5_be(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_be[crc_5, result, data], bytes_0_3
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_be[crc_5, result, data], bytes_0_2
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_be[crc_5, result, data], bytes_0_1
        }
        else if (bspec == byte_0)
        {
            __asm crc_be[crc_5, result, data], byte_0
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_be[crc_5, result, data], bytes_1_3
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_be[crc_5, result, data], bytes_2_3
        }
        else // if (bspec == byte_3)
        {
            __asm crc_be[crc_5, result, data], byte_3
        }
    }
    _INTRINSIC_END;
    return result;
}


/* crc_iscsi little-endian, bit_swap */

__intrinsic
unsigned int crc_iscsi_le_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_le[crc_iscsi, result, data], bytes_0_3, bit_swap
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_le[crc_iscsi, result, data], bytes_0_2, bit_swap
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_le[crc_iscsi, result, data], bytes_0_1, bit_swap
        }
        else if (bspec == byte_0)
        {
            __asm crc_le[crc_iscsi, result, data], byte_0, bit_swap
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_le[crc_iscsi, result, data], bytes_1_3, bit_swap
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_le[crc_iscsi, result, data], bytes_2_3, bit_swap
        }
        else // if (bspec == byte_3)
        {
            __asm crc_le[crc_iscsi, result, data], byte_3, bit_swap
        }
    }
    _INTRINSIC_END;
    return result;
}

/* crc_iscsi big-endian, bit_swap */

__intrinsic
unsigned int crc_iscsi_be_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_be[crc_iscsi, result, data], bytes_0_3, bit_swap
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_be[crc_iscsi, result, data], bytes_0_2, bit_swap
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_be[crc_iscsi, result, data], bytes_0_1, bit_swap
        }
        else if (bspec == byte_0)
        {
            __asm crc_be[crc_iscsi, result, data], byte_0, bit_swap
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_be[crc_iscsi, result, data], bytes_1_3, bit_swap
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_be[crc_iscsi, result, data], bytes_2_3, bit_swap
        }
        else // if (bspec == byte_3)
        {
            __asm crc_be[crc_iscsi, result, data], byte_3, bit_swap
        }
    }
    _INTRINSIC_END;
    return result;
}

/* crc_10 little-endian, bit_swap */

__intrinsic
unsigned int crc_10_le_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_le[crc_10, result, data], bytes_0_3, bit_swap
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_le[crc_10, result, data], bytes_0_2, bit_swap
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_le[crc_10, result, data], bytes_0_1, bit_swap
        }
        else if (bspec == byte_0)
        {
            __asm crc_le[crc_10, result, data], byte_0, bit_swap
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_le[crc_10, result, data], bytes_1_3, bit_swap
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_le[crc_10, result, data], bytes_2_3, bit_swap
        }
        else // if (bspec == byte_3)
        {
            __asm crc_le[crc_10, result, data], byte_3, bit_swap
        }
    }
    _INTRINSIC_END;
    return result;
}

/* crc_10 big-endian, bit_swap */

__intrinsic
unsigned int crc_10_be_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_be[crc_10, result, data], bytes_0_3, bit_swap
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_be[crc_10, result, data], bytes_0_2, bit_swap
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_be[crc_10, result, data], bytes_0_1, bit_swap
        }
        else if (bspec == byte_0)
        {
            __asm crc_be[crc_10, result, data], byte_0, bit_swap
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_be[crc_10, result, data], bytes_1_3, bit_swap
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_be[crc_10, result, data], bytes_2_3, bit_swap
        }
        else // if (bspec == byte_3)
        {
            __asm crc_be[crc_10, result, data], byte_3, bit_swap
        }
    }
    _INTRINSIC_END;
    return result;
}

/* crc_5 little-endian, bit_swap */

__intrinsic
unsigned int crc_5_le_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2  ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_le[crc_5, result, data], bytes_0_3, bit_swap
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_le[crc_5, result, data], bytes_0_2, bit_swap
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_le[crc_5, result, data], bytes_0_1, bit_swap
        }
        else if (bspec == byte_0)
        {
            __asm crc_le[crc_5, result, data], byte_0, bit_swap
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_le[crc_5, result, data], bytes_1_3, bit_swap
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_le[crc_5, result, data], bytes_2_3, bit_swap
        }
        else // if (bspec == byte_3)
        {
            __asm crc_le[crc_5, result, data], byte_3, bit_swap
        }
    }
    _INTRINSIC_END;
    return result;
}

/* crc_5 big-endian, bit_swap */

__intrinsic
unsigned int crc_5_be_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_be[crc_5, result, data], bytes_0_3, bit_swap
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_be[crc_5, result, data], bytes_0_2, bit_swap
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_be[crc_5, result, data], bytes_0_1, bit_swap
        }
        else if (bspec == byte_0)
        {
            __asm crc_be[crc_5, result, data], byte_0, bit_swap
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_be[crc_5, result, data], bytes_1_3, bit_swap
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_be[crc_5, result, data], bytes_2_3, bit_swap
        }
        else // if (bspec == byte_3)
        {
            __asm crc_be[crc_5, result, data], byte_3, bit_swap
        }
    }
    _INTRINSIC_END;
    return result;
}


/* pop_count */

__intrinsic
unsigned int pop_count(
    unsigned int data
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        __asm
        {
            pop_count1[data];
            pop_count2[data];
            pop_count3[result, data];
        }
    }
    _INTRINSIC_END;
    return result;
}


__intrinsic
unsigned int rotr(unsigned int value, int shift)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    if (__is_ct_const(shift))
    {
        CT_ASSERT(shift >= 1 && shift <= 31);
        __asm alu_shf[result, --, B, value, >>rot/**/__ct_const_val(shift)]
    }
    else
    {
        result = (((value)<<(32 - (shift & 0x1f))) | ((value)>>(shift & 0x1f)));
    }
    return result;
    _INTRINSIC_END;
}

__intrinsic
unsigned int rotl(unsigned int value, int shift)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    if (__is_ct_const(shift))
    {
        CT_ASSERT(shift >= 1 && shift <= 31);
        __asm alu_shf[result, --, B, value, <<rot/**/__ct_const_val(shift)]
    }
    else
    {
        result = (((value)<<(shift & 0x1f)) | ((value)>>(32 - (shift & 0x1f))));
    }
    return result;
    _INTRINSIC_END;
}


/* crc_16 little-endian */

unsigned int crc_16_le(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_le[crc_16, result, data], bytes_0_3
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_le[crc_16, result, data], bytes_0_2
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_le[crc_16, result, data], bytes_0_1
        }
        else if (bspec == byte_0)
        {
            __asm crc_le[crc_16, result, data], byte_0
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_le[crc_16, result, data], bytes_1_3
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_le[crc_16, result, data], bytes_2_3
        }
        else // if (bspec == byte_3)
        {
            __asm crc_le[crc_16, result, data], byte_3
        }
    }
    _INTRINSIC_END;
    return result;
}


/* crc_16 big-endian */

unsigned int crc_16_be(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_be[crc_16, result, data], bytes_0_3
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_be[crc_16, result, data], bytes_0_2
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_be[crc_16, result, data], bytes_0_1
        }
        else if (bspec == byte_0)
        {
            __asm crc_be[crc_16, result, data], byte_0
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_be[crc_16, result, data], bytes_1_3
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_be[crc_16, result, data], bytes_2_3
        }
        else // if (bspec == byte_3)
        {
            __asm crc_be[crc_16, result, data], byte_3
        }
    }
    _INTRINSIC_END;
    return result;
}


/* crc_32 little-endian */

__intrinsic
unsigned int crc_32_le(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_le[crc_32, result, data], bytes_0_3
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_le[crc_32, result, data], bytes_0_2
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_le[crc_32, result, data], bytes_0_1
        }
        else if (bspec == byte_0)
        {
            __asm crc_le[crc_32, result, data], byte_0
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_le[crc_32, result, data], bytes_1_3
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_le[crc_32, result, data], bytes_2_3
        }
        else // if (bspec == byte_3)
        {
            __asm crc_le[crc_32, result, data], byte_3
        }
    }
    _INTRINSIC_END;
    return result;
}


/* crc_32 big-endian */

__intrinsic
unsigned int crc_32_be(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_be[crc_32, result, data], bytes_0_3
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_be[crc_32, result, data], bytes_0_2
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_be[crc_32, result, data], bytes_0_1
        }
        else if (bspec == byte_0)
        {
            __asm crc_be[crc_32, result, data], byte_0
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_be[crc_32, result, data], bytes_1_3
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_be[crc_32, result, data], bytes_2_3
        }
        else // if (bspec == byte_3)
        {
            __asm crc_be[crc_32, result, data], byte_3
        }
    }
    _INTRINSIC_END;
    return result;
}


/* crc_ccitt little-endian */

__intrinsic
unsigned int crc_ccitt_le(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_le[crc_ccitt, result, data], bytes_0_3
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_le[crc_ccitt, result, data], bytes_0_2
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_le[crc_ccitt, result, data], bytes_0_1
        }
        else if (bspec == byte_0)
        {
            __asm crc_le[crc_ccitt, result, data], byte_0
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_le[crc_ccitt, result, data], bytes_1_3
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_le[crc_ccitt, result, data], bytes_2_3
        }
        else // if (bspec == byte_3)
        {
            __asm crc_le[crc_ccitt, result, data], byte_3
        }
    }
    _INTRINSIC_END;
    return result;
}


/* crc_ccitt big-endian */

__intrinsic
unsigned int crc_ccitt_be(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_be[crc_ccitt, result, data], bytes_0_3
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_be[crc_ccitt, result, data], bytes_0_2
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_be[crc_ccitt, result, data], bytes_0_1
        }
        else if (bspec == byte_0)
        {
            __asm crc_be[crc_ccitt, result, data], byte_0
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_be[crc_ccitt, result, data], bytes_1_3
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_be[crc_ccitt, result, data], bytes_2_3
        }
        else // if (bspec == byte_3)
        {
            __asm crc_be[crc_ccitt, result, data], byte_3
        }
    }
    _INTRINSIC_END;
    return result;
}


/**
 *
 */

/* crc_none little-endian */

__intrinsic
unsigned int crc_none_le(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_le[none, result, data], bytes_0_3
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_le[none, result, data], bytes_0_2
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_le[none, result, data], bytes_0_1
        }
        else if (bspec == byte_0)
        {
            __asm crc_le[none, result, data], byte_0
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_le[none, result, data], bytes_1_3
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_le[none, result, data], bytes_2_3
        }
        else // if (bspec == byte_3)
        {
            __asm crc_le[none, result, data], byte_3
        }
    }
    _INTRINSIC_END;
    return result;
}

/* crc_none big-endian */

__intrinsic
unsigned int crc_none_be(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_be[none, result, data], bytes_0_3
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_be[none, result, data], bytes_0_2
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_be[none, result, data], bytes_0_1
        }
        else if (bspec == byte_0)
        {
            __asm crc_be[none, result, data], byte_0
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_be[none, result, data], bytes_1_3
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_be[none, result, data], bytes_2_3
        }
        else // if (bspec == byte_3)
        {
            __asm crc_be[none, result, data], byte_3
        }
    }
    _INTRINSIC_END;
    return result;
}

/* crc_16 little-endian, bit_swap */

__intrinsic
unsigned int crc_16_le_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_le[crc_16, result, data], bytes_0_3, bit_swap
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_le[crc_16, result, data], bytes_0_2, bit_swap
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_le[crc_16, result, data], bytes_0_1, bit_swap
        }
        else if (bspec == byte_0)
        {
            __asm crc_le[crc_16, result, data], byte_0, bit_swap
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_le[crc_16, result, data], bytes_1_3, bit_swap
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_le[crc_16, result, data], bytes_2_3, bit_swap
        }
        else // if (bspec == byte_3)
        {
            __asm crc_le[crc_16, result, data], byte_3, bit_swap
        }
    }
    _INTRINSIC_END;
    return result;
}

/* crc_16 big-endian, bit_swap */

__intrinsic
unsigned int crc_16_be_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_be[crc_16, result, data], bytes_0_3, bit_swap
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_be[crc_16, result, data], bytes_0_2, bit_swap
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_be[crc_16, result, data], bytes_0_1, bit_swap
        }
        else if (bspec == byte_0)
        {
            __asm crc_be[crc_16, result, data], byte_0, bit_swap
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_be[crc_16, result, data], bytes_1_3, bit_swap
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_be[crc_16, result, data], bytes_2_3, bit_swap
        }
        else // if (bspec == byte_3)
        {
            __asm crc_be[crc_16, result, data], byte_3, bit_swap
        }
    }
    _INTRINSIC_END;
    return result;
}

/* crc_32 little-endian, bit_swap */

__intrinsic
unsigned int crc_32_le_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_le[crc_32, result, data], bytes_0_3, bit_swap
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_le[crc_32, result, data], bytes_0_2, bit_swap
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_le[crc_32, result, data], bytes_0_1, bit_swap
        }
        else if (bspec == byte_0)
        {
            __asm crc_le[crc_32, result, data], byte_0, bit_swap
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_le[crc_32, result, data], bytes_1_3, bit_swap
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_le[crc_32, result, data], bytes_2_3, bit_swap
        }
        else // if (bspec == byte_3)
        {
            __asm crc_le[crc_32, result, data], byte_3, bit_swap
        }
    }
    _INTRINSIC_END;
    return result;
}

/* crc_32 big-endian, bit_swap */

__intrinsic
unsigned int crc_32_be_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_be[crc_32, result, data], bytes_0_3, bit_swap
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_be[crc_32, result, data], bytes_0_2, bit_swap
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_be[crc_32, result, data], bytes_0_1, bit_swap
        }
        else if (bspec == byte_0)
        {
            __asm crc_be[crc_32, result, data], byte_0, bit_swap
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_be[crc_32, result, data], bytes_1_3, bit_swap
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_be[crc_32, result, data], bytes_2_3, bit_swap
        }
        else // if (bspec == byte_3)
        {
            __asm crc_be[crc_32, result, data], byte_3, bit_swap
        }
    }
    _INTRINSIC_END;
    return result;
}

/* crc_ccitt little-endian, bit_swap */

__intrinsic
unsigned int crc_ccitt_le_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_le[crc_ccitt, result, data], bytes_0_3, bit_swap
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_le[crc_ccitt, result, data], bytes_0_2, bit_swap
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_le[crc_ccitt, result, data], bytes_0_1, bit_swap
        }
        else if (bspec == byte_0)
        {
            __asm crc_le[crc_ccitt, result, data], byte_0, bit_swap
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_le[crc_ccitt, result, data], bytes_1_3, bit_swap
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_le[crc_ccitt, result, data], bytes_2_3, bit_swap
        }
        else // if (bspec == byte_3)
        {
            __asm crc_le[crc_ccitt, result, data], byte_3, bit_swap
        }
    }
    _INTRINSIC_END;
    return result;
}

/* crc_ccitt big-endian, bit_swap */

__intrinsic
unsigned int crc_ccitt_be_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_be[crc_ccitt, result, data], bytes_0_3, bit_swap
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_be[crc_ccitt, result, data], bytes_0_2, bit_swap
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_be[crc_ccitt, result, data], bytes_0_1, bit_swap
        }
        else if (bspec == byte_0)
        {
            __asm crc_be[crc_ccitt, result, data], byte_0, bit_swap
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_be[crc_ccitt, result, data], bytes_1_3, bit_swap
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_be[crc_ccitt, result, data], bytes_2_3, bit_swap
        }
        else // if (bspec == byte_3)
        {
            __asm crc_be[crc_ccitt, result, data], byte_3, bit_swap
        }
    }
    _INTRINSIC_END;
    return result;
}

/* crc_none little-endian, bit_swap */

__intrinsic
unsigned int crc_none_le_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2  ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_le[none, result, data], bytes_0_3, bit_swap
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_le[none, result, data], bytes_0_2, bit_swap
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_le[none, result, data], bytes_0_1, bit_swap
        }
        else if (bspec == byte_0)
        {
            __asm crc_le[none, result, data], byte_0, bit_swap
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_le[none, result, data], bytes_1_3, bit_swap
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_le[none, result, data], bytes_2_3, bit_swap
        }
        else // if (bspec == byte_3)
        {
            __asm crc_le[none, result, data], byte_3, bit_swap
        }
    }
    _INTRINSIC_END;
    return result;
}

/* crc_none big-endian, bit_swap */

__intrinsic
unsigned int crc_none_be_bit_swap(
    unsigned int data,
    bytes_specifier_t bspec             /* byte specifier */
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(bspec == bytes_0_3 || bspec == bytes_0_2 ||
                    bspec == bytes_0_1 || bspec == byte_0 ||
                    bspec == bytes_1_3 || bspec == bytes_2_3 || bspec == byte_3);
        if (bspec == bytes_0_3)
        {
            __asm crc_be[none, result, data], bytes_0_3, bit_swap
        }
        else if (bspec == bytes_0_2)
        {
            __asm crc_be[none, result, data], bytes_0_2, bit_swap
        }
        else if (bspec == bytes_0_1)
        {
            __asm crc_be[none, result, data], bytes_0_1, bit_swap
        }
        else if (bspec == byte_0)
        {
            __asm crc_be[none, result, data], byte_0, bit_swap
        }
        else if (bspec == bytes_1_3)
        {
            __asm crc_be[none, result, data], bytes_1_3, bit_swap
        }
        else if (bspec == bytes_2_3)
        {
            __asm crc_be[none, result, data], bytes_2_3, bit_swap
        }
        else // if (bspec == byte_3)
        {
            __asm crc_be[none, result, data], byte_3, bit_swap
        }
    }
    _INTRINSIC_END;
    return result;
}

/* crc read remainder */

__intrinsic
unsigned int crc_read()
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        result = local_csr_read(local_csr_crc_remainder);
    }
    _INTRINSIC_END;
    return result;
}


/* crc write residue */

__intrinsic
void crc_write(
    unsigned int residue
)
{
    _INTRINSIC_BEGIN;
    local_csr_write(local_csr_crc_remainder, residue);
    _INTRINSIC_END;
}

/*
 *
 * Byte align
 *
 */

/* byte-align block little-endian */

__intrinsic
void byte_align_block_le(
    unsigned int n_byte_align_oper,
    void *dest,
    void *src,
    unsigned shift_cnt
)
{
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(__is_ct_const(n_byte_align_oper));    // needs not to be const but it's big help
        CT_ASSERT(n_byte_align_oper <= 16);
        CT_ASSERT(__is_in_reg(dest));
        CT_ASSERT(__is_in_reg(src));
        //CT_ASSERT(__elem_size(dest)==4);
        //CT_ASSERT(__elem_size(src)==4);

        local_csr_write(local_csr_byte_index, shift_cnt);   // wasted if n_byte_align_oper==0, but ...

        if (n_byte_align_oper == 1)
        {
            __asm
            {
                byte_align_le[--, __ct_4_byte_esize(src[0])];
            }
        }
        else if (n_byte_align_oper == 2)
        {
            __asm
            {
                byte_align_le[--, __ct_4_byte_esize(src[0])];
                byte_align_le[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
            }
        }
        else if (n_byte_align_oper == 3)
        {
            __asm
            {
                byte_align_le[--, __ct_4_byte_esize(src[0])];
                byte_align_le[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_le[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
            }
        }
        else if (n_byte_align_oper == 4)
        {
            __asm
            {
                byte_align_le[--, __ct_4_byte_esize(src[0])];
                byte_align_le[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_le[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_le[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
            }
        }
        else if (n_byte_align_oper == 5)
        {
            __asm
            {
                byte_align_le[--, __ct_4_byte_esize(src[0])];
                byte_align_le[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_le[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_le[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_le[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
            }
        }
        else if (n_byte_align_oper == 6)
        {
            __asm
            {
                byte_align_le[--, __ct_4_byte_esize(src[0])];
                byte_align_le[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_le[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_le[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_le[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_le[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
            }
        }
        else if (n_byte_align_oper == 7)
        {
            __asm
            {
                byte_align_le[--, __ct_4_byte_esize(src[0])];
                byte_align_le[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_le[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_le[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_le[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_le[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_le[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
            }
        }
        else if (n_byte_align_oper == 8)
        {
            __asm
            {
                byte_align_le[--, __ct_4_byte_esize(src[0])];
                byte_align_le[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_le[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_le[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_le[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_le[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_le[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
                byte_align_le[__ct_4_byte_esize(dest[6]), __ct_4_byte_esize(src[7])];
            }
        }
        else if (n_byte_align_oper == 9)
        {
            __asm
            {
                byte_align_le[--, __ct_4_byte_esize(src[0])];
                byte_align_le[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_le[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_le[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_le[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_le[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_le[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
                byte_align_le[__ct_4_byte_esize(dest[6]), __ct_4_byte_esize(src[7])];
                byte_align_le[__ct_4_byte_esize(dest[7]), __ct_4_byte_esize(src[8])];
            }
        }
        else if (n_byte_align_oper == 10)
        {
            __asm
            {
                byte_align_le[--, __ct_4_byte_esize(src[0])];
                byte_align_le[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_le[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_le[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_le[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_le[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_le[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
                byte_align_le[__ct_4_byte_esize(dest[6]), __ct_4_byte_esize(src[7])];
                byte_align_le[__ct_4_byte_esize(dest[7]), __ct_4_byte_esize(src[8])];
                byte_align_le[__ct_4_byte_esize(dest[8]), __ct_4_byte_esize(src[9])];
            }
        }
        else if (n_byte_align_oper == 11)
        {
            __asm
            {
                byte_align_le[--, __ct_4_byte_esize(src[0])];
                byte_align_le[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_le[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_le[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_le[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_le[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_le[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
                byte_align_le[__ct_4_byte_esize(dest[6]), __ct_4_byte_esize(src[7])];
                byte_align_le[__ct_4_byte_esize(dest[7]), __ct_4_byte_esize(src[8])];
                byte_align_le[__ct_4_byte_esize(dest[8]), __ct_4_byte_esize(src[9])];
                byte_align_le[__ct_4_byte_esize(dest[9]), __ct_4_byte_esize(src[10])];
            }
        }
        else if (n_byte_align_oper == 12)
        {
            __asm
            {
                byte_align_le[--, __ct_4_byte_esize(src[0])];
                byte_align_le[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_le[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];

                byte_align_le[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_le[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_le[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_le[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
                byte_align_le[__ct_4_byte_esize(dest[6]), __ct_4_byte_esize(src[7])];
                byte_align_le[__ct_4_byte_esize(dest[7]), __ct_4_byte_esize(src[8])];
                byte_align_le[__ct_4_byte_esize(dest[8]), __ct_4_byte_esize(src[9])];
                byte_align_le[__ct_4_byte_esize(dest[9]), __ct_4_byte_esize(src[10])];
                byte_align_le[__ct_4_byte_esize(dest[10]), __ct_4_byte_esize(src[11])];
            }
        }
        else if (n_byte_align_oper == 13)
        {
            __asm
            {
                byte_align_le[--, __ct_4_byte_esize(src[0])];
                byte_align_le[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_le[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_le[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_le[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_le[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_le[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
                byte_align_le[__ct_4_byte_esize(dest[6]), __ct_4_byte_esize(src[7])];
                byte_align_le[__ct_4_byte_esize(dest[7]), __ct_4_byte_esize(src[8])];
                byte_align_le[__ct_4_byte_esize(dest[8]), __ct_4_byte_esize(src[9])];
                byte_align_le[__ct_4_byte_esize(dest[9]), __ct_4_byte_esize(src[10])];
                byte_align_le[__ct_4_byte_esize(dest[10]), __ct_4_byte_esize(src[11])];
                byte_align_le[__ct_4_byte_esize(dest[11]), __ct_4_byte_esize(src[12])];
            }
        }
        else if (n_byte_align_oper == 14)
        {
            __asm
            {
                byte_align_le[--, __ct_4_byte_esize(src[0])];
                byte_align_le[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_le[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_le[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_le[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_le[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_le[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
                byte_align_le[__ct_4_byte_esize(dest[6]), __ct_4_byte_esize(src[7])];
                byte_align_le[__ct_4_byte_esize(dest[7]), __ct_4_byte_esize(src[8])];
                byte_align_le[__ct_4_byte_esize(dest[8]), __ct_4_byte_esize(src[9])];
                byte_align_le[__ct_4_byte_esize(dest[9]), __ct_4_byte_esize(src[10])];
                byte_align_le[__ct_4_byte_esize(dest[10]), __ct_4_byte_esize(src[11])];
                byte_align_le[__ct_4_byte_esize(dest[11]), __ct_4_byte_esize(src[12])];
                byte_align_le[__ct_4_byte_esize(dest[12]), __ct_4_byte_esize(src[13])];
            }
        }
        else if (n_byte_align_oper == 15)
        {
            __asm
            {
                byte_align_le[--, __ct_4_byte_esize(src[0])];
                byte_align_le[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_le[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_le[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_le[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_le[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_le[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
                byte_align_le[__ct_4_byte_esize(dest[6]), __ct_4_byte_esize(src[7])];
                byte_align_le[__ct_4_byte_esize(dest[7]), __ct_4_byte_esize(src[8])];
                byte_align_le[__ct_4_byte_esize(dest[8]), __ct_4_byte_esize(src[9])];
                byte_align_le[__ct_4_byte_esize(dest[9]), __ct_4_byte_esize(src[10])];
                byte_align_le[__ct_4_byte_esize(dest[10]), __ct_4_byte_esize(src[11])];
                byte_align_le[__ct_4_byte_esize(dest[11]), __ct_4_byte_esize(src[12])];
                byte_align_le[__ct_4_byte_esize(dest[12]), __ct_4_byte_esize(src[13])];
                byte_align_le[__ct_4_byte_esize(dest[13]), __ct_4_byte_esize(src[14])];
            }
        }
        else if (n_byte_align_oper == 16)
        {
            __asm
            {
                byte_align_le[--, __ct_4_byte_esize(src[0])];
                byte_align_le[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_le[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_le[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_le[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_le[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_le[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
                byte_align_le[__ct_4_byte_esize(dest[6]), __ct_4_byte_esize(src[7])];
                byte_align_le[__ct_4_byte_esize(dest[7]), __ct_4_byte_esize(src[8])];
                byte_align_le[__ct_4_byte_esize(dest[8]), __ct_4_byte_esize(src[9])];
                byte_align_le[__ct_4_byte_esize(dest[9]), __ct_4_byte_esize(src[10])];
                byte_align_le[__ct_4_byte_esize(dest[10]), __ct_4_byte_esize(src[11])];
                byte_align_le[__ct_4_byte_esize(dest[11]), __ct_4_byte_esize(src[12])];
                byte_align_le[__ct_4_byte_esize(dest[12]), __ct_4_byte_esize(src[13])];
                byte_align_le[__ct_4_byte_esize(dest[13]), __ct_4_byte_esize(src[14])];
                byte_align_le[__ct_4_byte_esize(dest[14]), __ct_4_byte_esize(src[15])];
            }
        }
    }
    _INTRINSIC_END;
}

/* byte-align block big-endian */

__intrinsic
void byte_align_block_be(
    unsigned int n_byte_align_oper,
    void *dest,
    void *src,
    unsigned shift_cnt
)
{
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(__is_ct_const(n_byte_align_oper));    // needs not to be const but it's big help
        CT_ASSERT(n_byte_align_oper <= 16);
        CT_ASSERT(__is_in_reg(dest));
        CT_ASSERT(__is_in_reg(src));
        //CT_ASSERT(__elem_size(dest)==4);
        //CT_ASSERT(__elem_size(src)==4);

        local_csr_write(local_csr_byte_index, shift_cnt);   // wasted if n_byte_align_oper==0, but ...

        if (n_byte_align_oper == 1)
        {
            __asm
            {
                byte_align_be[--, __ct_4_byte_esize(src[0])];
            }
        }
        else if (n_byte_align_oper == 2)
        {
            __asm
            {
                byte_align_be[--, __ct_4_byte_esize(src[0])];
                byte_align_be[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
            }
        }
        else if (n_byte_align_oper == 3)
        {
            __asm
            {
                byte_align_be[--, __ct_4_byte_esize(src[0])];
                byte_align_be[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_be[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
            }
        }
        else if (n_byte_align_oper == 4)
        {
            __asm
            {
                byte_align_be[--, __ct_4_byte_esize(src[0])];
                byte_align_be[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_be[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_be[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
            }
        }
        else if (n_byte_align_oper == 5)
        {
            __asm
            {
                byte_align_be[--, __ct_4_byte_esize(src[0])];
                byte_align_be[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_be[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_be[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_be[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
            }
        }
        else if (n_byte_align_oper == 6)
        {
            __asm
            {
                byte_align_be[--, __ct_4_byte_esize(src[0])];
                byte_align_be[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_be[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_be[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_be[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_be[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
            }
        }
        else if (n_byte_align_oper == 7)
        {
            __asm
            {
                byte_align_be[--, __ct_4_byte_esize(src[0])];
                byte_align_be[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_be[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_be[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_be[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_be[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_be[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
            }
        }
        else if (n_byte_align_oper == 8)
        {
            __asm
            {
                byte_align_be[--, __ct_4_byte_esize(src[0])];
                byte_align_be[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_be[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_be[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_be[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_be[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_be[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
                byte_align_be[__ct_4_byte_esize(dest[6]), __ct_4_byte_esize(src[7])];
            }
        }
        else if (n_byte_align_oper == 9)
        {
            __asm
            {
                byte_align_be[--, __ct_4_byte_esize(src[0])];
                byte_align_be[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_be[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_be[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_be[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_be[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_be[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
                byte_align_be[__ct_4_byte_esize(dest[6]), __ct_4_byte_esize(src[7])];
                byte_align_be[__ct_4_byte_esize(dest[7]), __ct_4_byte_esize(src[8])];
            }
        }
        else if (n_byte_align_oper == 10)
        {
            __asm
            {
                byte_align_be[--, __ct_4_byte_esize(src[0])];
                byte_align_be[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_be[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_be[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_be[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_be[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_be[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
                byte_align_be[__ct_4_byte_esize(dest[6]), __ct_4_byte_esize(src[7])];
                byte_align_be[__ct_4_byte_esize(dest[7]), __ct_4_byte_esize(src[8])];
                byte_align_be[__ct_4_byte_esize(dest[8]), __ct_4_byte_esize(src[9])];
            }
        }
        else if (n_byte_align_oper == 11)
        {
            __asm
            {
                byte_align_be[--, __ct_4_byte_esize(src[0])];
                byte_align_be[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_be[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_be[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_be[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_be[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_be[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
                byte_align_be[__ct_4_byte_esize(dest[6]), __ct_4_byte_esize(src[7])];
                byte_align_be[__ct_4_byte_esize(dest[7]), __ct_4_byte_esize(src[8])];
                byte_align_be[__ct_4_byte_esize(dest[8]), __ct_4_byte_esize(src[9])];
                byte_align_be[__ct_4_byte_esize(dest[9]), __ct_4_byte_esize(src[10])];
            }
        }
        else if (n_byte_align_oper == 12)
        {
            __asm
            {
                byte_align_be[--, __ct_4_byte_esize(src[0])];
                byte_align_be[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_be[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_be[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_be[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_be[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_be[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
                byte_align_be[__ct_4_byte_esize(dest[6]), __ct_4_byte_esize(src[7])];
                byte_align_be[__ct_4_byte_esize(dest[7]), __ct_4_byte_esize(src[8])];
                byte_align_be[__ct_4_byte_esize(dest[8]), __ct_4_byte_esize(src[9])];
                byte_align_be[__ct_4_byte_esize(dest[9]), __ct_4_byte_esize(src[10])];
                byte_align_be[__ct_4_byte_esize(dest[10]), __ct_4_byte_esize(src[11])];
            }
        }
        else if (n_byte_align_oper == 13)
        {
            __asm
            {
                byte_align_be[--, __ct_4_byte_esize(src[0])];
                byte_align_be[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_be[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_be[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_be[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_be[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_be[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
                byte_align_be[__ct_4_byte_esize(dest[6]), __ct_4_byte_esize(src[7])];
                byte_align_be[__ct_4_byte_esize(dest[7]), __ct_4_byte_esize(src[8])];
                byte_align_be[__ct_4_byte_esize(dest[8]), __ct_4_byte_esize(src[9])];
                byte_align_be[__ct_4_byte_esize(dest[9]), __ct_4_byte_esize(src[10])];
                byte_align_be[__ct_4_byte_esize(dest[10]), __ct_4_byte_esize(src[11])];
                byte_align_be[__ct_4_byte_esize(dest[11]), __ct_4_byte_esize(src[12])];
            }
        }
        else if (n_byte_align_oper == 14)
        {
            __asm
            {
                byte_align_be[--, __ct_4_byte_esize(src[0])];
                byte_align_be[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_be[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_be[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_be[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_be[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_be[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
                byte_align_be[__ct_4_byte_esize(dest[6]), __ct_4_byte_esize(src[7])];
                byte_align_be[__ct_4_byte_esize(dest[7]), __ct_4_byte_esize(src[8])];
                byte_align_be[__ct_4_byte_esize(dest[8]), __ct_4_byte_esize(src[9])];
                byte_align_be[__ct_4_byte_esize(dest[9]), __ct_4_byte_esize(src[10])];
                byte_align_be[__ct_4_byte_esize(dest[10]), __ct_4_byte_esize(src[11])];
                byte_align_be[__ct_4_byte_esize(dest[11]), __ct_4_byte_esize(src[12])];
                byte_align_be[__ct_4_byte_esize(dest[12]), __ct_4_byte_esize(src[13])];
            }
        }
        else if (n_byte_align_oper == 15)
        {
            __asm
            {
                byte_align_be[--, __ct_4_byte_esize(src[0])];
                byte_align_be[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_be[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_be[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_be[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_be[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_be[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
                byte_align_be[__ct_4_byte_esize(dest[6]), __ct_4_byte_esize(src[7])];
                byte_align_be[__ct_4_byte_esize(dest[7]), __ct_4_byte_esize(src[8])];
                byte_align_be[__ct_4_byte_esize(dest[8]), __ct_4_byte_esize(src[9])];
                byte_align_be[__ct_4_byte_esize(dest[9]), __ct_4_byte_esize(src[10])];
                byte_align_be[__ct_4_byte_esize(dest[10]), __ct_4_byte_esize(src[11])];
                byte_align_be[__ct_4_byte_esize(dest[11]), __ct_4_byte_esize(src[12])];
                byte_align_be[__ct_4_byte_esize(dest[12]), __ct_4_byte_esize(src[13])];
                byte_align_be[__ct_4_byte_esize(dest[13]), __ct_4_byte_esize(src[14])];
            }
        }
        else if (n_byte_align_oper == 16)
        {
            __asm
            {
                byte_align_be[--, __ct_4_byte_esize(src[0])];
                byte_align_be[__ct_4_byte_esize(dest[0]), __ct_4_byte_esize(src[1])];
                byte_align_be[__ct_4_byte_esize(dest[1]), __ct_4_byte_esize(src[2])];
                byte_align_be[__ct_4_byte_esize(dest[2]), __ct_4_byte_esize(src[3])];
                byte_align_be[__ct_4_byte_esize(dest[3]), __ct_4_byte_esize(src[4])];
                byte_align_be[__ct_4_byte_esize(dest[4]), __ct_4_byte_esize(src[5])];
                byte_align_be[__ct_4_byte_esize(dest[5]), __ct_4_byte_esize(src[6])];
                byte_align_be[__ct_4_byte_esize(dest[6]), __ct_4_byte_esize(src[7])];
                byte_align_be[__ct_4_byte_esize(dest[7]), __ct_4_byte_esize(src[8])];
                byte_align_be[__ct_4_byte_esize(dest[8]), __ct_4_byte_esize(src[9])];
                byte_align_be[__ct_4_byte_esize(dest[9]), __ct_4_byte_esize(src[10])];
                byte_align_be[__ct_4_byte_esize(dest[10]), __ct_4_byte_esize(src[11])];
                byte_align_be[__ct_4_byte_esize(dest[11]), __ct_4_byte_esize(src[12])];
                byte_align_be[__ct_4_byte_esize(dest[12]), __ct_4_byte_esize(src[13])];
                byte_align_be[__ct_4_byte_esize(dest[13]), __ct_4_byte_esize(src[14])];
                byte_align_be[__ct_4_byte_esize(dest[14]), __ct_4_byte_esize(src[15])];
            }
        }
    }
    _INTRINSIC_END;
}


/* find first bit set */

__intrinsic
unsigned int ffs(
    unsigned int data
)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        __asm ffs[result, data];
    }
    _INTRINSIC_END;
    return result;
}

/* ToDo: load field */

/* ToDo: load field with clear */


/*
 *
 * CAM write
 *
 */
/* CAM write */

__intrinsic
void cam_write(
    unsigned int entry_num,
    unsigned int tag,
    unsigned int cam_state
)
{
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(__is_ct_const(cam_state));
        if (__is_ct_const(entry_num))
        {
            CT_ASSERT(entry_num <= 15);
        }
        __asm nop;      // Just in case previous instruction is conditional p3-branch
        // Will be removed by scheduler if not
        __asm cam_write[entry_num, tag, __ct_const_val(cam_state)];
    }
    _INTRINSIC_END;
}


/* CAM lookup */

__intrinsic
cam_lookup_t cam_lookup(
    unsigned int tag
)
{
    cam_lookup_t result;
    _INTRINSIC_BEGIN;
    {
        __asm nop;      // Just in case previous instruction is conditional p3-branch
        // Will be removed by scheduler if not
        __asm cam_lookup[result, tag]   //ToDo: should we warn when tag==0?
    }
    _INTRINSIC_END;
    return result;
}

/* CAM write state */

__intrinsic
void cam_write_state(
    unsigned int entry_num,
    unsigned int cam_state
)
{
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(__is_ct_const(cam_state));
        if (__is_ct_const(entry_num))
        {
            CT_ASSERT(entry_num <= 15);
        }
        __asm nop;      // Just in case previous instruction is conditional p3-branch
        // Will be removed by scheduler if not
        __asm cam_write_state[entry_num, __ct_const_val(cam_state)]
    }
    _INTRINSIC_END;
}

/* CAM read tag */

__intrinsic
unsigned int cam_read_tag(
    unsigned int entry_num
)
{
    unsigned int result;
    _INTRINSIC_BEGIN;
    {
        if (__is_ct_const(entry_num))
        {
            CT_ASSERT(entry_num <= 15);
        }
        __asm cam_read_tag[result, entry_num]
    }
    _INTRINSIC_END;
    return result;
}

/* CAM read state */

__intrinsic
cam_lookup_t cam_read_state(
    unsigned int entry_num
)
{
    cam_lookup_t result;
    _INTRINSIC_BEGIN;
    {
        if (__is_ct_const(entry_num))
        {
            CT_ASSERT(entry_num <= 15);
        }
        __asm cam_read_state[result, entry_num]
    }
    _INTRINSIC_END;
    return result;
}


/* CAM clear */

__intrinsic
void cam_clear()
{
    _INTRINSIC_BEGIN;
    {
        __asm nop;      // Just in case previous instruction is conditional p3-branch
        // Will be removed by scheduler if not
        __asm cam_clear;
    }
    _INTRINSIC_END;
}



/* multiply */
__intrinsic
unsigned int multiply_24x8(
    unsigned int x,
    unsigned int y
)
{
    unsigned int result;
    _INTRINSIC_BEGIN;
    {
        __asm
        {
            mul_step[x, y], 24x8_start
            mul_step[x, y], 24x8_step1
            mul_step[result, --], 24x8_last
        }
    }
    _INTRINSIC_END;
    return result;
}

__intrinsic
unsigned int multiply_16x16(
    unsigned int x,
    unsigned int y
)
{
    unsigned int result;
    _INTRINSIC_BEGIN;
    {
        __asm
        {
            mul_step[x, y], 16x16_start
            mul_step[x, y], 16x16_step1
            mul_step[x, y], 16x16_step2
            mul_step[result, --], 16x16_last
        }
    }
    _INTRINSIC_END;
    return result;
}

__intrinsic
unsigned int multiply_32x32_lo(
    unsigned int x,
    unsigned int y
)
{
    unsigned int result;
    _INTRINSIC_BEGIN;
    {
        __asm
        {
            mul_step[x, y], 32x32_start
            mul_step[x, y], 32x32_step1
            mul_step[x, y], 32x32_step2
            mul_step[x, y], 32x32_step3
            mul_step[x, y], 32x32_step4
            mul_step[result, --], 32x32_last
        }
    }
    _INTRINSIC_END;
    return result;
}

__intrinsic
unsigned int multiply_32x32_hi(
    unsigned int x,
    unsigned int y
)
{
    unsigned int result;
    _INTRINSIC_BEGIN;
    {
        __asm
        {
            mul_step[x, y], 32x32_start
            mul_step[x, y], 32x32_step1
            mul_step[x, y], 32x32_step2
            mul_step[x, y], 32x32_step3
            mul_step[x, y], 32x32_step4
            mul_step[result, --], 32x32_last
            mul_step[result, --], 32x32_last2
        }
    }
    _INTRINSIC_END;
    return result;
}

__intrinsic
unsigned long long multiply_32x32(
    unsigned int x,
    unsigned int y
)
{
    unsigned int lo, hi;
    _INTRINSIC_BEGIN;
    {
        __asm
        {
            mul_step[x, y], 32x32_start
            mul_step[x, y], 32x32_step1
            mul_step[x, y], 32x32_step2
            mul_step[x, y], 32x32_step3
            mul_step[x, y], 32x32_step4
            mul_step[lo, --], 32x32_last
            mul_step[hi, --], 32x32_last2
        }
    }
    _INTRINSIC_END;
    return ((unsigned long long)hi << 32) | lo;
}



__intrinsic
void __set_timestamp(
    __int64 timestamp
)
{
    _INTRINSIC_BEGIN;
    {
        local_csr_write(local_csr_timestamp_low, 0);
        local_csr_write(local_csr_timestamp_high, (unsigned)(timestamp >> 32));
        local_csr_write(local_csr_timestamp_low, (unsigned)timestamp);
    }
    _INTRINSIC_END;
}

__intrinsic
__int64 __timestamp_start()
{
    unsigned lo, hi;
    _INTRINSIC_BEGIN;
    {
        lo = local_csr_read(local_csr_timestamp_low);
        hi = local_csr_read(local_csr_timestamp_high);
    }
    _INTRINSIC_END;
    return ((__int64)hi << 32) | lo;
}

__intrinsic
__int64 __timestamp_stop(
    __int64 handle
)
{
    __int64 curr;
    _INTRINSIC_BEGIN;
    {
        curr = __timestamp_start();
    }
    _INTRINSIC_END;
    return curr - handle;
}

__intrinsic
void __set_profile_count(
    unsigned int profile_count
)
{
    _INTRINSIC_BEGIN;
    {

        local_csr_write(local_csr_profile_count, profile_count);
    }
    _INTRINSIC_END;
}

__intrinsic
unsigned int __profile_count_start()
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        result = local_csr_read(local_csr_profile_count);
    }
    _INTRINSIC_END;
    return result;
}

__intrinsic
unsigned int __profile_count_stop(
    unsigned int handle
)
{
    unsigned curr;
    _INTRINSIC_BEGIN;
    {
        curr = __profile_count_start();
    }
    _INTRINSIC_END;
    return curr - handle;
}

/* sleep */

__intrinsic
void __sleep(
    unsigned int cycles                 /* approx. cycles to sleep, resolution is 16-cycle */
)
{

    _INTRINSIC_BEGIN;
    {
        SIGNAL sig;
        unsigned sig_num;
        unsigned tlo;

        __implicit_write(&sig);
        sig_num = __signal_number(&sig);
        tlo = local_csr_read(local_csr_timestamp_low);
        tlo += cycles >> 4;
        local_csr_write(local_csr_active_ctx_future_count, tlo);
        local_csr_write(local_csr_active_future_count_signal, sig_num);
        __asm ctx_arb[sig];
    }
    _INTRINSIC_END;
}



__intrinsic
int bit_test(
    unsigned int data,                  /* data to bit test */
    unsigned int bit_pos                /* bit position to test */
)
{
    int result = 1;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(__is_ct_const(bit_pos));
        __asm
        {
            br_bset[data, __ct_const_val(bit_pos), L1];
            alu[result, --, B, 0]
            L1:
        }
    }
    _INTRINSIC_END;
    return result;
}

__intrinsic
int inp_state_test(
    inp_state_t state_name              /* state to test */
)
{
    int result = 1;
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(__is_ct_const(state_name));
        __asm
        {
            br_inp_state[__ct_const_val(state_name), L1];
            alu[result, --, B, 0]
            L1:
        }
    }
    _INTRINSIC_END;
    return result;
}

__intrinsic
unsigned int nn_ring_dequeue_incr(void)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        __asm alu[result, --, B, *n$index++]
    }
    _INTRINSIC_END;
    return result;
}

__intrinsic
unsigned int nn_ring_dequeue(void)
{
    unsigned result;
    _INTRINSIC_BEGIN;
    {
        __asm alu[result, --, B, *n$index]
    }
    _INTRINSIC_END;
    return result;
}

__intrinsic
void nn_ring_enqueue_incr(
    unsigned int val
)
{
    _INTRINSIC_BEGIN;
    {
        __asm alu[*n$index++, --, B, val]
    }
    _INTRINSIC_END;
}


/* bswap (swap byte in a longword) */
__intrinsic
unsigned int bswap(
    unsigned int v
)
{
    unsigned int result;
    _INTRINSIC_BEGIN;
    {
        __asm
        {
            alu_shf[v, --, B, v, >>rot16]
            ld_field_w_clr[result, 1010b, v, <<8]
            ld_field[result, 0101b, v, >>8]
        }
    }
    _INTRINSIC_END;
    return result;
}


/* bitswap (swap bit in each byte) */
__intrinsic
unsigned int bitswap(
    unsigned int v
)
{
    unsigned int m1 = 0x0f0f0f0f;
    unsigned int v2 = ((v & m1) << 4) | ((v >> 4)&m1);
    unsigned int m2 = 0x33333333;
    unsigned int v3 = ((v2 & m2) << 2) | ((v2 >> 2)&m2);
    unsigned int m3 = 0x55555555;
    unsigned int v4 = ((v3 & m3) << 1) | ((v3 >> 1)&m3);
    return v4;
}

/* wait for signal */
__intrinsic
void ctx_wait(signal_t sig)
{
    _INTRINSIC_BEGIN;
    {
        CT_ASSERT(sig == kill || sig == voluntary || sig == bpt/* || sig == no_load*/);
        if (sig == kill)
        {
            __asm ctx_arb[kill]
        }
        else if (sig == voluntary)
        {
            __asm ctx_arb[voluntary]
        }
        else
        {
            __asm ctx_arb[bpt]
        }
    }
    _INTRINSIC_END;

}


__intrinsic
void signal_same_ME(
    unsigned int sig_no,
    unsigned int ctx
)
{
    _INTRINSIC_BEGIN;
    {
        local_csr_write(local_csr_same_me_signal, ((sig_no & 0xf) << 3) | (ctx & 0x7));
    }
    _INTRINSIC_END;
}

__intrinsic
void signal_same_ME_next_ctx(
    unsigned int sig_no
)
{
    _INTRINSIC_BEGIN;
    {
        local_csr_write(local_csr_same_me_signal, (1 << 7) | ((sig_no & 0xf) << 3));
    }
    _INTRINSIC_END;
}

__intrinsic
void signal_prev_ME(
    unsigned int sig_no,
    unsigned int ctx
)
{
    _INTRINSIC_BEGIN;
    {
        local_csr_write(local_csr_prev_neighbor_signal, ((sig_no & 0xf) << 3) | (ctx & 0x7));
    }
    _INTRINSIC_END;
}

__intrinsic
void signal_prev_ME_this_ctx(
    unsigned int sig_no
)
{
    _INTRINSIC_BEGIN;
    {
        local_csr_write(local_csr_prev_neighbor_signal, (1 << 7) | ((sig_no & 0xf) << 3));
    }
    _INTRINSIC_END;
}

__intrinsic
void signal_next_ME(
    unsigned int sig_no,
    unsigned int ctx
)
{
    _INTRINSIC_BEGIN;
    {
        local_csr_write(local_csr_next_neighbor_signal, ((sig_no & 0xf) << 3) | (ctx & 0x7));
    }
    _INTRINSIC_END;
}

__intrinsic
void signal_next_ME_this_ctx(
    unsigned int sig_no
)
{
    _INTRINSIC_BEGIN;
    {
        local_csr_write(local_csr_next_neighbor_signal, (1 << 7) | ((sig_no & 0xf) << 3));
    }
    _INTRINSIC_END;
}


/* halt() */
__intrinsic
void halt()
{
    _INTRINSIC_BEGIN;
    {
        __asm
        {
            halt
        }
    }
    _INTRINSIC_END;
}

#include "nfp_override.c"
#include "nfp_arm.c"
#include "nfp_cls.c"
#include "nfp_cluster_target.c"
#include "nfp_crypto.c"
#include "nfp_mem.c"
#include "nfp_pcie.c"
#include "nfp_ila.c"
#include "nfp_nbi.c"
#include "nfp_math.c"

#endif /* NFP_STDLIB_ENABLE_CMD_INTRINSICS || NFP_STDLIB_LEGACY */
#endif /* __INTRINSIC_C__ */

