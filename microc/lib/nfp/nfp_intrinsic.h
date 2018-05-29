/*
 * Copyright (C) 2008-2014 Netronome Systems, Inc.  All rights reserved.
 */

/* NFP definitions for use by intrinsic functions */

#ifndef __NFP_INTRINSIC_H__
#define __NFP_INTRINSIC_H__

#ifndef NFP_LIB_ANY_NFCC_VERSION
    #if (!defined(__NFP_TOOL_NFCC) ||                       \
        (__NFP_TOOL_NFCC < NFP_SW_VERSION(5, 0, 0, 0)) ||   \
        (__NFP_TOOL_NFCC > NFP_SW_VERSION(6, 0, 2, 255)))
        #error "This standard library is not supported for the version of the SDK currently in use."
    #endif
#endif

#define _INTRINSIC_BEGIN
#define _INTRINSIC_END
#define CT_QPERFINFO_INDIRECT_REF(fn)  \
        __ct_Qperfinfo(128, #fn "(): Size of data access cannot be determined at compile-time. __implicit_read/write may be needed to protect xfer buffer. Use of " #fn "_ind() is recommended instead.")

#define CT_ASSERT(expr) __ct_assert(expr, #expr)

#define _INTRINSIC_UNSUPPORTED_NFP3200_INDIRECT_REF() { const int Unsupported_NFP3200_Indirect_Reference = 0; CT_ASSERT(Unsupported_NFP3200_Indirect_Reference); }

#define _INTRINSIC_NEED_40_BIT_THIRD_PARTY() { const int Need_40_bit_Third_Party_Addressing_Mode_Enabled = 0;  CT_ASSERT(Need_40_bit_Third_Party_Addressing_Mode_Enabled); }


/*
 * Indirect reference macros for indirect words
 */

#define INTRINSIC_IND_ALU_COUNT_MAX 32

/*
 * Indirect reference macros for indirect words
 */

#ifdef __NFP_INDIRECT_REF_FORMAT_NFP3200

/*
 * These macros can be used by NFP-6xxx or NFP-32xx where the macro will set
 * all applicable fields for the override.
 */

/* Encoding 0x02 */
/*
 * Override length
 */
#define _INTRINSIC_OVERRIDE_LENGTH(ov_ind, length)                              \
{                                                                               \
    ov_ind.value = 0;                                                           \
    ov_ind.cnt_ind.encoding = 0x2;                                              \
    ov_ind.cnt_ind.ref_count = length;                                          \
}

/* Encoding 0x03 */
/*
 * Override length and bytemask
 */
#define _INTRINSIC_OVERRIDE_LENGTH_AND_BYTEMASK_IN_ALU(ov_ind, length, bytemask)\
{                                                                               \
    ov_ind.value = 0;                                                           \
    ov_ind.cnt_mask_ind.encoding = 3;                                           \
    ov_ind.cnt_mask_ind.ref_count = length;                                     \
    ov_ind.cnt_mask_ind.byte_mask = bytemask;                                   \
}

/* Encoding 0x04 */
/*
 * Override bytemask
 */
#define _INTRINSIC_OVERRIDE_BYTEMASK(ov_ind, bytemask)                          \
{                                                                               \
    ov_ind.value = 0;                                                           \
    ov_ind.mask_ind.encoding = 4;                                               \
    ov_ind.mask_ind.byte_mask = bytemask;                                       \
}


/* Count override */
#define _INTRINSIC_IND_ALU_COUNT_MIN_MAX(count, min_value, max_value)       \
    override_cnt_ind_t ind;                                                 \
    if (__is_ct_const(count))                                               \
    {                                                                       \
        CT_ASSERT((count) >= (min_value) && (count) <= (max_value));        \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        RT_RANGE_ASSERT((count) >= (min_value) && (count) <= (max_value));  \
    }                                                                       \
    ind.value = 0;                                                          \
    ind.encoding = 2;                                                       \
    ind.ref_count = (count) - 1;                                            \
    __asm { alu[--, --, B, ind] }


/* Count and Byte mask override */

#define _INTRINSIC_IND_ALU_COUNT_MIN_MAX_MASK_MAX(count, min_value, max_value,mask, max_mask) \
    override_cnt_mask_ind_t ind;                                            \
    if (__is_ct_const(count))                                               \
    {                                                                       \
        CT_ASSERT((count) >= (min_value) && (count) <= (max_value));        \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        RT_RANGE_ASSERT((count) >= (min_value) && (count) <= (max_value));  \
    }                                                                       \
    if (__is_ct_const(mask))                                                \
    {                                                                       \
        CT_ASSERT((mask) >= 0 && (mask) <= (max_mask));                     \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        RT_RANGE_ASSERT((mask) >= 0 && (mask) <= (max_mask));               \
    }                                                                       \
    ind.value = 0;                                                          \
    ind.encoding = 3;                                                       \
    ind.ref_count = (count) - 1;                                            \
    ind.byte_mask = (mask);                                                 \
    __asm { alu[--, --, B, ind] }


/* Byte mask override */
#define _INTRINSIC_IND_ALU_MASK_MAX(mask,max_mask)                          \
    override_mask_ind_t ind;                                                \
    if (__is_ct_const(mask))                                                \
    {                                                                       \
        CT_ASSERT((mask) >= 0x1 &&  (mask) <= (max_mask));                  \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        RT_RANGE_ASSERT((mask) >= 0x1 &&  (mask) <= (max_mask));            \
    }                                                                       \
    ind.value = 0;                                                          \
    ind.encoding = 4;                                                       \
    ind.byte_mask = (mask);                                                 \
    __asm { alu[--, --, B, ind] }

#endif



/*
 * Macros for NFP6000
 */



#ifdef __NFP_INDIRECT_REF_FORMAT_NFP6000

/*
 * Override fields macros  used internally by the standard library.
 */

// Override byte mask as data in PREV ALU
#define _INTRINSIC_OVERRIDE_BYTEMASK_AS_DATA_FIELD(ov_alu, ov_data)             \
{                                                                               \
    ov_alu = ov_alu | (((ov_data) & 0xff) << 16) | ovr_data_byte_mask_bit;      \
}

// Override length but mask/limit the length bits required by the operation
#define _INTRINSIC_OVERRIDE_LENGTH_FIELD(ov_alu, ov_len)                        \
{                                                                               \
    ov_alu = ov_alu | (((ov_len) & 0x1f) << 8) | ovr_length_bit;                \
}

// Override immediate 16 bits
#define _INTRINSIC_OVERRIDE_IMM_DATA_FIELD(ov_alu, ov_data)                     \
{                                                                               \
    ov_alu = ov_alu | ovr_data_16bit_imm_bit | (((ov_data) & 0xffff) << 16);    \
}

// Override xfer
#define _INTRINSIC_OVERRIDE_FULL_REF_FIELD(ov_alu, ov_data)                     \
{                                                                               \
    ov_alu = ov_alu | ovr_data_full_ref_bit | (((ov_data) & 0xffff) << 16);     \
}

// Override byte mask which has ovr bit set in PREV ALU result and data in indirect CSR
#define _INTRINSIC_OVERRIDE_BYTEMASK_IND_CSR_FIELD(ov_alu, ov_csr, ov_bm)       \
{                                                                               \
    ov_alu = ov_alu | ovr_byte_mask_bit;                                        \
    ov_csr = ov_csr | ((ov_bm) & 0xff);                                         \
}

// Override data master
#define _INTRINSIC_OVERRIDE_DATA_MASTER_FIELD(ov_alu, ov_csr, ov_master)        \
{                                                                               \
    ov_alu = ov_alu | ovr_data_master_bit;                                      \
    ov_csr = ov_csr | (((ov_master) & 0x3ff) << 20);                            \
}

// Override 14 bits - island+master+signal_master in CSR ind
#define _INTRINSIC_OVERRIDE_SIGNAL_ISLAND_AND_DATA_MASTER_FIELD(ov_alu, ov_csr, ov_master)     \
{                                                                                       \
    ov_alu = ov_alu | ovr_signal_and_data_master_bit;                                   \
    ov_csr = ov_csr | ((ov_master & 0x3fff) << 16);                                     \
}

/*
 * These macros are used internally by the standard library.
 * These macros initialises and set the override bits plus override fields
 */

/*
 * Override bytemask in prev ALU result
 */
#define _INTRINSIC_OVERRIDE_BYTEMASK_IN_ALU(ov_ind, bytemask)                              \
{                                                                                          \
    ov_ind.alu_ind.value = 0x00;                                                           \
    _INTRINSIC_OVERRIDE_BYTEMASK_AS_DATA_FIELD(ov_ind.alu_ind.value, bytemask);            \
}

#define _INTRINSIC_OVERRIDE_BYTEMASK _INTRINSIC_OVERRIDE_BYTEMASK_IN_ALU

/*
 * Override length in prev ALU result
 */
#define _INTRINSIC_OVERRIDE_LENGTH(ov_ind, length)                                          \
{                                                                                           \
    ov_ind.alu_ind.value = 0x00;                                                            \
    _INTRINSIC_OVERRIDE_LENGTH_FIELD(ov_ind.alu_ind.value, length);                         \
}

/*
 * Override length and bytemask in prev ALU result
 */
#define _INTRINSIC_OVERRIDE_LENGTH_AND_BYTEMASK_IN_ALU(ov_ind, length, bytemask)            \
{                                                                                           \
    ov_ind.alu_ind.value = 0x00;                                                            \
    _INTRINSIC_OVERRIDE_BYTEMASK_AS_DATA_FIELD(ov_ind.alu_ind.value, bytemask);             \
    _INTRINSIC_OVERRIDE_LENGTH_FIELD(ov_ind.alu_ind.value, length);                         \
}

/*
 * Override immediate data in prev ALU result
 */
#define _INTRINSIC_OVERRIDE_DATA_IN_ALU(ov_ind, data)                                       \
{                                                                                           \
    ov_ind.alu_ind.value = 0x00;                                                            \
    _INTRINSIC_OVERRIDE_IMM_DATA_FIELD(ov_ind.alu_ind.value, data);                         \
}

/*
 * Override length and immediate data in prev ALU result
 */
#define _INTRINSIC_OVERRIDE_IMM_DATA_AND_LENGTH(ov_ind, data, length)                       \
{                                                                                           \
    ov_ind.alu_ind.value = 0x00;                                                            \
    _INTRINSIC_OVERRIDE_IMM_DATA_FIELD(ov_ind.alu_ind.value, data);                         \
    _INTRINSIC_OVERRIDE_LENGTH_FIELD(ov_ind.alu_ind.value, length);                         \
}

/*
 * Override full data ref in prev ALU result
 */
#define _INTRINSIC_OVERRIDE_FULL_DATA_REF(ov_ind, data)                                     \
{                                                                                           \
    ov_ind.alu_ind.value = 0x00;                                                            \
    _INTRINSIC_OVERRIDE_FULL_REF_FIELD(ov_ind.alu_ind.value, data);                         \
}


/* Count override */
#define _INTRINSIC_IND_ALU_COUNT_MIN_MAX(count, min_value, max_value)       \
    generic_ind_t ind;                                                      \
    if (__is_ct_const(count))                                               \
    {                                                                       \
        CT_ASSERT((count) >= (min_value) && (count) <= (max_value));        \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        RT_RANGE_ASSERT((count) >= (min_value) && (count) <= (max_value));  \
    }                                                                       \
    _INTRINSIC_OVERRIDE_LENGTH(ind, (count-1));                             \
    __asm { alu[--, --, B, ind.alu_ind.value] }


/* Count and Byte mask override */
#define _INTRINSIC_IND_ALU_COUNT_MIN_MAX_MASK_MAX(count, min_value, max_value, mask, max_mask) \
    generic_ind_t ind;                                                      \
    if (__is_ct_const(count))                                               \
    {                                                                       \
        CT_ASSERT((count) >= (min_value) && (count) <= (max_value));        \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        RT_RANGE_ASSERT((count) >= (min_value) && (count) <= (max_value));  \
    }                                                                       \
    if (__is_ct_const(mask))                                                \
    {                                                                       \
        CT_ASSERT((mask) <= (max_mask));                                    \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        RT_RANGE_ASSERT((mask) <= (max_mask));                              \
    }                                                                       \
    _INTRINSIC_OVERRIDE_LENGTH_AND_BYTEMASK_IN_ALU(ind, (count-1), mask);   \
    __asm { alu[--, --, B, ind.alu_ind.value] }


/* Byte mask override */
#define _INTRINSIC_IND_ALU_MASK_MAX(mask,max_mask)                          \
    generic_ind_t ind;                                                      \
    if (__is_ct_const(mask))                                                \
    {                                                                       \
        CT_ASSERT((mask) >= 0x1 &&  (mask) <= (max_mask));                  \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        RT_RANGE_ASSERT((mask) >= 0x1 &&  (mask) <= (max_mask));            \
    }                                                                       \
    _INTRINSIC_OVERRIDE_BYTEMASK_IN_ALU(ind, mask);                         \
    __asm { alu[--, --, B, ind.alu_ind.value] }

#endif /* NFP_6000 */



/* Convert 40 bit address to high and low address */
#define _INTRINSIC_CONVERT_HI_LO_ADDRESS(address)                       \
    hi_addr = (unsigned int)((unsigned long long)address>>32);          \
    hi_addr = (unsigned int)hi_addr<<24;                                \
    low_addr = (unsigned int)address;



/**
 * @addtogroup misc Miscellaneous Intrinsics
 * @{
 */

/** Assert if unsigned value is not between min_value and max_value. If all of these are
 * constants, a compile time assert is shown otherwise a runtime assert.
 *
 * @param value       Value to verify if within range
 * @param min_value   The minimum value of the range
 * @param max_value   The maximum value of the range
 *
 */
__intrinsic
void assert_range(unsigned int value, unsigned int min_value, unsigned int max_value);




/** Rotate right a 32-bit word by specified number of bits.
 *
 * @param value     The 32-bit value to rotate to the right
 * @param shift     The number of bits to rotate to the right (1 - 31).
 *
 * @return         The 32-bit result of the value shifted to the right by "shift" bits.
 */
__intrinsic
unsigned int rotr(unsigned int value, int shift);

/** Rotate left a 32-bit word by specified number of bits.
 *
 * @param value     The 32-bit value to rotate to the left
 * @param shift     The number of bits to rotate to the left (1 - 31).
 *
 * @return         The 32-bit result of the value shifted to the left by "shift" bits.
 */
__intrinsic
unsigned int rotl(unsigned int value, int shift);

/**
 * @}
 */



/*
 * Lightweight runtime asserts for intrinsic functions - the context is suspended
 * and mailbox1 contains the address where the problem occurred. mailbox 0
 * is set to zero.
 *
 * Excluding the condition check the assert uses about 4 instructions. It does
 * not use any SRAM as assert() in util.c as it only records the program
 * counter. The list file can be used to determine the location in source
 * code where the assert failed.
 *
 * Run time asserts are only done when _INTRINSIC_RT_ASSERT is defined
 */
#ifdef _INTRINSIC_RT_ASSERT
__noinline
__intrinsic
void ___rt_assert(void* addr)
{
    local_csr_write(local_csr_mailbox1,(unsigned int)addr);
    local_csr_write(local_csr_mailbox0,1);
    __asm ctx_arb[bpt]
}

/*
 * Needs to be intrinsic to use from intrinsics
 */
__intrinsic
__forceinline
void __rt_assert(void)
{
    __gpr uint32_t reg;
    __asm
    {
        load_addr[reg,label]
        label:
    }
    ___rt_assert((void*)reg);
}


/* RT_ALIGN_ASSERT is used for pointer alignment asserts */
#define RT_ALIGN_ASSERT(exp) RT_ASSERT(exp)

/* RT_RANGE_ASSERT is used for value and count asserts */
#define RT_RANGE_ASSERT(exp) RT_ASSERT(exp)

/* RT_ASSERT is for asserts not falling in the above two categories */
#define RT_ASSERT(exp) (void)( (exp) || (__rt_assert(),0) )

#else /* ! _INTRINSIC_RT_ASSERT */

#define RT_ALIGN_ASSERT(exp)
#define RT_RANGE_ASSERT(exp)
#define RT_ASSERT(exp)

#endif

#endif /* __NFP_INTRINSIC_H__ */

